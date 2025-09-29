#include<stdio.h>

int maxValue = 0;

int max(int a, int b){
    return (a>b)?a:b;
}

void knapsackBacktrack(int W, int wt[], int val[], int index, int n, int currentWeight, int currentValue){
    if(index==n){
        if(currentValue > maxValue) maxValue = currentValue;
        return;
    }
    knapsackBacktrack(W, wt, val, index + 1, n, currentWeight, currentValue);
    if(currentWeight + wt[index] <= W)
        knapsackBacktrack(W, wt, val, index + 1, n, currentWeight + wt[index], currentValue + val[index]);
}

int main(){
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int n = sizeof(val)/sizeof(val[0]);
    knapsackBacktrack(W, wt, val, 0, n, 0, 0);
    printf("The maximum value that can be put in the knapsack is: %d\n", maxValue);
}