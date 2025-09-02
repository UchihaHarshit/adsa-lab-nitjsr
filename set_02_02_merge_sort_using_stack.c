#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Merge function
void merge(int arr[], int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    int left[n1], right[n2];

    for (int i = 0; i < n1; i++)
        left[i] = arr[start + i];
    for (int j = 0; j < n2; j++)
        right[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = start;

    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            arr[k++] = left[i++];
        else
            arr[k++] = right[j++];
    }

    while (i < n1)
        arr[k++] = left[i++];
    while (j < n2)
        arr[k++] = right[j++];
}

// Structure to hold subproblems (like recursive calls)
typedef struct {
    int start, end, state;
} Frame;

// Merge Sort using stack
void mergeSort(int arr[], int n) {
    Frame stack[MAX];
    int top = -1;

    // push initial problem
    stack[++top] = (Frame){0, n - 1, 0};

    while (top >= 0) {
        Frame curr = stack[top--];
        int start = curr.start;
        int end = curr.end;
        int state = curr.state;

        if (start >= end)
            continue;

        int mid = start + (end - start)/2;

        if (state == 0) {
            // First time visiting this node: process left part
            // Push current with state=1 to process right later
            stack[++top] = (Frame){start, end, 1};
            // Push left child
            stack[++top] = (Frame){start, mid, 0};
        } else if (state == 1) {
            // Finished left, now process right
            // Push current with state=2 for merge after right
            stack[++top] = (Frame){start, end, 2};
            // Push right child
            stack[++top] = (Frame){mid + 1, end, 0};
        } else {
            // Merge step after both children done
            merge(arr, start, mid, end);
        }
    }
}

// Driver code
int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    mergeSort(arr, n);

    printf("Sorted array:   ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}
