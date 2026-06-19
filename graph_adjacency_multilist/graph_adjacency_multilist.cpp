/*
 * File: .c
 * Purpose:
 * Input:
 * Output:
 */

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <string.h>

#define VERTEX_NUM 7

std::queue<int> my_queue;

int visit[VERTEX_NUM];

typedef struct edge_node{
    int vertex_i;
    struct edge_node *next_same_i;
    int vertex_j;
    struct edge_node *next_same_j;
}edge_node;

typedef struct vertex_node{
    edge_node *first_ege;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *graph_initial(void);

void add_edge(graph *g, int i, int j);

void bfs(graph *g, int vertex);

void bfs_traverse(graph *g);

void dfs(graph *g, int vertex);

void dfs_traverse(graph *g);

int main(){
    char choice;
    graph *g = graph_initial();

    printf("input example: \n");
    printf("a 2 0 1 1 2 - add two arcs 0-1 and 1-2\n");
    printf("t - show bfs traversal's result and dfs traversal's result\n");
    printf("q/e/others -quit\n");

    while(1){
        scanf(" %c", &choice);

        if(choice == 'a'){
            int num;
            scanf(" %d", &num);
            for(int i = 0; i < num; i++){
                int tail, head;
                scanf(" %d %d", &tail, &head);
                add_edge(g, tail, head);
            }
        }else if(choice == 't'){
            bfs_traverse(g);
            dfs_traverse(g);
        }else{
            break;
        }
    }
    return 0;
}

graph *graph_initial(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));

    //set head node
    for(int i = 0; i < VERTEX_NUM; i++){
        g->vertex_list[i].first_ege = (edge_node *)malloc(sizeof(edge_node));
        memset(g->vertex_list[i].first_ege, 0, sizeof(edge_node));
    }
}

void add_edge(graph *g, int i, int j){
    //get a new node
    edge_node *edge = (edge_node *)malloc(sizeof(edge_node));
    edge->vertex_i = i;
    edge->vertex_j = j;
    
    //insert the new node to two linked list
    edge->next_same_i = g->vertex_list[i].first_ege
}

void bfs(graph *g, int vertex);

void bfs_traverse(graph *g);

void dfs(graph *g, int vertex);

void dfs_traverse(graph *g);