/*
 * File: shell_sort_20270731.c
 * Purpose: Sort an integer array in ascending order using the Shell Sort algorithm
 *          (diminishing increment sort). The array uses index 0 as a sentinel,
 *          so valid elements are stored from index 1 to length.
 * Input:   The user is prompted to enter the length of the array, followed by
 *          the array elements (space-separated). The program uses a fixed
 *          increment sequence {5, 3, 1} applied in that exact order.
 * Output:  Prints the sorted array in ascending order, with elements separated
 *          by spaces.
 */

#include <stdio.h>
#include <stdlib.h>

#define DT_SIZE 3

void shell_insert(int arr[], int length, int di){
    for(int i = 1 + di; i <= length; i++){
        if(arr[i] < arr[i - di]){
            arr[0] = arr[i];
            int j;
            for(j = i - di; j >= 0 && arr[0] < arr[j]; j -= di){
                arr[j + di] = arr[j];
            }
            arr[j + di] = arr[0];
        }
    }
}

void shell_sort(int arr[], int length, int d[], int d_length){
    for(int i = 0; i < d_length; i++){
        shell_insert(arr, length, d[i]);
    }
}

int main(){
    int length;
    int dt[DT_SIZE] = {5, 3, 1};
    int t = DT_SIZE;

    printf("input length of array:");
    scanf("%d", &length);

    int *array = (int *)malloc(sizeof(int) * (length+1));
    printf("input array:");
    for(int i = 1; i <= length; i++){
        scanf(" %d", &array[i]);
    }

    shell_sort(array, length, dt, t);

    printf("sorted array:");
    for(int i = 1; i <= length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}