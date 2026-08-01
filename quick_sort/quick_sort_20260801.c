/*
 * File: quick_sort_20260801.c
 * Purpose: Sort an integer array in ascending order using the Quick Sort algorithm
 *          (recursive implementation with in-place partitioning).
 * Input:   The user is prompted to enter the length of the array, followed by the
 *          array elements (integers) one by one.
 * Output:  The sorted array is printed to the standard output, with each element
 *          separated by a space.
 */

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;

int partition(elemtype arr[], int low, int high){
    elemtype pivot = arr[low];
    while(low < high){
        while(low < high && arr[high] >= pivot)
            high--;
        arr[low] = arr[high];
        while(low < high && arr[low] <= pivot)
            low++;
        arr[high] = arr[low];
    }
    arr[low] = pivot;
    return low;
}

void quick_sort(elemtype arr[], int low, int high){
    if(low < high){
        int pivot_pos = partition(arr, low, high);
        quick_sort(arr, low, pivot_pos - 1);
        quick_sort(arr, pivot_pos + 1, high);
    }
}

int main(){
    int length;

    printf("input length of array:");
    scanf("%d", &length);

    elemtype *array = (elemtype *)malloc(sizeof(elemtype) * (length));
    printf("input array:");
    for(int i = 0; i < length; i++){
        scanf(" %d", &array[i]);
    }

    quick_sort(array, 0, length - 1);

    printf("sorted array:");
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}