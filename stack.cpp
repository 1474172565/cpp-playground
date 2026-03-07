#include <iostream>
using namespace std;

class Stack {
    int arr[100];
    int top;
public:
    Stack() : top(-1) {}
    void push(int x) { arr[++top] = x; }
    void pop() { if(top>=0) top--; }
    int peek() { return arr[top]; }
};