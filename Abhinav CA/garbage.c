#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Block {
    int size;
    bool is_free;
    bool marked;
    struct Block* prev;
    struct Block* next;
} Block;

Block* head = NULL;

void create_block(int size) {
    Block* new_block = (Block*)malloc(sizeof(Block));
    new_block->size = size;
    new_block->is_free = true;
    new_block->marked = false;
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
    Block* temp = head;

    while (temp != NULL) {
        if (temp->is_free && temp->size >= size) {
            if (temp->size > size) {
                Block* new_block = (Block*)malloc(sizeof(Block));
                new_block->size = temp->size - size;
                new_block->is_free = true;
                new_block->marked = false;

                new_block->next = temp->next;
                if (new_block->next != NULL)
                    new_block->next->prev = new_block;

                new_block->prev = temp;
                temp->next = new_block;

                temp->size = size;
            }

            temp->is_free = false;
            printf("Allocated %d bytes.\n", size);
            return;
        }
        temp = temp->next;
    }

    printf("No suitable block found for %d bytes.\n", size);
}

void display_memory() {
    Block* temp = head;
    int index = 1;
    printf("\nMemory Blocks:\n");
    printf("------------------------------\n");
    while (temp != NULL) {
        if (temp->is_free) {
            printf("Size: %4d | Free\n", temp->size);
        } else {
            printf("Size: %4d | Used (Block #%d) Marked: %d\n", temp->size, index, temp->marked);
            index++;
        }
        temp = temp->next;
    }
    printf("------------------------------\n");
}

void mark(Block* b) {
    if (b == NULL || b->marked || b->is_free) return;
    b->marked = true;
}

void sweep() {
    Block* temp = head;
    while (temp != NULL) {
        if (!temp->is_free && !temp->marked) {
            printf("Garbage Collector: Freeing block of size %d bytes\n", temp->size);
            temp->is_free = true;
        }
        temp->marked = false;
        temp = temp->next;
    }
}

void coalesce() {
    Block* temp = head;
    while (temp != NULL && temp->next != NULL) {
        if (temp->is_free && temp->next->is_free) {
            Block* next = temp->next;
            temp->size += next->size;

            temp->next = next->next;
            if (next->next != NULL)
                next->next->prev = temp;

            free(next);
        } else {
            temp = temp->next;
        }
    }
}

void gc(int roots[], int root_count) {
    Block* temp;
    int index;

    for (int i = 0; i < root_count; i++) {
        index = 0;
        temp = head;
        while (temp != NULL) {
            if (!temp->is_free) {
                if (++index == roots[i]) {
                    mark(temp);
                    break;
                }
            }
            temp = temp->next;
        }
    }

    sweep();
    coalesce();
}

int main() {
    int choice, size, n, i;

    printf("Enter number of initial memory blocks: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("Enter size of block %d: ", i + 1);
        scanf("%d", &size);
        create_block(size);
    }

    int roots[100];
    int root_count = 0;

    printf("\n1. Allocate\n2. Display\n3. Add Root\n4. Run Garbage Collector\n5. Exit\n");

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
            printf("Enter block number to add as root (allocated block index): ");
            int r;
            scanf("%d", &r);
            roots[root_count++] = r;
            printf("Root added: block #%d\n", r);
        } else if (choice == 4) {
            printf("Running Garbage Collector...\n");
            gc(roots, root_count);
        } else if (choice == 5) {
            printf("Exiting...\n");
            break;
        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}
