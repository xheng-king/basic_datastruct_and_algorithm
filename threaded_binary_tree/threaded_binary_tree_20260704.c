/*
 * File: threaded_binary_tree_20260704.c
 * Purpose: Build a binary tree from a complete binary tree level-order array
 *          (with -1 for empty nodes), then convert it to an in-order threaded
 *          binary tree, and finally traverse it using the thread links.
 * Input:  An integer n (number of array elements, including placeholders),
 *         followed by n integers representing the complete binary tree in
 *         level order, where -1 denotes an empty node. The first integer
 *         is the root.
 * Output: The in-order traversal sequence of the threaded tree, printed
 *         as a single line of space-separated values.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define EMPTY -1

int is_threaded = 0;

typedef struct tree_node{
    int val;
    struct tree_node *left, *right;
    int left_tag, right_tag;
}tree_node;

tree_node *build_tree(int arr[], int n, int index){
    if(index >= n || arr[index] == EMPTY){
        return NULL;
    }

    tree_node *node = (tree_node *)malloc(sizeof(tree_node));

    node->val = arr[index];

    node->left_tag = 0;
    node->right_tag = 0;

    node->left = build_tree(arr, n, 2*index);
    node->right = build_tree(arr, n, 2*index+1);

    return node;
}

void preorder_traversal(tree_node *root){
    if(root != NULL){
        printf("%d ", root->val);
        preorder_traversal(root->left);
        preorder_traversal(root->right);
    }
}

void inorder_thread(tree_node *p, tree_node **pre){
    if(p != NULL){
        inorder_thread(p->left, pre);
        if(p->left == NULL){
            p->left = *pre;
            p->left_tag = 1;
        }
        if((*pre) != NULL && (*pre)->right == NULL){
            (*pre)->right = p;
            (*pre)->right_tag = 1;
        }
        *pre = p;
        inorder_thread(p->right, pre);
    }
}

void creat_inorder_thread(tree_node *root){
    tree_node *pre = NULL;
    if(root){
        inorder_thread(root, &pre);
        pre->right_tag = 1;
    }
    is_threaded = 1;
}

tree_node *first_node(tree_node *root){
    tree_node *current = root;
    while(current->left_tag == 0)
        current = current->left;
    return current;
}

tree_node *next_node(tree_node *root){
    if(root->right_tag)
        return root->right;
    else
        return first_node(root->right);
}

void inorder_traverse_by_thread(tree_node *root){
    for(tree_node *p = first_node(root); p != NULL; p = next_node(p)){
        printf("%d ", p->val);
    }
    printf("\n");
}

void delete_tree(tree_node *root){
    if(is_threaded){
        for(tree_node *p = first_node(root); p != NULL;){
            tree_node *next = next_node(p);
            free(p);
            p = next;
        }
    }else if(root != NULL){
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

int main() {
    int n;
    printf("请输入完全二叉树数组长度（包含空节点占位，用 -1 表示）：");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("输入无效。\n");
        return 0;
    }

    // 分配数组，下标 0 不使用，有效下标为 1 ~ n
    int *arr = (int *)malloc((n + 1) * sizeof(int));
    if (arr == NULL) {
        printf("内存分配失败。\n");
        return 1;
    }
    arr[0] = EMPTY;  // 占位，不会被访问

    printf("请输入 %d 个整数（-1 表示空节点），从根开始按层序输入：\n", n);
    for (int i = 1; i <= n; i++) {
        if (scanf("%d", &arr[i]) != 1) {
            printf("输入错误。\n");
            free(arr);
            return 1;
        }
    }

    // 建树：根索引为 1，数组实际长度为 n+1
    tree_node *root = build_tree(arr, n + 1, 1);

    if (root == NULL) {
        printf("空树，无需线索化。\n");
    } else {
        // 中序线索化
        creat_inorder_thread(root);

        // 输出中序线索遍历结果
        printf("中序线索遍历结果：");
        inorder_traverse_by_thread(root);

        // 释放内存（根据 is_threaded 采用不同释放方式）
        delete_tree(root);
    }

    free(arr);
    return 0;
}