/*
 * File: bfs_min_distance.cpp
 * Purpose: Implements an undirected graph using adjacency lists and provides
 *          BFS traversal, DFS traversal, and single-source shortest-path
 *          (minimum number of edges) from a given vertex using BFS.
 * Input:   Interactive commands:
 *          a <n> <v1> <v2> ... : add <n> undirected edges (each pair v1 v2).
 *          t                    : print BFS and DFS traversal sequences.
 *          f <v>                : print the shortest distances from vertex v
 *                                 to all other vertices (BFS-based).
 *          Any other character  : terminate the program.
 * Output:  For 't' – two lines: BFS order and DFS order (space‑separated).
 *          For 'f' – one line with VERTEX_NUM integers, the distances from
 *          the given source (‑1 for unreachable vertices).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define VERTEX_NUM 7

int visit[VERTEX_NUM];

int distance[VERTEX_NUM];

std::queue<int> my_queue;

typedef struct arc_node{
    int adjacent_vertex;
    struct arc_node* next_arc;
}arc_node;

typedef struct vertex_node{
    arc_node *first_node;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *graph_initial(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));

    memset(visit, 0, sizeof(visit));
    while(!my_queue.empty())
        my_queue.pop();

    return g;
}

void add_arc(graph *g, int tail, int head){
    arc_node *new_node = (arc_node *)malloc(sizeof(arc_node));
    new_node->adjacent_vertex = head;

    new_node->next_arc = g->vertex_list[tail].first_node;
    g->vertex_list[tail].first_node = new_node;
}

void bfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;
    my_queue.push(vertex);

    while(!my_queue.empty()){
        int out_queue_vertex = my_queue.front();
        my_queue.pop();
        for(arc_node *p = g->vertex_list[out_queue_vertex].first_node; p!=NULL; p = p->next_arc){
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
        if(visit[i] == 0){
            bfs(g, i);
        }
    }

    printf("\n");
}

void dfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;

    for(arc_node *p = g->vertex_list[vertex].first_node; p != NULL; p = p->next_arc){
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

void bfs_min_distance(graph *g, int vertex){
    memset(visit, 0, sizeof(visit));
    for(int i = 0; i < VERTEX_NUM; i++)
        distance[i] = -1;

    distance[vertex] = 0;
    visit[vertex] = 1;
    my_queue.push(vertex);

    while(!my_queue.empty()){
        int queue_front_vertex = my_queue.front();
        my_queue.pop();
        for(arc_node *p = g->vertex_list[queue_front_vertex].first_node; p != NULL; p = p->next_arc){
            if(visit[p->adjacent_vertex] == 0){
                distance[p->adjacent_vertex] = distance[queue_front_vertex] + 1;
                visit[p->adjacent_vertex] = 1;
                my_queue.push(p->adjacent_vertex);
            }
        }
    }
    
    for(int i = 0; i < VERTEX_NUM; i++){
        printf("%d ", distance[i]);
    }

    printf("\n");
}

int main(){
    graph *g = graph_initial();
    char choice;
    int v1, v2;

    printf("input example:\n");
    printf("a 2 0 1 3 4: add 2 arcs between 0&1 and 3&4\n");
    printf("t: show bfs and dfs traverse's result\n");
    printf("f 0: find distance between vertex 0 to other vertex\n");

    while(1){
        scanf(" %c", &choice);
        switch(choice){
            case 'a':
                int arc_num;
                scanf(" %d", &arc_num);
                for(int i = 0; i < arc_num; i++){
                    scanf(" %d %d", &v1, &v2);
                    add_arc(g, v1, v2);
                }
                break;

            case 't':
                bfs_traverse(g);
                dfs_traverse(g);
                break;
            
            case 'f':
                int vertex;
                scanf(" %d", &vertex);
                bfs_min_distance(g, vertex);
                break;

            default:
                return 0;
                break;
        }
    }
}
