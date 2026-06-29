/*
 * File: graph_adjacency_multilist.cpp
 * Purpose: Implements an undirected graph using an adjacency multilist representation.
 *          Supports adding edges, and performs both breadth‑first search (BFS) and
 *          depth‑first search (DFS) traversals over the entire graph, handling
 *          disconnected components by restarting from each unvisited vertex.
 * Input:  Interactive commands from standard input:
 *           a <num> <tail1> <head1> ... <tailN> <headN>
 *             – Adds <num> undirected edges. Each edge is given by its tail and head
 *               vertex indices (both in the range 0 .. VERTEX_NUM‑1, where VERTEX_NUM
 *               is fixed to 7 in this implementation).
 *           t – Executes both BFS and DFS traversals and prints their vertex sequences.
 *           q / e / other – Terminates the program.
 * Output: For each 't' command, prints two lines:
 *           – The BFS traversal order (space‑separated vertex indices).
 *           – The DFS traversal order (space‑separated vertex indices).
 *         If no edges have been added, each line is empty (just a newline).
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
    memset(visit, 0, sizeof(visit));
    while(!my_queue.empty())
        my_queue.pop();

    return g;
}

void add_edge(graph *g, int i, int j){
    //get a new node
    edge_node *edge = (edge_node *)malloc(sizeof(edge_node));
    edge->vertex_i = i;
    edge->vertex_j = j;
    
    //insert the new node to two linked list
    edge->next_same_i = g->vertex_list[i].first_ege;
    g->vertex_list[i].first_ege = edge;
    edge->next_same_j = g->vertex_list[j].first_ege;
    g->vertex_list[j].first_ege = edge;
}

void bfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;
    my_queue.push(vertex);

    while(!my_queue.empty()){
        int tmp = my_queue.front();
        my_queue.pop();
        for(edge_node *p = g->vertex_list[tmp].first_ege; p != NULL; ){
            int adjacent_vertex = (tmp == p->vertex_i) ? p->vertex_j : p->vertex_i;

            if(visit[adjacent_vertex] == 0){
                printf("%d ", adjacent_vertex);
                visit[adjacent_vertex] = 1;
                my_queue.push(adjacent_vertex);
            }

            p = (tmp == p->vertex_i) ? p->next_same_i : p->next_same_j;
        }
    }
}

void bfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));

    for(int i = 0; i < VERTEX_NUM; i++){
        if(visit[i] == 0)
            bfs(g, i);
    }

    printf("\n");
}

void dfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;

    for(edge_node *p = g->vertex_list[vertex].first_ege; p != NULL; ){
        int adjacent_vertex = (vertex == p->vertex_i) ? p->vertex_j : p->vertex_i;

        if(visit[adjacent_vertex] == 0)
            dfs(g, adjacent_vertex);

        p = (vertex == p->vertex_i) ? p->next_same_i : p->next_same_j;
    }
}

void dfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));

    for(int i = 0; i < VERTEX_NUM; i++){
        if(visit[i] == 0)
            dfs(g, i);
    }

    printf("\n");
}