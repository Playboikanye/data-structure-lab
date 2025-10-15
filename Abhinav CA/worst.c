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
    struct Block *t = head, *worst = NULL;
    while (t) {
        if (t->free && t->size >= s) {
            if (!worst || t->size > worst->size)
                worst = t;
        }
        t = t->next;
    }
    if (worst) {
        worst->size -= s;
        if (worst->size == 0)
            worst->free = 0;
        printf("Allocated process %d, remaining block size: %d\n", s, worst->size);
    } else {
        printf("No block found for %d\n", s);
    }
}

void display() {
    struct Block *t = head;
    int i = 1;
    printf("\nBlock\tRemaining Size\tStatus\n");
    while (t) {
        printf("%d\t%d\t\t%s\n", i++, t->size, t->free ? "Free" : "Used");
        t = t->next;
    }
}

int main() {
    int nb, np;
    printf("Enter number of memory blocks: ");
    scanf("%d", &nb);
    int b[nb];
    printf("Enter sizes of each block:\n");
    for (int i = 0; i < nb; i++) scanf("%d", &b[i]);
    create(b, nb);

    printf("Enter number of processes: ");
    scanf("%d", &np);
    int p[np];
    printf("Enter sizes of each process:\n");
    for (int i = 0; i < np; i++) {
        scanf("%d", &p[i]);
        alloc(p[i]);
    }
    printf("Using Worst fit memory allocation:\n");
    display();

    return 0;
}


