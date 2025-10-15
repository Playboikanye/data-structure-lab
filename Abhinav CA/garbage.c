#include <stdio.h>
#include <stdlib.h>

struct Block {
    int size, free;
    struct Block *prev, *next;
};

struct Block *head = NULL;

void create(int n[], int m) {
    struct Block *t, *p = NULL;
    for (int i = 0; i < m; i++) {
        t = malloc(sizeof(struct Block));
        t->size = n[i];
        t->free = 1;
        t->next = NULL;
        t->prev = p;
        if (p) p->next = t;
        else head = t;
        p = t;
    }
}

void alloc(int s) {
    struct Block *t = head;
    while (t) {
        if (t->free && t->size >= s) {
            t->free = 0;
            printf("Allocated process %d in block %d\n", s, t->size);
            return;
        }
        t = t->next;
    }
    printf("No block found for %d\n", s);
}

void freeBlock(int pos) {
    struct Block *t = head;
    for (int i = 1; t && i < pos; i++)
        t = t->next;
    if (t && !t->free) {
        t->free = 1;
        printf("Freed block %d\n", pos);
    } else
        printf("Invalid block %d\n", pos);
}

void gc() {
    struct Block *t = head;
    while (t && t->next) {
        if (t->free && t->next->free) {
            t->size += t->next->size;
            struct Block *tmp = t->next;
            t->next = tmp->next;
            if (tmp->next) tmp->next->prev = t;
            free(tmp);
        } else
            t = t->next;
    }
}

// New compaction function
void compact() {
    struct Block *t = head, *newHead = NULL, *lastUsed = NULL;
    int totalFreeSize = 0;

    // Build new list with only used blocks
    while (t) {
        if (!t->free) {
            struct Block *newBlock = malloc(sizeof(struct Block));
            newBlock->size = t->size;
            newBlock->free = 0;
            newBlock->prev = lastUsed;
            newBlock->next = NULL;
            if (lastUsed) lastUsed->next = newBlock;
            else newHead = newBlock;
            lastUsed = newBlock;
        } else {
            totalFreeSize += t->size;
        }
        t = t->next;
    }

    // Add one big free block if there is free space
    if (totalFreeSize > 0) {
        struct Block *freeBlock = malloc(sizeof(struct Block));
        freeBlock->size = totalFreeSize;
        freeBlock->free = 1;
        freeBlock->prev = lastUsed;
        freeBlock->next = NULL;
        if (lastUsed) lastUsed->next = freeBlock;
        else newHead = freeBlock;  // all blocks free scenario
    }

    // Free old list
    t = head;
    while (t) {
        struct Block *tmp = t;
        t = t->next;
        free(tmp);
    }

    head = newHead;
}

void display() {
    struct Block *t = head;
    int i = 1;
    printf("\nBlock\tSize\tStatus\n");
    while (t) {
        printf("%d\t%d\t%s\n", i++, t->size, t->free ? "Free" : "Used");
        t = t->next;
    }
}

int main() {
    int nb, np;
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    int b[nb];
    printf("Enter sizes of each block:\n");
    for (int i = 0; i < nb; i++)
        scanf("%d", &b[i]);
    create(b, nb);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    int p[np];
    printf("Enter sizes of each process:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &p[i]);
        alloc(p[i]);
    }

    display();

    int n;
    printf("\nEnter number of blocks to free: ");
    scanf("%d", &n);
    printf("Enter block numbers to free:\n");
    for (int i = 0; i < n; i++) {
        int pos;
        scanf("%d", &pos);
        freeBlock(pos);
    }

    printf("\nBefore GC:");
    display();
    gc();
    printf("\nAfter GC:");
    display();

    printf("\nAfter Compaction:");
    compact();
    display();

    return 0;
}