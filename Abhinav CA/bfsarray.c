#include <stdio.h>
#define MAX 10
int queue[MAX];
int front = -1, rear = -1;
void enqueue(int x) {
if (rear == MAX - 1) return;
if (front == -1) front = 0;
rear++;
queue[rear] = x;
}
int dequeue() {
if (front == -1 || front > rear) return -1;
int val = queue[front];
front++;
return val;
}
int isEmpty() {
return (front == -1 || front > rear);
}
void BFS(int graph[MAX][MAX], int n, int start){
int visited[MAX] = {0};
int current;
enqueue(start);
visited[start] = 1;
printf("BFS order: ");
while (!isEmpty()) {
current = dequeue();
printf("%d ", current);
for (int i = 0; i < n; i++) {
if (graph[current][i] == 1 && visited[i] == 0) {
enqueue(i);
visited[i] = 1;
}
}
}
printf("\n");}
int main() {
int n, start;
int graph[MAX][MAX];
printf("Enter number of nodes (max %d): ", MAX);
scanf("%d", &n);
printf("Enter adjacency matrix (each row has %d numbers):\n", n);
for (int i = 0; i < n; i++)
for (int j = 0; j < n; j++)
scanf("%d", &graph[i][j]);
printf("Enter starting node (0 to %d): ", n - 1);
scanf("%d", &start);
BFS(graph, n, start);
return 0;
}