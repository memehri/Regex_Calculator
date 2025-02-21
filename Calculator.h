#ifndef REGEX_CALCULATOR_CALCULATOR_H
#define REGEX_CALCULATOR_CALCULATOR_H

#include <cctype>
#include "Stack.h"
#include <cmath>
#include <conio.h>
#include <cstring>
#include <cstdlib>

int isp(char ch) {
    if (ch == '#') return 1;
    if (ch == '-') return 2;
    if (ch == '+') return 2;
    if (ch == '*') return 3;
    if (ch == '/') return 3;
    if (ch == '^') return 4;
    if ((ch == 's') || (ch == 'c') || (ch == 't') || (ch == 'o') || (ch == 'l') || (ch == 'L')) return 5;
    if (ch == '(') return 0;
}

int icp(char ch) {
    if (ch == '#') return 1;
    if (ch == '-') return 2;
    if (ch == '+') return 2;
    if (ch == '*') return 3;
    if (ch == '/') return 3;
    if (ch == '^') return 4;
    if ((ch == 's') || (ch == 'c') || (ch == 't') || (ch == 'o') || (ch == 'l') || (ch == 'L')) return 5;
    if (ch == '(') return 6;
}

char convert(char *s) {
    if (!strcmp(s, "sin")) return 's';
    if (!strcmp(s, "cos")) return 'c';
    if (!strcmp(s, "tan")) return 't';
    if (!strcmp(s, "cot")) return 'o';
    if (!strcmp(s, "log")) return 'L';
    if (!strcmp(s, "ln")) return 'l';
    if (!strcmp(s, "+")) return '+';
    if (!strcmp(s, "-")) return '-';
    if (!strcmp(s, "*")) return '*';
    if (!strcmp(s, "/")) return '/';
    if (!strcmp(s, "(")) return '(';
    if (!strcmp(s, "^")) return '^';
}

char *get(char *s) {
    int i = 0;
    char *r = new char[10];
    if (!isalpha(*s)) {
        r[0] = *s;
        r[1] = '\0';
        return r;
    } else {
        while (isalpha(*s)) {
            r[i] = *s;
            s++;
            i++;
        }
        r[i] = '\0';
        return r;
    }
}

class Node {
public:
    double number;
    char data;
    Node *right;
    Node *left;

    friend class Calculator;
};

class Calculator {
public:
    Node *maketree(char *s);

    double value(Node *);
};

double Calculator::value(Node *n) {
    if (n) {
        if (n->data == '\0') return n->number;
        else {
            switch (n->data) {
                case '+':
                    n->number = value(n->right) + value(n->left);
                    break;
                case '-':
                    n->number = value(n->left) - value(n->right);
                    break;
                case '/':
                    n->number = value(n->left) / value(n->right);
                    break;
                case '*':
                    n->number = value(n->left) * value(n->right);
                    break;
                case '^':
                    n->number = pow(value(n->left), value(n->right));
                    break;
                case 's':
                    n->number = sin(3.1415 / (180 / (value(n->right))));
                    break;
                case 'c':
                    n->number = cos(3.1415 / (180 / (value(n->right))));
                    break;
                case 't':
                    n->number = tan(3.1415 / (180 / (value(n->right))));
                    break;
                case 'o':
                    n->number = 1 / tan(3.1415 / (180 / (value(n->right))));
                    break;
                case 'L':
                    n->number = log10(value(n->right));
                    break;
                case 'l':
                    n->number = log(value(n->right));
            }
            return n->number;
        }
    }
    return 0;
}

Node *Calculator::maketree(char *s) {
    Stack<Node *> sta;
    Stack<char> sign;
    sign.push('#');
    int j = 0;
    char r[20];
    r[0] = '\0';
    char c;
    while (*s != '#' && *s != '\0') {
        if (isdigit(*s) || *s == '.') {
            r[j] = *s;
            j++;
            s++;
            continue;
        } else {
            if (r[0] != '\0') {
                r[j] = '\0';
                Node *n = new Node;
                n->data = '\0';
                n->number = atof(r);
                n->right = nullptr;
                n->left = nullptr;
                sta.push(n);
                j = 0;
                r[0] = '\0';
            }
            if (*s == ')')
                for (char c = sign.pop(); c != '('; c = sign.pop()) {
                    if (!isalpha(c)) {
                        Node *n = new Node;
                        n->number = 0;
                        n->data = c;
                        Node *p, *q;
                        p = sta.pop();
                        q = sta.pop();
                        n->right = p;
                        n->left = q;
                        sta.push(n);
                    } else {
                        Node *n = new Node;
                        n->left = 0;
                        n->data = c;
                        n->number = 0;
                        Node *p;
                        p = sta.pop();
                        n->right = p;
                        sta.push(n);
                    }
                }
            else {
                for (c = sign.pop(); isp(c) >= icp(convert(get(s))); c = sign.pop()) {
                    if (!isalpha(c)) {
                        Node *n = new Node;
                        n->number = 0;
                        n->data = c;
                        Node *p, *q;
                        p = sta.pop();
                        q = sta.pop();
                        n->right = p;
                        n->left = q;
                        sta.push(n);
                    } else {
                        Node *n = new Node;
                        n->left = 0;
                        n->data = c;
                        n->number = 0;
                        Node *p;
                        p = sta.pop();
                        n->right = p;
                        sta.push(n);
                    }
                }
                sign.push(c);
                sign.push(convert(get(s)));
            }
            if (isalpha(*s)) while (isalpha(*s)) s++; else s++;
        }
    }
    if (r[0] != '\0') {
        r[j] = '\0';
        Node *n = new Node;
        n->data = '\0';
        n->number = atof(r);
        n->right = 0;
        n->left = 0;
        sta.push(n);
        r[0] = '\0';
    }
    while (!sign.isEmpty()) {
        c = sign.pop();
        if (c != '#') {
            if (!isalpha(c)) {
                Node *n = new Node;
                n->number = 0;
                n->data = c;
                Node *p, *q;
                p = sta.pop();
                q = sta.pop();
                n->right = p;
                n->left = q;
                sta.push(n);
            } else {
                Node *n = new Node;
                n->left = nullptr;
                n->data = c;
                n->number = 0;
                Node *p;
                p = sta.pop();
                n->right = p;
                sta.push(n);
            }
        }
    }
    return sta.pop();
}

#endif //REGEX_CALCULATOR_CALCULATOR_H
