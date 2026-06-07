/*
 * File: disjoint_set_union.c
 * Purpose: Implements a Disjoint Set Union (Union-Find) data structure with
 *          path compression and union by size. Supports finding the root of
 *          an element and merging two sets. The program provides an interactive
 *          command-line interface.
 * Input:   Commands from standard input:
 *          - 'f' followed by an integer index (0 to MAX_SIZE-1): find operation.
 *          - 'u' followed by two integer indices: union operation.
 *          Any other command terminates the program.
 * Output:  For each 'f' command, prints the root of the queried element.
 *          No explicit output for 'u' commands. Errors (e.g., invalid indices
 *          or merging the same set) are not handled in this version; the array
 *          size is fixed to MAX_SIZE = 100.
 */

#include <stdio.h>

#define MAX_SIZE 100

int s[MAX_SIZE];

int initial(int s[]);

int find(int s[], int x);

int merge(int s[], int x, int y);

int main(){
    initial(s);
    char choice;
    int x, y;
    printf("example:\n");
    printf("f 2 - find index 2's root.\n");
    printf("u 1 3 - union set 1 and set 3.\n");
    while(1){
        scanf(" %c", &choice);
        switch (choice)
        {
        case 'f':
            scanf(" %d", &x);
            y = find(s, x);
            printf("%d's root is %d.\n", x, y);
            break;

        case 'u':
            scanf(" %d %d", &x, &y);
            merge(s, x, y);
            break;

        default:
            return 0;
        }
    }
}

int initial(int s[]){
    for(int i = 0; i < MAX_SIZE; i++){
        s[i] = -1;
    }
    return 0;
}

int find(int s[], int x){
    int root = x;
    while(s[root] >= 0)
        root = s[root];

    int tmp;
    while(root != x){
        tmp = s[x]; //save x's parent
        s[x] = root;
        x = tmp;
    }
    return root;
}

int merge(int s[], int root1, int root2){
    if(root1 == root2)
        return -1;

    if(s[root1] <= s[root2]){
        s[root1] += s[root2];
        s[root2] = root1;
    }else{
        s[root2] += s[root1];
        s[root1] = root2;
    }

    return 0;
}