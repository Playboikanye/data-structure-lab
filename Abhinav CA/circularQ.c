#include <stdio.h>

#define SIZE 5

int queue[SIZE];
int front = 0, rear = 0;
int count = 0;

void enqueue(int value) {
    if (count == SIZE) {
        printf("Queue Overflow\n");
        return;
    }
    queue[rear] = value;
    rear = (rear + 1) % SIZE;
    count++;
    printf("%d enqueued\n", value);
}

void dequeue() {
    if (count == 0) {
        printf("Queue Underflow\n");
        return;
    }
    printf("%d dequeued\n", queue[front]);
    front = (front + 1) % SIZE;
    count--;
}

void display() {
    if (count == 0) {
        printf("Queue is empty\n");
        return;
    }
    int i = front;
    printf("Queue: ");
    for (int j = 0; j < count; j++) {
        printf("%d ", queue[i]);
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

void peek() {
    if (count == 0) {
        printf("Queue is empty\n");
        return;
    }
    printf("Front element: %d\n", queue[front]);
}

void Exit()
{
    printf("Exit from the program.");
}

int main() {
    int choice, value,size;

    printf("Enter the size: \n");
    scanf("%d", &size);
    if (size <= 0 || size > 100) {
        printf("Invalid size.\n");
        return 1;
    }

    printf("\n Circular Queue Operations:\n");
    printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Peek\n5. Exit\n");

    while (1) {
        printf("\nEnter your choice: \n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: \n");
                scanf("%d", &value);
                enqueue(value);
                break;
            case 2:
                dequeue(value);
                break;
            case 3:
                display();
                break;
            case 4:
                peek();
                break;
            case 5:
                Exit();
                return 0;
                break;
        }
    }

    return 0;
}