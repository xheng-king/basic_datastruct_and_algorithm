/*
 * File: straight_insertion_sort.c
 * Purpose: Sort an integer array in non-decreasing order using straight insertion sort
 *          with a sentinel at index 0 (the actual data starts from index 1).
 * Input:  The user is prompted to enter the length of the array, followed by that
 *         many integers. The length must be a non-negative integer.
 * Output: The sorted array is printed on a single line, with elements separated by spaces.
 */

#include <stdio.h>
#include <stdlib.h>

void insert_sort(int arr[], int length){
    for(int i = 2; i <= length; i++){
        if(arr[i] < arr[i-1]){
            //need insertion
            arr[0] = arr[i];
            arr[i] = arr[i-1];
            int j;
            for(j = i-2; arr[j] > arr[0]; j--){
                arr[j+1] = arr[j];
            }
            arr[j+1] = arr[0];
        }
    }
}

int main(){
    int length = 0;
    
    printf("length of array:");
    scanf("%d", &length);

    int *array = (int *)malloc(sizeof(int) * (length + 1));
    printf("array:");
    for(int i = 1; i <= length; i++){
        scanf(" %d", &array[i]);
    }
    
    insert_sort(array, length);

    printf("sorted:");
    for(int i = 1; i <= length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}