#ifndef STACK1_H_INCLUDED
#define STACK1_H_INCLUDED

template<class T>
class Stack;

template<class T>
class Snode {
    friend class Stack<T>;

    T data;
    Snode *next;
};

template<class T>
class Stack {
    Snode<T> *first;
public:
    Stack();

    ~Stack();

    T pop();

    void push(T);

    bool isEmpty();
};

template<class T>
Stack<T>::Stack() {
    first = 0;
}

template<class T>
Stack<T>::~Stack() {
    Snode<T> *t;
    t = first;
    while (t) {
        first = first->next;
        delete t;
        t = first;
    }
}

template<class T>
bool Stack<T>::isEmpty() {
    return (first == 0);
}

template<class T>
T Stack<T>::pop() {
    T Data;
    Snode<T> *p;
    p = first;
    Data = p->data;
    first = first->next;
    delete p;
    return Data;
}

template<class T>
void Stack<T>::push(T d) {
    Snode<T> *t;
    t = new Snode<T>;
    t->data = d;
    t->next = first;
    first = t;
}

#endif // STACK1_H_INCLUDED
