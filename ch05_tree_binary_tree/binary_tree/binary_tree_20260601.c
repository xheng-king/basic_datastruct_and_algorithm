/*
 * File: binary_tree_20260601.c
 * Purpose: Implement binary tree creation, traversal, node adding.
 * Input:  -
 * Output: -
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENTSIZE 100

typedef struct BiTreeNode{
    int index;
    char content[CONTENTSIZE];
    struct BiTreeNode *lchild, *rchild;
    int ltag, rtag;
}BiTreeNode;

int BiTreePreOrderFind(BiTreeNode *p, BiTreeNode **target, int index){
    //Pre-order traversal
    if(p==NULL)
        return -1;

    if(p->index == index)
        *target = p;

    BiTreePreOrderFind(p->lchild, target, index);
    BiTreePreOrderFind(p->rchild, target, index);

    return 0;
}

BiTreeNode* BiTreeFindNode(BiTreeNode *bt, int index){
    BiTreeNode *p = bt;
    BiTreeNode *target = NULL;
    if(p != NULL){
        BiTreePreOrderFind(p, &target, index);
        return target;
    }else{
        return NULL;
    }
}

BiTreeNode* BiTreeAddNode(BiTreeNode *bt){
    int index, pindex;
    char content[CONTENTSIZE];

    printf("Input\"index content (parent's index)\":");
    scanf(" %d %s %d", &index, content, &pindex);

    printf("Your input index is %d, content is %s, pindex is %d\n", index, content, pindex);

    BiTreeNode *p = BiTreeFindNode(bt, pindex);
    if(p == NULL){
        // printf("1\n");
        p = (BiTreeNode *)malloc(sizeof(BiTreeNode));
        p->index = index;
        p->lchild = NULL;
        p->rchild = NULL;
        p->ltag = 0;
        p->rtag = 0;
        strcpy(p->content, content);
        return p;
    }else{
        if(p->lchild == NULL){
            p->lchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
            p->lchild->index = index;
            p->lchild->lchild = NULL;
            p->lchild->rchild = NULL;
            p->lchild->ltag = 0;
            p->lchild->rtag = 0;
            strcpy(p->lchild->content, content);
        }else if(p->rchild == NULL){
            p->rchild = (BiTreeNode *)malloc(sizeof(BiTreeNode));
            p->rchild->index = index;
            p->rchild->lchild = NULL;
            p->rchild->rchild = NULL;
            p->rchild->ltag = 0;
            p->rchild->rtag = 0;
            strcpy(p->rchild->content, content);
        }else{
            printf("The parent is full of child.\n");
        }
    }
    return bt;
}

int BiTreePreOrderTraversal(BiTreeNode *bt){
    if(bt == NULL)
        return -1;
    printf("%d ", bt->index);
    BiTreePreOrderTraversal(bt->lchild);
    BiTreePreOrderTraversal(bt->rchild);
}

int BiTreeInOrderTraversal(BiTreeNode *bt){
    if(bt == NULL)
        return -1;
    
    BiTreeInOrderTraversal(bt->lchild);
    printf("%d ", bt->index);
    BiTreeInOrderTraversal(bt->rchild);
}

int BiTreeShow(BiTreeNode *bt){
    if(bt == NULL)
        return -1;

    //Pre-Order
    printf("Pre-Order:");
    BiTreePreOrderTraversal(bt);
    printf("\n");
    //In-Order
    printf("In-Order:");
    BiTreeInOrderTraversal(bt);
    printf("\n");

    return 0;
}

int main(){
    int choice;
    BiTreeNode *bt = NULL;

    while(1){
        printf("Input choice:\n");
        printf("1 to add node.\n");
        printf("2 to show bitree.\n");
        printf("3 to quit.\n");

        scanf(" %d", &choice);
        switch(choice){
            case 1:
                bt = BiTreeAddNode(bt);
                break;
            case 2:
                BiTreeShow(bt);
                break;
            default:
                return 0;
        }
    }
}