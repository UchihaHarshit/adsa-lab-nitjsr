#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int stack1[MAX], stack2[MAX];
int top1 = -1, top2 = -1;

// Stack operations
void push1(int x) { stack1[++top1] = x; }
int pop1() { return stack1[top1--]; }
int isEmpty1() { return top1 == -1; }

void push2(int x) { stack2[++top2] = x; }
int pop2() { return stack2[top2--]; }
int isEmpty2() { return top2 == -1; }

// Queue operations (Method 1)
void enqueueM1(int x) {
    // Move all elements from stack1 to stack2
    while (!isEmpty1()) {
        push2(pop1());
    }
    // Push new element into stack1
    push1(x);
    // Move everything back from stack2 to stack1
    while (!isEmpty2()) {
        push1(pop2());
    }
    printf("%d enqueued\n", x);
}

void dequeueM1() {
    if (isEmpty1()) {
        printf("Queue is EMPTY!\n");
    } else {
        printf("%d dequeued\n", pop1());
    }
}

// Queue operations (Method 2)
void enqueueM2(int x) {
    push1(x);
    printf("%d enqueued\n", x);
}

void dequeueM2() {
    if (isEmpty1() && isEmpty2()) {
        printf("Queue is EMPTY!\n");
    } else {
        if (isEmpty2()) {
            // Move elements from stack1 to stack2
            while (!isEmpty1()) {
                push2(pop1());
            }
        }
        printf("%d dequeued\n", pop2());
    }
}

int main() {
    int choice, value, method;
    printf("Select method:\n1. Push costly\n2. Pop costly\nEnter choice: ");
    scanf("%d", &method);

    while (1) {
        printf("\n--- Queue using Two Stacks ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                if (method == 1) enqueueM1(value);
                else enqueueM2(value);
                break;

            case 2:
                if (method == 1) dequeueM1();
                else dequeueM2();
                break;

            case 3:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}