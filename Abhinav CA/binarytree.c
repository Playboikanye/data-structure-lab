#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char opStack[MAX];
int topOp = -1;

typedef struct Node {
    char data;
    struct Node *left, *right;
} Node;

Node *nodeStack[MAX];
int topNode = -1;

void pushOp(char c) {
    opStack[++topOp] = c;
}

char popOp() {
    return opStack[topOp--];
}

char peekOp() {
    return opStack[topOp];
}

int isEmptyOp() {
    return topOp == -1;
}

void pushNode(Node *node) {
    nodeStack[++topNode] = node;
}

Node *popNode() {
    return nodeStack[topNode--];
}

Node* newNode(char data) {
    Node *node = (Node*) malloc(sizeof(Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

int precedence(char c) {
    if (c == '+' || c == '-') return 1;
    if (c == '*' || c == '/') return 2;
    if (c == '^') return 3;
    return 0;
}

void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;
    for (i = 0; (c = infix[i]) != '\0'; i++) {
        if (isalnum(c)) {
            postfix[k++] = c;
        } else if (c == '(') {
            pushOp(c);
        } else if (c == ')') {
            while (!isEmptyOp() && peekOp() != '(')
                postfix[k++] = popOp();
            popOp(); // remove '('
        } else {
            while (!isEmptyOp() && precedence(peekOp()) >= precedence(c))
                postfix[k++] = popOp();
            pushOp(c);
        }
    }
    while (!isEmptyOp())
        postfix[k++] = popOp();
    postfix[k] = '\0';
}

Node* buildTree(char postfix[]) {
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        Node *node = newNode(c);
        if (isalnum(c)) {
            pushNode(node);
        } else {
            node->right = popNode();
            node->left = popNode();
            pushNode(node);
        }
    }
    return popNode();
}

void preorder(Node *root) {
    if (root) {
        printf("%c ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node *root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%c ", root->data);
    }
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    

    Node *root = buildTree(postfix);
    printf("Binary expression tree created successfully.\n");

    printf("\nPrefix expression : ");
    preorder(root);
    printf("\nPostfix expression: ");
    postorder(root);
    printf("\n");

    return 0;
}