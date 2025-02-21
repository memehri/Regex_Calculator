#include <iostream>
#include <conio.h>
#include "Calculator.h"

using namespace std;

void menu();

void calculate() {
    char s[100];
    system("cls");
    cout << "Enter an string for calculating:" << endl;
    cin >> s;
    Calculator m;
    Node *n = m.maketree(s);
    cout << "Result is:" << m.value(n);
    cout << endl << "if you want goto menu press m";
    char ch = getch();
    if ((ch == 'm') || (ch == 'M')) menu(); else calculate();
}

void about() {
    system("cls");
    cout << "This program takes a mathematical expression as a string, constructs a tree representation of the expression, "
            << endl;
    cout << "and evaluates the result.";
    cout << "Developer:Rohollah(Mehrad) Mehri" << endl;
    getch();
    menu();
}

void menu() {
    system("cls");
    cout << "    Menu:" << endl;
    cout << "        C-Calculate" << endl;
    cout << "        A-About" << endl;
    cout << "        E-Exit" << endl;
    cout << "    please select a choice:";
    char ch = getch();
    switch (ch) {
        case 'c':
        case 'C':
            calculate();
            break;
        case 'a':
        case 'A':
            about();
            break;
        case 'e':
        case 'E':
            exit(0);
    }
}

int main() {
    menu();
    return 0;
}