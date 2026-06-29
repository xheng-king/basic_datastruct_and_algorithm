/*
 * File: bitree_advanced_20260602.c
 * Purpose: Implements an advanced binary tree with the following features:
 *          - Dynamic creation of a binary tree (root with index 1).
 *          - In-order threading (converts the tree to a threaded binary tree).
 *          - In-order traversal using the thread pointers (both forward and reverse).
 *          - Add a new node as a left or right child of a given parent (if space available).
 *          - Delete a node and its entire subtree (automatically frees memory).
 *          - Interactive command-line interface for all operations.
 * Input:   Interactive commands from standard input:
 *          - a <index> <parent_index> : add a new node with the given index as a child of parent_index.
 *          - d <index>               : delete the node with the given index and its subtree.
 *          - s                       : show the tree by performing both forward and reverse in-order
 *                                       traversals (works only after threading).
 *          - t                       : thread the current binary tree (in-order threading).
 *          - q                       : quit the program (deletes the entire tree first).
 *          Any other input prints an error message and continues.
 * Output:  - For 's' command: prints the in-order sequence and the reversed in-order sequence
 *            (if the tree has been threaded). If not threaded, prints an error message.
 *          - For invalid commands: "Wrong input."
 *          - No explicit output for 'a', 'd', 't' commands unless an error occurs
 *            (e.g., adding to a full parent or deleting a non‑existent node – but note:
 *            the current implementation lacks error printing for these cases).
 *          - Upon quit, the tree is deallocated silently.
 * Notes:   - The tree uses a fixed root with index 1.
 *          - Threading is global: once threaded (`is_thread = 1`), subsequent deletions
 *            respect thread flags, and traversals require the tree to be threaded.
 *          - The current implementation has several bugs (e.g., `find_parent_node`
 *            incorrectly uses `==` instead of `=`, and deletion after threading may
 *            not handle thread pointers correctly). This header describes the intended
 *            behavior as implied by the code structure.
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