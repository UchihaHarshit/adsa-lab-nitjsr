#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void preorder(struct Node* root) {
    if (root == NULL) {
        return;
    }
    // Step 1: Visit root
    printf("%d ", root->data);

    // Step 2: Traverse left subtree
    preorder(root->left);

    // Step 3: Traverse right subtree
    preorder(root->right);
}

int main() {
    // Constructing a sample tree:
    //        1
    //       / \
    //      3   5
    //     / \   \
    //    7   9   11

    struct Node* root = createNode(1);
    root->left = createNode(3);
    root->right = createNode(5);
    root->left->left = createNode(7);
    root->left->right = createNode(9);
    root->right->right = createNode(11);

    printf("Preorder Traversal: ");
    preorder(root);

    return 0;
}