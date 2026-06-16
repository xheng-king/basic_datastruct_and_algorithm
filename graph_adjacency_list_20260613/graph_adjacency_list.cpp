/*
 * File: graph_adjacency_list.cpp
 * Purpose: Implements a graph using adjacency list representation. Supports adding directed edges and performing BFS (Breadth-First Search) and DFS (Depth-First Search) traversals on the graph.
 * Input: Interactive commands. 'a' followed by an integer arc_num and arc_num pairs of vertices (v1 v2) to add directed edges from v1 to v2. 't' triggers BFS and DFS traversals. Any other character exits the program.
 * Output: For the 't' command, outputs the BFS traversal order followed by the DFS traversal order, each on a new line. Vertex indices are printed as integers separated by spaces.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#define VERTEX_NUM 10

typedef struct arc_node{
    int adjacent_vertex;
    struct arc_node *next;
}arc_node;

typedef struct{
    arc_node *first_arc;
}vertex_node, adj_list[VERTEX_NUM];

typedef struct{
    adj_list vertex_list;
}graph;

std::queue<int> my_queue;
int visit[VERTEX_NUM];

graph * initial_graph(){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_edge(graph *g, int v1, int v2);

void bfs_traverse(graph *g);

void dfs_traverse(graph *g);

int main(){
    graph *g = initial_graph();
    char choice;
    int v1, v2;

    printf("input example:\n");
    printf("a 2 0 1 3 4: add 2 arcs between 0&1 and 3&4\n");
    printf("t: show bfs and dfs traverse's result\n");

    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                int arc_num;
                scanf(" %d", &arc_num);
                for(int i = 0; i < arc_num; i++){
                    scanf(" %d %d", &v1, &v2);
                    add_edge(g, v1, v2);
                }
                break;

            case 't':
                bfs_traverse(g);
                dfs_traverse(g);
                break;
            
            default:
                return 0;
                break;
        }
    }
}

void add_edge(graph *g, int v1, int v2){
    arc_node *p = g->vertex_list[v1].first_arc;
    if(p == NULL){
        g->vertex_list[v1].first_arc = (arc_node *)malloc(sizeof(arc_node));
        g->vertex_list[v1].first_arc->adjacent_vertex = v2;
        g->vertex_list[v1].first_arc->next = NULL;
    }else{
        while(p->next != NULL)
            p = p->next;

        p->next = (arc_node *)malloc(sizeof(arc_node));
        p->next->adjacent_vertex = v2;
        p->next->next = NULL;
    }
}

static void bfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;
    my_queue.push(vertex);

    while(!my_queue.empty()){
        int tmp = my_queue.front();
        my_queue.pop();
        for(arc_node *p = g->vertex_list[tmp].first_arc; p != NULL; p = p->next){
            if(visit[p->adjacent_vertex] == 0){
                printf("%d ", p->adjacent_vertex);
                visit[p->adjacent_vertex] = 1;
                my_queue.push(p->adjacent_vertex);
            }
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

static void dfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;

    arc_node *p = g->vertex_list[vertex].first_arc;
    for(; p != NULL; p = p->next){
        if(visit[p->adjacent_vertex] == 0)
            dfs(g, p->adjacent_vertex);
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