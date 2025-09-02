#include<stdio.h>
#include<stdlib.h>

struct node {           //Creating a structure for the linked list node
    int data;
    struct node *link;
};

// Global pointer to the start of the linked list
struct node *start = NULL;
// Function to insert a new node at the end of the linked list
void insert(int data) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->link = NULL;

    if(start == NULL){
        start = newNode;
    }
    else{
        struct node *temp = start;
        while(temp->link != NULL) {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}
// Function to insert a new node at a specific position in the linked list
void insertAtPosition(int data, int position) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->link = NULL;

    if(position == 1) {
        newNode->link = start;
        start = newNode;
        return;
    }

    struct node *temp = start;
    for(int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->link;
    }

    if(temp == NULL) {
        printf("Position out of bounds.\n");
        free(newNode);
        return;
    }

    newNode->link = temp->link;
    temp->link = newNode;
}

// Function to delete a node with a specific value from the linked list
void delete(int data) {
    if(start == NULL) {
        printf("List is empty.\n");
        return;
    }
    struct node *temp = start, *prev = NULL;

    while(temp != NULL && temp->data != data) {
        prev = temp;
        temp = temp->link;
    }

    if(temp == NULL) {
        printf("Element not found.\n");
        return;
    }

    if(prev == NULL) {
        start = temp->link;
    } else {
        prev->link = temp->link;
    }
    free(temp);
    printf("Element %d deleted.\n", data);
}

// Function to display the linked list
void display() {
    struct node *temp = start;
    if(temp == NULL) {
        printf("List is empty.\n");
        return;
    }
    while(temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->link;
    }
    printf("NULL\n");

}

// Function to search for a specific value in the linked list
void search(int data) {
    struct node *temp = start;
    while(temp != NULL) {
        if(temp->data == data) {
            printf("Element %d found in the list.\n", data);
            return;
        }
        temp = temp->link;
    }
    printf("Element %d not found in the list.\n", data);
}

int main() {
    int choice, data;
    int position;

    printf("\n1. Insert\n2. Insert at Position\n3. Delete\n4. Display\n5. Search\n6. Exit\n");
    while(1) {
        // printf("\n1. Insert\n2. Insert at Position\n3. Delete\n4. Display\n5. Search\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                printf("Enter position: ");
                scanf("%d", &position);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAtPosition(data, position);
                break;
            case 3:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                delete(data);
                break;
            case 4:
                display();
                break;
            case 5:
                printf("Enter data to search: ");
                scanf("%d", &data);
                search(data);
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}