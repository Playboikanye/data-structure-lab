#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block {
    int size;
    bool is_free;
    struct Block* prev;
    struct Block* next;
} Block;

Block* head = NULL;

void create_block(int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->size = size;
    new_block->is_free = true;
    new_block->prev = NULL;
    new_block->next = NULL;

    if (head == NULL) {
        head = new_block;
    } else {
        Block* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = new_block;
        new_block->prev = temp;
    }
}

void allocate_memory(int size) {
    Block* best_fit = NULL;
    Block* temp = head;

    while (temp != NULL) {
        if (temp->is_free && temp->size >= size) {
            if (best_fit == NULL || temp->size < best_fit->size) {
                best_fit = temp;
            }
        }
        temp = temp->next;
    }

    if (best_fit == NULL) {
        printf("No suitable block found for %d bytes.\n", size);
        return;
    }

    if (best_fit->size > size) {
        Block* new_block = (Block*)malloc(sizeof(Block));
        new_block->size = best_fit->size - size;
        new_block->is_free = true;

        new_block->next = best_fit->next;
        if (new_block->next != NULL)
            new_block->next->prev = new_block;

        new_block->prev = best_fit;
        best_fit->next = new_block;

        best_fit->size = size;
    }

    best_fit->is_free = false;

    printf("Allocated %d bytes.\n", size);
}


void display_memory() {
    Block* temp = head;
    int index = 1;
    printf("\nMemory Blocks:\n");
    while (temp != NULL) {
        if (temp->is_free) {
            printf("Size: %4d | Free\n", temp->size);
        } else {
            printf("Size: %4d | Used (Block #%d)\n", temp->size, index);
            index++;
        }
        temp = temp->next;
    }
}

int main() {
    int choice, size, block_index, n, i;

    printf("Enter number of initial memory blocks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);
        create_block(size);
    }

    printf("\n1. Allocate\n2. Display\n3. Exit\n");

    while (1) {
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            printf("Enter size to allocate: ");
            scanf("%d", &size);
            allocate_memory(size);
        } else if (choice == 2) {
            display_memory();
        } else if (choice == 3) {
            printf("Exited\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}