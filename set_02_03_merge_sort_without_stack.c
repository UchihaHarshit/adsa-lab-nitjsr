#include <stdio.h>
#include <stdlib.h>

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

// Bottom-up Merge Sort
void mergeSort(int arr[], int n) {
    int size;   // Current subarray size
    int ls;  // Starting index of left subarray

    // Merge subarrays
    for (size = 1; size <= n - 1; size *= 2) {
        for (ls = 0; ls < n - 1; ls += 2 * size) {
            int mid = ls + size - 1;
            int right_end = (ls + 2 * size - 1 < n - 1) 
                            ? (ls + 2 * size - 1) 
                            : (n - 1);

            if (mid < right_end)  // Only merge if valid
                merge(arr, ls, mid, right_end);
        }
    }
}

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
