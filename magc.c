#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Obj {
    int id;
    bool marked;
    struct Obj* ref;
} Obj;

Obj* heap[MAX], *roots[MAX];
int hsize = 0, rsize = 0;

Obj* new_obj(int id) {
    if (hsize >= MAX) return NULL;
    Obj* o = malloc(sizeof(Obj));
    o->id = id; o->marked = 0; o->ref = NULL;
    heap[hsize++] = o;
    return o;
}

void add_root(Obj* o) {
    if (rsize < MAX) roots[rsize++] = o;
}

void mark(Obj* o) {
    if (!o || o->marked) return;
    o->marked = 1;
    mark(o->ref);
}

void sweep() {
    for (int i = 0; i < hsize; i++) {
        if (heap[i] && !heap[i]->marked) {
            printf("Collecting %d\n", heap[i]->id);
            free(heap[i]); heap[i] = NULL;
        } else if (heap[i]) {
            heap[i]->marked = 0;
        }
    }
}

void gc() {
    for (int i = 0; i < rsize; i++) mark(roots[i]);
    sweep();
}

void print_heap() {
    printf("Heap:\n");
    for (int i = 0; i < hsize; i++)
        if (heap[i]) printf("Obj %d\n", heap[i]->id);
}

int main() {
    Obj* a = new_obj(1), *b = new_obj(2), *c = new_obj(3);
    a->ref = b; b->ref = c;
    add_root(a);
    printf("Before GC:\n"); print_heap();
    b->ref = NULL;
    gc();
    printf("After GC:\n"); print_heap();
    return 0;
}