#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

int index = 0;

Node* createNode(char data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

Node* buildTreeFromPrefix(char* prefix) {
    // Skip spaces
    while (prefix[index] == ' ') index++;

    // End of string
    if (prefix[index] == '\0' || prefix[index] == '\n') return NULL;

    char token = prefix[index++];
    Node* node = createNode(token);

    // If operator, build left and right subtrees
    if (token == '+' || token == '-' || token == '*' || token == '/') {
        node->left = buildTreeFromPrefix(prefix);
        node->right = buildTreeFromPrefix(prefix);
    }

    return node;
}

void printPostfix(Node* root) {
    if (!root) return;
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c ", root->data);
}

int main() {
    char prefixExpr[100];

    printf("Enter prefix expression:\n");
    if (!fgets(prefixExpr, sizeof(prefixExpr), stdin)) {
        printf("Input error\n");
        return 1;
    }

    index = 0;
    Node* root = buildTreeFromPrefix(prefixExpr);

    printf("Postfix expression: ");
    printPostfix(root);
    printf("\n");

    return 0;
}
