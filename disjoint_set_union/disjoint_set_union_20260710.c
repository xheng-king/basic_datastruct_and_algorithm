/*
 * File: disjoint_set_union_20260710.c
 * Purpose: Implement a disjoint-set union (union-find) data structure
 *          with path compression and union by size, and demonstrate its
 *          usage on a small set of 10 elements.
 * Input:  None (hard-coded test sequence inside main).
 * Output: Prints the root of selected elements after initial merges,
 *         and lists all current roots with their set sizes after further
 *         unions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *init_set(int len){
    int *set = (int *)malloc(len * sizeof(int));
    for(int i = 0; i < len; i++)
        set[i] = -1;
    return set;
}

int find(int set[], int len, int x){
    int root = x;
    while(set[root] >= 0)
        root = set[root];
    
    int current = x, next;
    while(current != root){
        next = set[current];
        set[current] = root;
        current = next;
    }

    return root;
}

void merge(int set[], int len, int x, int y){
    int x_root = find(set, len, x);
    int y_root = find(set, len, y);

    if(set[x_root] > set[y_root]){
        set[y_root] += set[x_root];
        set[x_root] = y_root;
    }else{
        set[x_root] += set[y_root];
        set[y_root] = x_root;
    }
}

int main() {
    int n = 10;
    int *set = init_set(n);

    // 初始合并：将 (0,1), (2,3), (4,5), (6,7), (8,9) 分别合并
    merge(set, n, 0, 1);
    merge(set, n, 2, 3);
    merge(set, n, 4, 5);
    merge(set, n, 6, 7);
    merge(set, n, 8, 9);

    // 查找各元素的根（路径压缩）
    printf("find(0) = %d\n", find(set, n, 0));
    printf("find(2) = %d\n", find(set, n, 2));

    // 合并两个不同的集合：将 (0,1) 和 (2,3) 合并，再将 (4,5) 和 (6,7) 合并
    merge(set, n, 1, 2);   // 现在集合 {0,1,2,3}
    merge(set, n, 5, 6);   // 现在集合 {4,5,6,7}

    // 输出当前所有根节点及其集合大小（根节点的 set[i] 为负数，绝对值即大小）
    printf("\n当前集合信息：\n");
    for (int i = 0; i < n; i++) {
        if (set[i] < 0) {
            printf("  根 %d，集合大小 %d\n", i, -set[i]);
        }
    }

    // 释放内存
    free(set);
    return 0;
}