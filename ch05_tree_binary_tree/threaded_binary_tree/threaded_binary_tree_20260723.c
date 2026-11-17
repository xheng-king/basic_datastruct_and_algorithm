/*
 * File: threaded_binary_tree_20260723.c
 * Purpose: Build a binary tree from a level-order array representation (with -1 
 *          for empty nodes), convert it to an in-order threaded binary tree, 
 *          and then traverse it using the thread links to print the in-order 
 *          sequence.
 * Input:   A sequence of integers terminated by -2. Each integer before -2 
 *          represents a node value in level order; -1 denotes an empty node. 
 *          The first integer is the root. The sequence is read until -2 is 
 *          encountered.
 * Output:  The in-order traversal sequence of the threaded binary tree, 
 *          printed as a single line of space-separated values.
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_NUM 100

typedef struct bitree_node{
    int index;
    int ltag, rtag;
    struct bitree_node *lchild, *rchild;
}bitree_node;

bitree_node *creat_tree(int node[], int length, int current){
    //pre-order
    if(current > length || node[current] == -1)
        return NULL;
    
    bitree_node *new_node = (bitree_node *)malloc(sizeof(bitree_node));
    new_node->index = node[current];
    new_node->ltag = 0;
    new_node->rtag = 0;

    new_node->lchild = creat_tree(node, length, current*2);
    new_node->rchild = creat_tree(node, length, current*2+1);

    return new_node;
}

void inthread(bitree_node *current, bitree_node **pre){
    if(current != NULL){
        inthread(current->lchild, pre);
        if(current->lchild == NULL){
            current->lchild = *pre;
            current->ltag = 1;
        }
        if((*pre) != NULL && (*pre)->rchild == NULL){
            (*pre)->rchild = current;
            (*pre)->rtag = 1;
        }
        *pre = current;
        inthread(current->rchild, pre);
    }
}

void creat_inthread(bitree_node *root){
    bitree_node *pre = NULL;
    inthread(root, &pre);
    pre->rtag = 1;
}

bitree_node *first_node(bitree_node *root){
    bitree_node *p = root;
    while(p->ltag == 0)
        p = p->lchild;
    return p;
}

bitree_node *next_node(bitree_node *current){
    if(current->rtag == 1)
        return current->rchild;
    else
        return first_node(current->rchild);
}

void inorder_traverse(bitree_node *root){
    if(root != NULL){
        for(bitree_node *p = first_node(root); p != NULL; p = next_node(p)){
            printf("%d ", p->index);
        }
    }
}

void delete_tree(bitree_node *root){
    //post-order
    if(root != NULL){
        if(root->ltag == 0)
            delete_tree(root->lchild);
        if(root->rtag == 0)
            delete_tree(root->rchild);
        free(root);
    }
}

int main() {
    int length = 0;
    int node[MAX_NODE_NUM];
    int x;

    printf("input binary tree with Array Representation(-2 to end, -1 as empty node):\n");
    scanf("%d", &x);
    while(x != -2){
        node[++length] = x;
        scanf(" %d", &x);
    }
    bitree_node *root = creat_tree(node, length, 1);
    creat_inthread(root);
    inorder_traverse(root);
    delete_tree(root);

    return 0;
}