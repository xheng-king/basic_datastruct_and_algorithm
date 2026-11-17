/*
 * File: merge_sort_20260831.c
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
    for(i = low; i <= high; i++)
        b[i] = arr[i];

    for(i = low, j = mid+1, k = low; i <= mid && j <= high; ){
        if(b[j] < b[i])
            arr[k++] = b[j++];
        else
            arr[k++] = b[i++];
    }

    while(i <= mid)
        arr[k++] = b[i++];
    while(j <= high)
        arr[k++] = b[j++];
}

void merge_sort(elemtype arr[], int low, int high){
    if(low < high){
        int mid = (low + high) / 2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid + 1, high);
        merge(arr, low, mid, high);
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