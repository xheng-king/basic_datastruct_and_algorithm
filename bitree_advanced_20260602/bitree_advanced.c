/*
 * File: BiTreeAdvanced.c
 * Purpose: Implement binary tree creation, traversal, node adding, node deleting, threading.
 * Input:  -
 * Output: -
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bitree_node{
    int index;
    struct bitree_node *lchild, *rchild;
    int ltag, rtag;
} bitree_node, *bitree;

int is_thread = 0;

//creat binary tree
bitree creat_bitree();

/*
    find node by index
    the node's address will be saved at *bn
    return -1 when can't find the node
    *bn must be initialized as NULL 
 */
static int find_node(int index, bitree bt, bitree_node **bn);

/*
    add node to binary tree, return 0 when success
    return -1 when tree is empty or parent already has two child nodes
 */
int add_node_to_bitree(int parent_index, int index, bitree bt);


/*
    delete node of binary tree, its child nodes will be deleted as well
    return 0 when delete success
 */
int delete_node_of_bitree(int index, bitree bt);

/*
    inthread the bitree
 */
int creat_inthread(bitree bt);

static int inthread(bitree_node *p, bitree_node **pre);

int inorder_traversal_by_thread(bitree bt);

int inorder_traversal_reversed_by_thread(bitree bt);

int main(){
    char choice;
    bitree bt = creat_bitree();

    printf("Input structure: operation (index) (pindex)\n");
    printf("example:\n");
    printf("add node 2 to node 1: a 2 1\n");
    printf("delete node 2: d 2\n");
    printf("show bitree: s\n");
    printf("thread the bitree: t\n");
    printf("quit: q\n");

    int parent_index, index;
    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                scanf(" %d %d", &index, &parent_index);
                add_node_to_bitree(parent_index, index, bt);
                break;
            case 'd':
                scanf(" %d", &index);
                delete_node_of_bitree(index, bt);
                break;
            case 's':
                inorder_traversal_by_thread(bt);
                inorder_traversal_reversed_by_thread(bt);
                break;
            case 't':
                creat_inthread(bt);
                break;
            case 'q':
                delete_node_of_bitree(1, bt);
                return 0;
                break;
            default:
                printf("Wrong input.\n");
        }
    }
}

bitree creat_bitree(){
    bitree bt = (bitree_node *)malloc(sizeof(bitree_node));
    bt->index = 1;
    bt->lchild = NULL;
    bt->rchild = NULL;
    bt->ltag = 0;
    bt->rtag = 0;
    return bt;
}

static int find_node(int index, bitree bt, bitree_node **bn){
    if(bt == NULL)
        return -1;

    if(bt->index == index){
        *bn = bt;
        return 0;
    }

    find_node(index, bt->lchild, bn);
    find_node(index, bt->rchild, bn);
    if(*bn != NULL)
        return 0;
    else
        return -1;
}

int add_node_to_bitree(int parent_index, int index, bitree bt){
    bitree_node *btn;
    if(find_node(parent_index, bt, &btn) == -1)
        return -1;

    if(btn->index != parent_index)
        return -1;

    if(btn->lchild == NULL){
        btn->lchild = (bitree_node *)malloc(sizeof(bitree_node));
        btn->lchild->index = index;
        btn->lchild->ltag = 0;
        btn->lchild->rtag = 0;
        return 0;
    }else if(btn->rchild == NULL){
        btn->rchild = (bitree_node *)malloc(sizeof(bitree_node));
        btn->rchild->index = index;
        btn->rchild->ltag = 0;
        btn->rchild->rtag = 0;
        return 0;
    }else{
        return -1;
    }
}

static int delete_node_post_order(bitree_node *btn){
    if(is_thread == 1){

        if(btn == NULL)
            return 0;
        if(btn->ltag == 0)
            delete_node_post_order(btn->lchild);
        if(btn->rtag == 0)
            delete_node_post_order(btn->rchild);
        free(btn);

    }else{

        if(btn == NULL)
            return 0;
        delete_node_post_order(btn->lchild);
        delete_node_post_order(btn->rchild);
        free(btn);

    }
    return 0;
}

static int find_parent_node(int index, bitree bt, bitree_node **bn){
    if((bt == NULL) || (bt->lchild == NULL && bt->rchild == NULL))
        return -1;

    if((bt->lchild->index == index) || (bt->rchild->index == index)){
        *bn == bt;
        return 0;
    }

    find_parent_node(index, bt->lchild, bn);
    find_parent_node(index, bt->rchild, bn);
    if(*bn != NULL)
        return 0;
    else
        return -1;
}

int delete_node_of_bitree(int index, bitree bt){
    bitree_node *btn, *parent_btn;
    if(find_node(index, bt, &btn) == -1)
        return -1;
    
    if(find_node(index, bt, &parent_btn) == -1){
        //just delete this node
        delete_node_post_order(btn);
    }else{
        //render the parent child pointer to NULL after delete this node 
        if(parent_btn->lchild == btn)
            parent_btn->lchild == NULL;
        else
            parent_btn->rchild == NULL;
        delete_node_post_order(btn);
    }
    return 0;
}

int creat_inthread(bitree bt){
    if(bt == NULL)
        return -1;
    
    is_thread = 1;
    bitree_node *p = bt, *pre = NULL;
    inthread(p, &pre);
    pre->rtag = 1;
    pre->rchild = NULL;
}

static int inthread(bitree_node *p, bitree_node **pre){
    if(p == NULL)
        return -1;

    inthread(p->lchild, pre);
    
    if(p->lchild == NULL){
        p->ltag = 1;
        p->lchild = *pre;
    }
    if((*pre) != NULL && (*pre)->rchild == NULL){
        (*pre)->rtag = 1;
        (*pre)->rchild = p;
    }
    *pre = p;

    inthread(p->rchild, pre);
}

int inorder_traversal_by_thread(bitree bt){
    if(bt == NULL || is_thread == 0){
        printf("The tree is empty or not inthread bitree.\n");
        return -1;
    }

    bitree_node *p = bt;
    while(p->ltag == 0)
        p = p->lchild; //find the first node in in-order traversal

    printf("In-order sequence: ");
    while(p != NULL){
        printf("%d ", p->index);
        if(p->rtag == 1)
            p = p->rchild;
        else{
            p = p->rchild;
            while(p->ltag == 0)
                p = p->lchild;
        }
    }

    printf("\n");
}

int inorder_traversal_reversed_by_thread(bitree bt){
    if(bt == NULL || is_thread == 0){
        printf("The tree is empty or not inthread bitree.\n");
        return -1;
    }

    bitree_node *p = bt;
    while(p->rtag == 0)
        p = p->rchild; //find the last node in in-order traversal
    
    printf("In-order sequence(reversed): ");
    while(p != NULL){
        printf("%d ", p->index);
        if(p->ltag == 1)
            p = p->lchild;
        else{
            p = p->lchild;
            while(p->rtag == 0)
                p = p->rchild;
        }
    }

    printf("\n");
}