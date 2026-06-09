/*
 * File: graph_adjacency_matrix.c
 * Purpose:
 * Input:
 * Output:
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <queue>

#define MAX_VERTEX_LEN 10

typedef int vertex_type;
typedef int edge_type;

typedef struct{
    edge_type edge[MAX_VERTEX_LEN][MAX_VERTEX_LEN];
}graph;

std::queue<vertex_type> q;
int visit[MAX_VERTEX_LEN] = {0};

graph * initial_graph(){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_edge(graph *g, vertex_type v1, vertex_type v2);

void bfs_traverse(graph *g);

void dfs_traverse(graph *g);

int main(){
    graph *g = initial_graph();
    char choice;
    vertex_type v1, v2;

    printf("input example:\n");
    printf("a 1 2: add edge between 1 and 2\n");
    printf("t: show bfs and dfs traverse's result\n");

    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                scanf(" %d %d", &v1, &v2);
                add_edge(g, v1, v2);
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

void add_edge(graph *g, vertex_type v1, vertex_type v2){
    g->edge[v1][v2] = 1;
    g->edge[v2][v1] = 1;
}

static void bfs(graph *g, vertex_type v){
    printf("%d ", v);
    visit[v] = 1;
    q.push(v);
    while(!q.empty()){
        int v1 = q.front();
        q.pop();
        for(int i = 0; i < MAX_VERTEX_LEN; i++){
            if(g->edge[v1][i] == 1 && visit[i] == 0){
                printf("%d ", i);
                visit[i] = 1;
                q.push(i);
            }
        }
    }
}

void bfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));
    for(vertex_type i = 0; i < MAX_VERTEX_LEN; i++){
        if(visit[i] == 0)
            bfs(g, i);
    }
    printf("\n");
}

static void dfs(graph *g, int i){
    printf("%d ", i);
    visit[i] = 1;
    for(int j = 0; j < MAX_VERTEX_LEN; j++){
        if(visit[j] == 0 && g->edge[i][j] == 1)
            dfs(g, j);
    }
}

void dfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));
    for(vertex_type i = 0; i < MAX_VERTEX_LEN; i++){
        if(visit[i] == 0)
            dfs(g, i);
    }
    printf("\n");
}