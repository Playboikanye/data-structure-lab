#include <stdio.h>
#define MAX 10

int deque[MAX];
int front = -1;
int rear = -1;

int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

int isEmpty() {
    return (front == -1);
}

void insertFront(int item) {
    if (isFull()) {
        printf("Deque is full\n");
        return;
    }

    if (isEmpty()) {
        front =0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }

    deque[front] = item;
    printf("Inserted %d at front\n", item);
}

void insertRear(int item) {
    if (isFull()) {
        printf("Deque is full\n");
        return;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }

    deque[rear] = item;
    printf("Inserted %d at rear\n", item);
}

void deleteFront() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }

    int item = deque[front];
    printf("Deleted %d from front\n", item);

    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

void deleteRear() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }

    int item = deque[rear];
    printf("Deleted %d from rear\n", item);

    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

void display() {
    if (isEmpty()) {
        printf("Deque is empty\n");
        return;
    }

    printf("Elements in deque are: ");
    int i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear)
            break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

void getFront() {
    if (isEmpty()) {
        printf("Deque is empty\n");
    } else {
        printf("Element at front: %d\n", deque[front]);
    }
}

void getRear() {
    if (isEmpty()) {
        printf("Deque is empty\n");
    } else {
        printf("Element at rear: %d\n", deque[rear]);
    }
}

int main() {
    int choice, value;
    int running = 1;

    while (running) {
        printf("\nChoose operation:\n");
        printf("1. Insert at Front\n2. Insert at Rear\n3. Delete from Front\n4. Delete from Rear\n");
        printf("5. Display\n6. Peek Front\n7. Peek Rear\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertFront(value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertRear(value);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                getFront();
                break;
            case 7:
                getRear();
                break;
            case 8:
                printf("Exiting...\n");
                running = 0;
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    return 0;
}
