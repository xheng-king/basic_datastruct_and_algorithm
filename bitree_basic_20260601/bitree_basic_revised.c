/*
 * File: BiTree_revised.c
 * Purpose: Binary tree creation, traversal, and node insertion (improved version).
 *          Fixed add-node logic, code style, and memory management.
 * Input:  User commands
 * Output: Tree traversals
 * Improvements over original:
 * 错误：添加节点时若父节点不存在会错误地创建孤立节点并丢失原树
 *       缺少必要的 static 修饰内部函数
 * 优化：增加严格检查：树空时只有父索引为 -1 才能创建根；父节点不存在或已满时拒绝添加
 * 总结：思想掌握，数据结构能用就行，生产环境再写更加安全稳定的数据结构
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CONTENTSIZE 100

typedef struct BiTreeNode {
    int index;                         // Node identifier
    char content[CONTENTSIZE];         // Node content
    struct BiTreeNode *lchild, *rchild; // Left and right children
    int ltag, rtag;                    // Threading tags (reserved for future use)
} BiTreeNode;

/* Recursive helper to find a node by index (pre-order traversal) */
static BiTreeNode* findNodePreOrder(BiTreeNode *node, int index) {
    if (node == NULL)
        return NULL;
    if (node->index == index)
        return node;

    BiTreeNode *found = findNodePreOrder(node->lchild, index);
    if (found != NULL)
        return found;
    return findNodePreOrder(node->rchild, index);
}

/* Public function: find a node by index in the binary tree */
BiTreeNode* BiTreeFindNode(BiTreeNode *root, int index) {
    return findNodePreOrder(root, index);
}

/* Create a new node with given index and content */
static BiTreeNode* createNode(int index, const char *content) {
    BiTreeNode *newNode = (BiTreeNode*)malloc(sizeof(BiTreeNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->index = index;
    strcpy(newNode->content, content);
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    newNode->ltag = 0;
    newNode->rtag = 0;
    return newNode;
}

/* Add a node to the binary tree.
   - For the root node, use parent_index = -1.
   - Returns the root of the tree (unchanged if insertion fails). */
BiTreeNode* BiTreeAddNode(BiTreeNode *root) {
    int index, parentIndex;
    char content[CONTENTSIZE];

    printf("Input \"index content parent_index\": ");
    scanf(" %d %s %d", &index, content, &parentIndex);
    printf("Your input: index=%d, content=%s, parent_index=%d\n", index, content, parentIndex);

    /* Case: empty tree – only allow root creation with parent_index = -1 */
    if (root == NULL) {
        if (parentIndex == -1) {
            root = createNode(index, content);
            printf("Root node added.\n");
        } else {
            printf("Error: Tree is empty. To create root, set parent index = -1.\n");
        }
        return root;
    }

    /* Non‑empty tree: find parent */
    BiTreeNode *parent = BiTreeFindNode(root, parentIndex);
    if (parent == NULL) {
        printf("Error: Parent node with index %d not found.\n", parentIndex);
        return root;
    }

    /* Check if parent already has two children */
    if (parent->lchild != NULL && parent->rchild != NULL) {
        printf("Error: Parent node (index %d) already has two children.\n", parentIndex);
        return root;
    }

    /* Create and attach the new node */
    BiTreeNode *newNode = createNode(index, content);
    if (parent->lchild == NULL) {
        parent->lchild = newNode;
        printf("Node added as left child of %d.\n", parentIndex);
    } else {
        parent->rchild = newNode;
        printf("Node added as right child of %d.\n", parentIndex);
    }

    return root;
}

/* Pre-order traversal (recursive) */
static void preOrderTraversal(BiTreeNode *node) {
    if (node == NULL)
        return;
    printf("%d ", node->index);
    preOrderTraversal(node->lchild);
    preOrderTraversal(node->rchild);
}

/* In-order traversal (recursive) */
static void inOrderTraversal(BiTreeNode *node) {
    if (node == NULL)
        return;
    inOrderTraversal(node->lchild);
    printf("%d ", node->index);
    inOrderTraversal(node->rchild);
}

/* Display the tree using pre-order and in-order traversals */
void BiTreeShow(BiTreeNode *root) {
    if (root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printf("Pre-order: ");
    preOrderTraversal(root);
    printf("\n");
    printf("In-order:  ");
    inOrderTraversal(root);
    printf("\n");
}

/* Free all nodes of the tree (post-order) */
void BiTreeFree(BiTreeNode *root) {
    if (root == NULL)
        return;
    BiTreeFree(root->lchild);
    BiTreeFree(root->rchild);
    free(root);
}

int main() {
    int choice;
    BiTreeNode *root = NULL;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add node\n");
        printf("2. Show tree\n");
        printf("3. Quit\n");
        printf("Your choice: ");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                root = BiTreeAddNode(root);
                break;
            case 2:
                BiTreeShow(root);
                break;
            case 3:
                BiTreeFree(root);
                printf("Exiting. Memory freed.\n");
                return 0;
            default:
                printf("Invalid choice. Please enter 1, 2, or 3.\n");
                break;
        }
    }
}