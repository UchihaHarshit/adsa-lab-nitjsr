#include<stdio.h>
int main(){
    int m, n, i, j;
    printf("Enter the number of rows: ");
    scanf("%d", &m);
    printf("\nEnter the number of columns: ");
    scanf("%d", &n);
    int a[m][n] = {0};
    printf("\nEnter the elements of Array:\n");
    for(i = 0; i < n; i++){
        for ( j = 0; j < m; j++){
            scanf("%d", &a[i][j]);
        }
    }
    
    for(i = 0; i < n; i++){ //Printing the array
        printf("\n");
        for ( j = 0; j < m; j++)
        {
            printf("%d ", a[i][j]);
        }
    }
}