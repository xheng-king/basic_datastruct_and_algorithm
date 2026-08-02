/*
 * File: select_sort_20260802.c
 * Purpose: Implements selection sort algorithm to sort an integer array in ascending order.
 * Input:   User provides the length of the array, then enters that many integers.
 * Output:  Prints the sorted array elements separated by spaces, followed by a newline.
 */

#include <stdio.h>
#include <stdlib.h>

typedef int elemtype;

void select_sort(elemtype arr[], int length){
    for(int i = 0; i < length - 1; i++){
        int min = i;
        for(int j = i + 1; j < length; j++){
            if(arr[j] < arr[min])
                min = j;
        }
        if(min != i){
            int tmp = arr[min];
            arr[min] = arr[i];
            arr[i] = tmp;
        }
    }
}

int main(){
    int length;

    printf("input length of array:");
    scanf("%d", &length);

    int *array = (int *)malloc(sizeof(int) * (length));
    printf("input array:");
    for(int i = 0; i < length; i++){
        scanf(" %d", &array[i]);
    }

    select_sort(array, length);

    printf("sorted array:");
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}