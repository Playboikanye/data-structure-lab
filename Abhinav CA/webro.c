#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Node 
{
    char url[100];
    struct Node* prev;
    struct Node* next;
} Node;
Node* head = NULL;
Node* current = NULL;
Node* createNode(const char* url) 
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->url, url);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
void visit(const char* url) 
{
    Node* newNode = createNode(url);
    if (head == NULL) 
    {
        head = newNode;
        current = newNode;
    } else {
        if (current->next) 
        {
            Node* temp = current->next;
            while (temp) 
            {
                Node* next = temp->next;
                free(temp);
                temp = next;
            }
            current->next = NULL;
        }

        current->next = newNode;
        newNode->prev = current;
        current = newNode;
    }
    printf("Visited: %s\n", current->url);
}
void goBack() {
    if (current && current->prev) 
    {
        current = current->prev;
        printf("Went back to: %s\n", current->url);
    } else {
        printf("No previous page.\n");
    }
}
void goForward() {
    if (current && current->next) 
    {
        current = current->next;
        printf("Went forward to: %s\n", current->url);
    } else {
        printf("No forward page.\n");
    }
}
void showCurrent() {
    if (current) {
        printf("Current page: %s\n", current->url);
    } else {
        printf("No page loaded.\n");
    }
}
void cleanUp() 
{
    Node* temp = head;
    while (temp) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
}
int main() 
{
    int choice;
    char url[100];
    printf("\n=== Browser Navigation ===\n");
    printf("1. Visit new URL\n");
    printf("2. Back\n");
    printf("3. Forward\n");
    printf("4. Show current page\n");
    printf("5. Exit\n");
    while (1) 
    {    
        printf("Choose an option: ");
        scanf("%d", &choice);
        getchar(); 
        switch (choice) 
        {
            case 1:
                printf("Enter URL: ");
                fgets(url, sizeof(url), stdin);
                url[strcspn(url, "\n")] = '\0'; 
                visit(url);
                break;
            case 2:
                goBack();
                break;
            case 3:
                goForward();
                break;
            case 4:
                showCurrent();
                break;
            case 5:
                cleanUp();
                printf("Exiting browser...\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}