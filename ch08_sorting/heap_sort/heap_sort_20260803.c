/*
 * File: heap_sort_20260803.c
 * Purpose: Sort an integer array in ascending order using the heap sort algorithm.
 *          The array is treated as a 1-indexed binary heap (index 0 is unused as a temporary swap slot).
 * Input:  An integer length N (N >= 0), followed by N integers to be sorted.
 * Output: The sorted sequence of the N integers, printed in ascending order, separated by spaces.
 */

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;

void heap_adjust(elemtype arr[], int k, int len){
    arr[0] = arr[k];
    for(int i = 2 * k; i <= len; i *= 2){
        if(i < len && arr[i] < arr[i+1])
            i++;
        if(arr[0] > arr[i])
            break;
        else{
            arr[k] = arr[i];
            k = i;
        }
    }
    arr[k] = arr[0];
}

void build_max_heap(elemtype arr[], int len){
    for(int i = len / 2; i > 0; i--){
        heap_adjust(arr, i, len);
    }
}

void heap_sort(elemtype arr[], int len){
    build_max_heap(arr, len);
    for(int i = len; i > 1; i--){
        int tmp = arr[1];
        arr[1] = arr[i];
        arr[i] = tmp;
        heap_adjust(arr, 1, i-1);
    }
}

int main(){
    int length;

    printf("input length of array:");
    scanf("%d", &length);

    int *array = (int *)malloc(sizeof(int) * (length+1));
    printf("input array:");
    for(int i = 1; i <= length; i++){
        scanf(" %d", &array[i]);
    }

    heap_sort(array, length);

    printf("sorted array:");
    for(int i = 1; i <= length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}