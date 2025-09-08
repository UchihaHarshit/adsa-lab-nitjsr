#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int q1[MAX], q2[MAX];
int front1 = -1, rear1 = -1;
int front2 = -1, rear2 = -1;

// Queue helpers
int isEmpty(int front, int rear) { return (front == -1); }
void enqueue(int q[], int *front, int *rear, int x) {
    if (*rear == MAX - 1) {
        printf("Queue Overflow\n");
        return;
    }
    if (*front == -1) *front = 0;
    q[++(*rear)] = x;
}
int dequeue(int q[], int *front, int *rear) {
    if (isEmpty(*front, *rear)) return -1;
    int x = q[*front];
    if (*front == *rear) *front = *rear = -1;
    else (*front)++;
    return x;
}

// Stack operations (Method 1)
void pushM1(int x) {
    // Enqueue to q2
    enqueue(q2, &front2, &rear2, x);

    // Move all from q1 to q2
    while (!isEmpty(front1, rear1)) {
        enqueue(q2, &front2, &rear2, dequeue(q1, &front1, &rear1));
    }

    // Swap q1 and q2
    int tempF = front1, tempR = rear1;
    front1 = front2; rear1 = rear2;
    front2 = tempF;  rear2 = tempR;

    printf("%d pushed\n", x);
}

void popM1() {
    if (isEmpty(front1, rear1)) {
        printf("Stack is EMPTY!\n");
    } else {
        printf("%d popped\n", dequeue(q1, &front1, &rear1));
    }
}

// Stack operations (Method 2)
void pushM2(int x) {
    enqueue(q1, &front1, &rear1, x);
    printf("%d pushed\n", x);
}

void popM2() {
    if (isEmpty(front1, rear1)) {
        printf("Stack is EMPTY!\n");
    } else {
        // Move elements except last from q1 -> q2
        while (front1 != rear1) {
            enqueue(q2, &front2, &rear2, dequeue(q1, &front1, &rear1));
        }
        // Last element is stack top
        printf("%d popped\n", dequeue(q1, &front1, &rear1));

        // Swap q1 and q2
        int tempF = front1, tempR = rear1;
        front1 = front2; rear1 = rear2;
        front2 = tempF;  rear2 = tempR;
    }
}

int main() {
    int choice, value, method;

    printf("Select method:\n1. Push costly\n2. Pop costly\nEnter choice: ");
    scanf("%d", &method);

    while (1) {
        printf("\n--- Stack using Two Queues ---\n");
        printf("1. Push\n2. Pop\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                if (method == 1) pushM1(value);
                else pushM2(value);
                break;
            case 2:
                if (method == 1) popM1();
                else popM2();
                break;
            case 3:
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}