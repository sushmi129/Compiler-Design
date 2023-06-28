#include <stdio.h>
#include <stdlib.h>


void print_stack_content(int stack[], int arr[], int top) {
    printf("Stack content: ");
    for (int i = 0; i <= top; i += 2) {
        int lo = stack[i];
        int hi = stack[i+1];
        printf("[ ");
        for (int j = lo; j <= hi; j++) {
            printf("%d ", arr[j]);
        }
        printf("] ");
    }
    printf("\n");
}

int partition(int arr[], int lo, int hi) {
    int pivot = arr[lo];
    int i = lo;
    for (int j = lo + 1; j <= hi; j++) {
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[lo];
    arr[lo] = arr[i];
    arr[i] = temp;
    printf("(pivot : %d)\n",pivot);
    return i;
}



void quicksort(int arr[], int size) {
    int stack[size];
    int top = -1;
    stack[++top] = 0;
    stack[++top] = size - 1;
    while (top >= 0) {
        int hi = stack[top--];
        int lo = stack[top--];
        if (lo < hi) {
            printf("Array[%d:%d] : ",lo,hi);
            for(int k=lo;k<=hi;k++) {
                printf("%d ",arr[k]);
            }
            int pivot = partition(arr, lo, hi);
            stack[++top] = lo;
            stack[++top] = pivot - 1;
            stack[++top] = pivot + 1;
            stack[++top] = hi;
            print_stack_content(stack, arr, top);
        }
    }
}

int main() {
    int size;
    printf("Enter size of array : ");
    scanf("%d", &size);
    printf("Enter array : ");
    int arr[size];
    for(int i=0;i<size;i++)
    	scanf("%d",&arr[i]);
    quicksort(arr, size);
    printf("\nSorted Array : ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}

/*
OUTPUT :
Enter size of array : 7
Enter array : 8 6 4 1 18 3 9 
Array[0:6] : 8 6 4 1 18 3 9 (pivot : 8)
Stack content: [ 3 6 4 1 ] [ 18 9 ] 
Array[5:6] : 18 9 (pivot : 18)
Stack content: [ 3 6 4 1 ] [ 9 ] [ ] 
Array[0:3] : 3 6 4 1 (pivot : 3)
Stack content: [ 1 ] [ 4 6 ] 
Array[2:3] : 4 6 (pivot : 4)
Stack content: [ 1 ] [ ] [ 6 ] 
*/


