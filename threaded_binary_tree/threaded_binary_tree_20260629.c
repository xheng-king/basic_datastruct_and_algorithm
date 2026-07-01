/*
 * File: threaded_binary_tree.c
 * Purpose: Implements an in-order threaded binary tree with operations to 
 *          create, add nodes, delete the entire tree, thread the tree, and 
 *          perform both forward and reverse in-order traversals using threads.
 * Input:   Interactive commands from standard input:
 *          - 'c' : create an empty tree.
 *          - 'a' <index> <parent_index> <is_left_child> : add a new node 
 *               with given index as left (1) or right (0) child of parent.
 *          - 'd' : delete the entire tree (argument ignored).
 *          - 't' : thread the current binary tree (in-order).
 *          - 's' : display both forward and reverse in-order traversals 
 *               (must be threaded first).
 *          - other : quit the program.
 * Output:  Prints traversal results (node indices separated by spaces) when 
 *          's' is issued; otherwise prompts for commands and confirms exit.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bitree_node{
    int index;
    struct bitree_node *lchild, *rchild;
    int ltag, rtag;
}bitree_node;

typedef struct bitree{
    bitree_node *root;
}bitree;

bitree *init_tree(void){
    bitree *tree = (bitree *)malloc(sizeof(bitree));
    tree->root = NULL;
    return tree;
}

bitree_node *find_node(bitree_node *current, int index){
    if(current == NULL || current->index == index)
        return current;

    bitree_node *result = find_node(current->lchild, index);
    if(result)
        return result;
    
    result = find_node(current->rchild, index);
    if(result)
        return result;

    return NULL;
}

void add_node(bitree *t, int index, int parent_index, int is_lchild){
    if(t == NULL)
        return;
    bitree_node *new_node = (bitree_node *)malloc(sizeof(bitree_node));
    new_node->index = index;
    new_node->lchild = NULL;
    new_node->rchild = NULL;
    new_node->ltag = 0;
    new_node->rtag = 0;

    if(t->root == NULL)
        t->root = new_node;
    else{
        bitree_node *parent = find_node(t->root, parent_index);
        if(parent == NULL)
            return;
        if(is_lchild)
            parent->lchild = new_node;
        else
            parent->rchild = new_node;
    }
}


void delete_node(bitree_node *node){
    if(node != NULL){
        delete_node(node->lchild);
        delete_node(node->rchild);
        free(node);
    }
}

void delete_tree(bitree *bt){
    /* if this tree is threaded,
     *  the function will fail and incur segment fault
     */
    if(bt != NULL)
        delete_node(bt->root);
}

void inthread(bitree_node *p, bitree_node **pre_address){
    if(p != NULL){
        inthread(p->lchild, pre_address);
        if(p->lchild == NULL){
            p->ltag = 1;
            p->lchild = *pre_address;
        }if(*pre_address != NULL && (*pre_address)->rchild == NULL){
            (*pre_address)->rchild = p;
            (*pre_address)->rtag = 1;
        }
        *pre_address = p;
        inthread(p->rchild, pre_address);
    }
}

void creat_inthread(bitree *t){
    if(t == NULL)
        return;
    bitree_node *pre = NULL;
    if(t->root != NULL){
        inthread(t->root, &pre);
        pre->rtag = 1;
    }
}

bitree_node *first_node(bitree_node *root){
    bitree_node *p = root;
    while(p->ltag == 0)
        p = p->lchild;
    return p;
}

bitree_node *next_node(bitree_node *current){
    if(current->rtag)
        return current->rchild;
    else
        return first_node(current->rchild);
}

void inorder_traversal_by_thread(bitree *bt){
    if(bt != NULL){
        bitree_node *current = first_node(bt->root);
        for(; current != NULL; current = next_node(current)){
            printf("%d ", current->index);
        }
        printf("\n");
    }
}

bitree_node *last_node(bitree_node *root){
    bitree_node *p = root;
    while(p->rtag == 0)
        p = p->rchild;
    return p;
}

bitree_node *next_node_reverse(bitree_node *current){
    if(current->ltag == 1)
        return current->lchild;
    else
        return last_node(current->lchild);
}

void inorder_traversal_reversed_by_thread(bitree *bt){
    if(bt != NULL){
        for(bitree_node *current = last_node(bt->root); current != NULL;
            current = next_node_reverse(current)){
                printf("%d ", current->index);
            }
        printf("\n");
    }
}


int main(){
    char choice;
    bitree *bt = NULL;
    printf("Input structure: operation (index) (pindex)\n");
    printf("example:\n");
    printf("creat empty tree: c");
    printf("add node 2 as node 1's left child: a 2 1 1\n");
    printf("add node 3 as node 2's right child: a 3 2 0\n");
    printf("delete tree: d\n");
    printf("show bitree: s\n");
    printf("thread the bitree: t\n");
    printf("quit: q\n");

    int parent_index, index, is_left_child;
    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                scanf(" %d %d %d", &index, &parent_index, &is_left_child);
                add_node(bt, index, parent_index, is_left_child);
                break;
            case 'c':
                bt = init_tree();
                break;
            case 'd':
                scanf(" %d", &index);
                delete_tree(bt);
                bt = NULL;
                break;
            case 's':
                inorder_traversal_by_thread(bt);
                inorder_traversal_reversed_by_thread(bt);
                break;
            case 't':
                creat_inthread(bt);
                break;
            default:
                printf("bye!\n");
                return 0;
        }
    }
}
