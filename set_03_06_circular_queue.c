#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int queue[SIZE];
int front = -1, rear = -1;

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is FULL!\n");
    } else {
        if (front == -1) front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("%d enqueued\n", value);
    }
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("%d dequeued\n", queue[front]);
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

void peek() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("Front element: %d\n", queue[front]);
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("Queue: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear) break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}


struct Node {
    int data;
    struct Node *next;
};

struct Node *front = NULL, *rear = NULL;

void enqueueLL(int value) {
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;

    if (front == NULL) {
        front = rear = newNode;
        rear->next = front;
    } else {
        rear->next = newNode;
        rear = newNode;
        rear->next = front;
    }
    printf("%d enqueued\n", value);
}
 
void dequeueLL() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
    } else if (front == rear) {
        printf("%d dequeued\n", front->data);
        free(front);
        front = rear = NULL;
    } else {
        struct Node *temp = front;
        printf("%d dequeued\n", front->data);
        front = front->next;
        rear->next = front;
        free(temp);
    }
}

void peekLL() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("Front element: %d\n", front->data);
    }
}

void displayLL() {
    if (front == NULL) {
        printf("Queue is EMPTY!\n");
        return;
    }

    struct Node *temp = front;
    printf("Queue: ");
    do {
        printf("%d ", temp->data);
        temp = temp->next;
    } while (temp != front);
    printf("\n");
}
 
int main() {
    int mainChoice, choice, value;

    while (1) {
        printf("\n=== Select Queue Implementation ===\n");
        printf("1. Circular Queue using Array\n");
        printf("2. Circular Queue using Linked List\n");
        printf("3. Exit Program\n");
        printf("Enter choice: ");
        scanf("%d", &mainChoice);

        if (mainChoice == 3) break;

        while (1) {
            printf("\n--- Operations Menu ---\n");
            printf("1. Enqueue\n2. Dequeue\n3. Peek\n4. Display\n5. Back to Main Menu\n");
            printf("Enter choice: ");
            scanf("%d", &choice);

            if (choice == 5) break;

            switch (choice) {
                case 1:
                    printf("Enter value: ");
                    scanf("%d", &value);
                    if (mainChoice == 1) enqueue(value);
                    else enqueueLL(value);
                    break;

                case 2:
                    if (mainChoice == 1) dequeue();
                    else dequeueLL();
                    break;

                case 3:
                    if (mainChoice == 1) peek();
                    else peekLL();
                    break;

                case 4:
                    if (mainChoice == 1) display();
                    else displayLL();
                    break;

                default:
                    printf("Invalid choice!\n");
            }
        }
    }

    printf("Exiting program...\n");
    return 0;
}