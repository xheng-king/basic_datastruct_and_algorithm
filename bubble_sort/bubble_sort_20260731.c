/*
 * File: bubble_sort_20260731.c
 * Purpose: Sorts an array of integers in ascending order using the bubble sort algorithm.
 * Input:   The user is prompted to enter the length of the array, followed by the integer elements.
 * Output:  Prints the sorted array in one line, with elements separated by spaces.
 */

#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int arr[], int length){
    for(int i = 0; i < length - 1; i++){
        int flag = 0;
        for(int j = length - 1; j > i; j--){
            if(arr[j] < arr[j - 1]){
                int tmp = arr[j];
                arr[j] = arr[j - 1];
                arr[j - 1] = tmp;
                flag = 1;
            }
        }
        if(flag == 0)
            break;
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

    bubble_sort(array, length);

    printf("sorted array:");
    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    free(array);
    return 0;
}