#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define N 4

// Represents a state of the puzzle
typedef struct Node {
    struct Node* parent;
    int board[N][N];
    int blank_x, blank_y;
    int g_cost; // Level
    int f_cost; // g_cost + h_cost
    struct Node* next;
} Node;

Node* pq_head = NULL; // Head of the priority queue

int calculateMHDistance(int board[N][N], int goal[N][N]) {
    int distance = 0;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            if (board[i][j] != 0) {
                for (int r = 0; r < N; r++)
                    for (int c = 0; c < N; c++)
                        if (goal[r][c] == board[i][j])
                            distance += abs(i - r) + abs(j - c);
            }
        }
    return distance;
}

// Creates a new puzzle node
Node* newNode(int board[N][N], int x, int y, int g_cost, Node* parent, int goal[N][N]) {
    Node* node = (Node*)malloc(sizeof(Node));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            node->board[i][j] = board[i][j];
    node->parent = parent;
    node->blank_x = x;
    node->blank_y = y;
    node->g_cost = g_cost;
    node->f_cost = g_cost + calculateMHDistance(board, goal);
    node->next = NULL;
    return node;
}

// Priority Queue (Sorted Linked List)
void push(Node* node) {
    if (!pq_head || node->f_cost < pq_head->f_cost) {
        node->next = pq_head;
        pq_head = node;
    } else {
        Node* curr = pq_head;
        while (curr->next && curr->next->f_cost <= node->f_cost)
            curr = curr->next;
        node->next = curr->next;
        curr->next = node;
    }
}

Node* pop() {
    if (!pq_head) return NULL;
    Node* temp = pq_head;
    pq_head = pq_head->next;
    return temp;
}

// Solvability
bool isSolvable(int board[N][N]) {
    int inversions = 0;
    int arr[N * N];
    int k = 0, blankRowFromBottom = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (board[i][j] == 0) blankRowFromBottom = N - i;
            arr[k++] = board[i][j];
        }
    }
    for (int i = 0; i < N * N - 1; i++)
        for (int j = i + 1; j < N * N; j++)
            if (arr[i] && arr[j] && arr[i] > arr[j])
                inversions++;
    return ((inversions % 2 != 0) && (blankRowFromBottom % 2 == 0)) ||
           ((inversions % 2 == 0) && (blankRowFromBottom % 2 != 0));
}

void printPath(Node* node) {
    if (node == NULL) return;
    printPath(node->parent);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) printf("%3d ", node->board[i][j]);
        printf("\n");
    }
    printf("-----------\n");
}

void solve(int initial[N][N], int goal[N][N], int bx, int by) {
    if (!isSolvable(initial)) {
        printf("This puzzle is not solvable.\n");
        return;
    }

    int row[] = {1, -1, 0, 0};
    int col[] = {0, 0, 1, -1};
    push(newNode(initial, bx, by, 0, NULL, goal));

    while (pq_head) {
        Node* min = pop();
        if (calculateMHDistance(min->board, goal) == 0) {
            printf("Goal Reached in %d moves!\n", min->g_cost);
            printPath(min);
            // Clean up memory
            while(pq_head) free(pop());
            while(min) { Node* temp = min; min = min->parent; free(temp); }
            return;
        }
        for (int i = 0; i < 4; i++) {
            int new_x = min->blank_x + row[i], new_y = min->blank_y + col[i];
            if (new_x >= 0 && new_x < N && new_y >= 0 && new_y < N) {
                int new_board[N][N];
                for (int r = 0; r < N; r++) for (int c = 0; c < N; c++) new_board[r][c] = min->board[r][c];
                new_board[min->blank_x][min->blank_y] = new_board[new_x][new_y];
                new_board[new_x][new_y] = 0;
                push(newNode(new_board, new_x, new_y, min->g_cost + 1, min, goal));
            }
        }
    }
}

 
int main() {
    int initial[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 0, 8}, // 0 is the blank
        {9, 10, 7, 12},
        {13, 14, 11, 15}};
    int goal[N][N] = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 10, 11, 12},
        {13, 14, 15, 0}};

    solve(initial, goal, 1, 2); // blank is at (1, 2)
    return 0;
}