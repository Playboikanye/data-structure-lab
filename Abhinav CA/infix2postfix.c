#include <stdio.h>
#include <ctype.h>
#define SIZE 30
char stack[SIZE];
int top = -1;
int precedence(char op) {
    if(op == '+' || op == '-') return 1;
    if(op == '*' || op == '/') return 2;
    if(op == '^') return 3;
    return 0;
}
void push(char c) {
    if(top < SIZE - 1)
        stack[++top] = c;
}
char pop() {
    if(top >= 0)
        return stack[top--];
    return '\0';
}
char peek() {
    if(top >= 0)
        return stack[top];
    return '\0';
}
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
int main() {
    char infix[SIZE], postfix[SIZE];
    int p = 0;
    printf("Enter the infix statement:\n");
    scanf("%s", infix);
    for(int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];
        if(isalnum(ch)) {
            postfix[p++] = ch;
        }
        else if(ch == '(') {
            push(ch);
        }
        else if(ch == ')') {
            while(peek() != '(' && top != -1) {
                postfix[p++] = pop();
            }
            pop(); 
        }
        else if(isOperator(ch)) {
            while(top != -1 && precedence(peek()) >= precedence(ch)) {
                postfix[p++] = pop();
            }
            push(ch);
        }
    }
    while(top != -1) {
        postfix[p++] = pop();
    }
    postfix[p] = '\0';
    printf("Postfix expression: %s\n", postfix);
    return 0;
}
