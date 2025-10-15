#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insertSorted(Node** head, int value) {
    Node* newNode = malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (*head == NULL || (*head)->data >= value) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->data < value) {
        current = current->next;
    }

    newNode->next = current->next;
    current->next = newNode;
}


int search(Node* head, int value) {
    Node* current = head;
    while (current != NULL) {
        if (current->data == value) return 1;
        current = current->next;
    }
    return 0;
}


int deleteNode(Node** head, int value) {
    Node* current = *head;
    Node* prev = NULL;

    while (current != NULL && current->data != value) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) return 0; // not found

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
    return 1;
}


void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    Node* head = NULL;
    int choice, value;

    while (1) {
        printf("\n1. Insert\n2. Search\n3. Delete\n4. Print\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                insertSorted(&head, value);
                break;

            case 2:
                printf("Enter value to search: ");
                scanf("%d", &value);
                if (search(head, value))
                    printf("Value found.\n");
                else
                    printf("Value not found.\n");
                break;

            case 3:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                if (deleteNode(&head, value))
                    printf("Value deleted.\n");
                else
                    printf("Value not found.\n");
                break;

            case 4:
                printList(head);
                break;

            case 5:
                
                while (head != NULL) {
                    Node* temp = head;
                    head = head->next;
                    free(temp);
                }
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
