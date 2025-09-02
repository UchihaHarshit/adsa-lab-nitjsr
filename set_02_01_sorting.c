#include<stdio.h>
#include<stdlib.h>

void swap(int* x, int* y){
    int temp = *x;
    *x = *y;
    *y = temp;
}

void insertionSort(int arr[], int n){
        for (int i = 1; i < n; ++i) {
        int key = arr[i];
        for(int j = i - 1; j >= 0 && arr[j] > key; --j) {
            arr[j + 1] = arr[j];
            arr[j] = key;
        }
    }
}


void bubbleSort(int arr[], int n){
    int i = 0, j = 0;
    for(i = 0; i < n-1; i++){
        for(j = 0; j < n-i-1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}


void selectionSort(int arr[], int n){
    int i = 0, j = 0;
    for(i = 0; i < n-1; i++){
        int minIndex= i;
        for(j = i + 1; j < n; j++){
            if(arr[j] < arr[minIndex]){
                minIndex = j;
            }
        }
        swap(&arr[i], &arr[minIndex]);
    }
}


void shellSort(int arr[], int n){
    int gap, i, j, temp;
    for(gap = n/2; gap > 0; gap /= 2){
        for(i = gap; i < n; i++){
            temp = arr[i];
            for(j = i; j >= gap && arr[j - gap] > temp; j -= gap){
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}


void quickSort(int arr[], int start, int end){
    if(start < end){
        int pivot = arr[end];
        int i = (start - 1);
        for(int j = start; j <= end - 1; j++){
            if(arr[j] < pivot){
                i++;
                swap(&arr[i], &arr[j]);
            }
        }
        swap(&arr[i + 1], &arr[end]);
        int pi = i + 1;
        quickSort(arr, start, pi - 1);
        quickSort(arr, pi + 1, end);
    }
}


void mergeSort(int arr[], int start, int end){
    if(start < end){
        int mid = start + (end - start) / 2;
        mergeSort(arr, start, mid);
        mergeSort(arr, mid + 1, end);
        int i, j, k;
        int n1 = mid - start + 1;
        int n2 = end - mid;
        int L[n1], R[n2];
        for(i = 0; i < n1; i++){
            L[i] = arr[start + i];
        }
        for(j = 0; j < n2; j++){
            R[j] = arr[mid + 1 + j];
        }
        i = 0;
        j = 0;
        k = start;
        while(i < n1 && j < n2){
            if(L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest]){
        largest = left;
    }
    if(right < n && arr[right] > arr[largest]){
        largest = right;
    }
    if(largest != i){
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}


void heapSort(int arr[], int n){
    int i;
    for(i = n / 2 - 1; i >= 0; i--){
        heapify(arr, n, i);
    }
    for(i = n - 1; i >= 0; i--){
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

}

int findMax(int arr[], int n){
    int max = arr[0];
    for(int i = 1; i < n; i++){
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
}


void radixSort(int arr[], int n){
    int max = findMax(arr, n);
    for(int exp = 1; max/exp > 0; exp *= 10){
        int output[n];
        int count[10] = {0};
        for(int i = 0; i < n; i++){
            count[(arr[i]/exp)%10]++;
        }
        for(int i = 1; i < 10; i++){
            count[i] += count[i - 1];
        }
        for(int i = n - 1; i >= 0; i--){
            output[count[(arr[i]/exp)%10] - 1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }
        for(int i = 0; i < n; i++){
            arr[i] = output[i];
        }
    }

}


void countingSort(int arr[], int n){
    int max = findMax(arr, n);
    int count[max + 1];
    for(int i = 0; i <= max; i++){
        count[i] = 0;
    }
    for(int i = 0; i < n; i++){
        count[arr[i]]++;
    }
    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }
    int output[n];
    for(int i = n - 1; i >= 0; i--){
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }
    for(int i = 0; i < n; i++){
        arr[i] = output[i];
    }

}


void bucketSort(int arr[], int n){
    int max = findMax(arr, n);
    int bucket[max + 1];
    for(int i = 0; i <= max; i++){
        bucket[i] = 0;
    }
    for(int i = 0; i < n; i++){
        bucket[arr[i]]++;
    }
    int index = 0;
    for(int i = 0; i <= max; i++){
        while(bucket[i] > 0){
            arr[index++] = i;
            bucket[i]--;
        }
    }

}


int getBit(int num, int bit) {
    return (num >> bit) & 1;
}


void radixExchangeSort(int arr[], int left, int right, int bit){
    if (left >= right || bit < 0) {
        return;
    }

    int i = left;
    int j = right;

    // Partition step based on the current bit
    while (i <= j) {
        while (i <= j && getBit(arr[i], bit) == 0) {
            i++;
        }
        while (i <= j && getBit(arr[j], bit) == 1) {
            j--;
        }
        if (i < j) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
            j--;
        }
    }

    // Recurse on left and right partitions
    radixExchangeSort(arr, left, j, bit - 1);
    radixExchangeSort(arr, i, right, bit - 1);
}

void addressCalculationSort(int arr[], int n) {
    int max = arr[0];
    for(int i = 1; i < n; i++) {
        if(arr[i] > max) {
            max = arr[i];
        }
    }

    int M = max / n;
    if((max - n*M) > (n*(M+1) - max)) {
        M = M + 1;
    }

    // Create buckets
    int *address[n];      // array of pointers to buckets
    int bucketSize[n];    // number of elements in each bucket
    for(int i = 0; i < n; i++) {
        address[i] = (int*)malloc(n * sizeof(int));
        bucketSize[i] = 0;
    }

    // Insert elements into buckets
    for(int i = 0; i < n; i++) {
        int index = arr[i] / M;
        if(index >= n) index = n-1; // prevent overflow
        address[index][bucketSize[index]++] = arr[i];
    }

    // Sort each bucket
    for(int i = 0; i < n; i++) {
        for(int j = 1; j < bucketSize[i]; j++) {
            int key = address[i][j];
            int k = j - 1;
            while(k >= 0 && address[i][k] > key) {
                address[i][k+1] = address[i][k];
                k--;
            }
            address[i][k+1] = key;
        }
    }

    // Step 6: Gather back into original array
    int idx = 0;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < bucketSize[i]; j++) {
            arr[idx++] = address[i][j];
        }
        free(address[i]);
    }
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", arr[i]);
    }
}

void createArray(int dest[], int src[], int n) {
    for(int i = 0; i < n; i++) {
        dest[i] = src[i];
    }
}

int main() {
    int original[] = {29, 25, 3, 49, 9, 37, 21, 43};
    int n = sizeof(original) / sizeof(original[0]);
    int choice;

    printf("Choose Sorting Algorithm:\n");
    printf("1. Insertion Sort\n");
    printf("2. Bubble Sort\n");
    printf("3. Selection Sort\n");
    printf("4. Shell Sort\n");
    printf("5. Quick Sort\n");
    printf("6. Merge Sort\n");
    printf("7. Heap Sort\n");
    printf("8. Radix Sort\n");
    printf("9. Counting Sort\n");
    printf("10. Bucket Sort\n");
    printf("11. Radix Exchange Sort\n");
    printf("12. Address Calculation Sort\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int arr[n];
    createArray(arr, original, n);

    switch(choice) {
        case 1:
            insertionSort(arr, n);
            printf("Insertion Sort: ");
            break;
        case 2:
            bubbleSort(arr, n);
            printf("Bubble Sort: ");
            break;
        case 3:
            selectionSort(arr, n);
            printf("Selection Sort: ");
            break;
        case 4:
            shellSort(arr, n);
            printf("Shell Sort: ");
            break;
        case 5:
            quickSort(arr, 0, n - 1);
            printf("Quick Sort: ");
            break;
        case 6:
            mergeSort(arr, 0, n - 1);
            printf("Merge Sort: ");
            break;
        case 7:
            heapSort(arr, n);
            printf("Heap Sort: ");
            break;
        case 8:
            radixSort(arr, n);
            printf("Radix Sort: ");
            break;
        case 9:
            countingSort(arr, n);
            printf("Counting Sort: ");
            break;
        case 10:
            bucketSort(arr, n);
            printf("Bucket Sort: ");
            break;
        case 11: {
            int max = findMax(arr, n);
            int maxBits = 0;
            while(max > 0) {
                maxBits++;
                max >>= 1;
            }
            radixExchangeSort(arr, 0, n - 1, maxBits - 1);
            printf("Radix Exchange Sort: ");
            break;
        }
        case 12:
            addressCalculationSort(arr, n);
            printf("Address Calculation Sort: ");
            break;
        default:
            printf("Invalid choice!\n");
            return 0;
    }

    printArray(arr, n);
    return 0;
}


