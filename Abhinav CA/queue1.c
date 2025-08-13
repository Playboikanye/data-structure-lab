#include <stdio.h>

#define MAX 10

int rear = -1;
int front = -1;
int queue[MAX];

void enqueue(int n) {
    if (rear == MAX - 1) {
        printf("Queue is full\n");
    } else if (rear == -1 && front == -1) {
        front = 0;
        rear = 0;
        queue[rear] = n;
        printf("The item has been entered\n");
    } else {
        rear++;
        queue[rear] = n;
        printf("The item has been entered\n");
    }
}

void dequeue() {
    if (front == -1 && rear == -1) {
        printf("Queue is empty\n");
    } else {
        int n = queue[front];
        printf("The deleted element is: %d\n", n);
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
    }
}

void display() {
    if (front == -1 && rear == -1) {
        printf("Queue is empty\n");
    } else {
        printf("The elements in queue are:\n");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
       printf("\n");
    }
}

void peek() {
    if (front == -1 && rear == -1) {
        printf("Queue is empty\n");
    } else {
        printf("The element at the front is: %d\n", queue[front]);
    }
}

int main() {
    int element, opt;
    int n=1;

    while (n) {
        printf("\nChoose among the following functions:\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Peek\n5. Exit\n");
        printf("Enter your option: ");
        scanf("%d", &opt);

        switch (opt) {
            case 1:
                printf("Enter the value to be entered: ");
                scanf("%d", &element);
                enqueue(element);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                peek();
                break;
            case 5:
                printf("Exiting program.\n");
                n=0;
                break;
            default:
                printf("Invalid function\n");
                break;
        }
    }

    return 0;
}