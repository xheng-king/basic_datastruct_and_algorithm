/*
 * File: binary_insertion_sort_20260723.c
 * Purpose: Sorts an integer array in ascending order using binary insertion sort.
 *          The 0-th element is reserved exclusively as a sentinel (temporary buffer);
 *          valid data elements are stored from index 1 through `length` (inclusive).
 * Input:  A single integer `length`, followed by `length` whitespace-separated integers.
 *         The array capacity is implicitly length + 1 to accommodate the sentinel.
 * Output: The sorted integer sequence, printed in ascending order, separated by spaces,
 *         with a trailing newline.
 */

#include <stdio.h>
#include <stdlib.h>

void insert_sort(int arr[], int length){
    for(int i = 2; i <= length; i++){
        if(arr[i] < arr[i-1]){
            arr[0] = arr[i];
            int low = 1, high = i - 1;
            while(low <= high){
                int m = (low + high) / 2;
                if(arr[m] > arr[0])
                    high = m - 1;
                else
                    low = m + 1;
            }
            for(int j = i-1; j >= high+1; j--){
                arr[j+1] = arr[j];
            }
            arr[high + 1] = arr[0];
        }
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

    insert_sort(array, length);

    printf("sorted array:");
    for(int i = 1; i <= length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}