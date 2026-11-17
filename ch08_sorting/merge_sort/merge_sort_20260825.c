/*
 * File: merge_sort_20260825.c
 * Purpose: Implement the merge sort algorithm to sort an array of integers
 *          in non-decreasing order using a divide-and-conquer approach.
 * Input:   The user is prompted to enter the length of the array (positive integer),
 *          followed by that many integer elements separated by whitespace.
 * Output:  The sorted array is printed to the standard output, with elements
 *          separated by spaces and followed by a newline.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
typedef int elemtype;

elemtype b[MAX_SIZE];

void merge(elemtype arr[], int low, int mid, int high){
    int i, j, k;
    for(k = low; k <= high; k++)
        b[k] = arr[k];

    for(i = low, k = i, j = mid + 1; i <= mid && j <= high; k++){
        if(b[i] <= b[j])
            arr[k] = b[i++];
        else
            arr[k] = b[j++];
    }

    while(i <= mid)
        arr[k++] = b[i++];
    while(j <= high)
        arr[k++] = b[j++];
}

void merge_sort(elemtype arr[], int low, int high){
    if(low < high){
        int m = (low + high) / 2;
        merge_sort(arr, low, m);
        merge_sort(arr, m+1, high);
        merge(arr, low, m, high);
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

    merge_sort(array, 0, length - 1);

    printf("sorted array:");
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}