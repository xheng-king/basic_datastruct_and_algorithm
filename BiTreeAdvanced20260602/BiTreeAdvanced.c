/*
 * File: BiTreeAdvanced.c
 * Purpose: Implement binary tree creation, traversal, node adding, node deleting, threading.
 * Input:  -
 * Output: -
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENT_SIZE 100;

typedef struct bitree_node{
    int index;
    struct bitree_node *lchild, *rchild;
    int ltag, rtag;
    char content[CONTENT_SIZE];
} bitree_node, *bitree;

//creat binary tree
bitree creat_bitree();

/*
    find node by index
    the node's address will be saved at *bn
    return -1 when can't find the node
 */
static int find_node(int index, bitree bt, bitree_node **bn);

/*
    add node to binary tree, return 0 when success
    return -1 when tree is empty or parent already has two child nodes
 */
int add_node_to_bitree(int parent_index, int index, char *content, bitree bt);


/*
    delete node of binary tree, its child nodes will be deleted as well
    return 0 when delete success
 */
int delete_node_of_bitree(int index, bitree bt);

/*
    thread the bitree
 */
int thread_bitree(bitree bt);

int main(){

}