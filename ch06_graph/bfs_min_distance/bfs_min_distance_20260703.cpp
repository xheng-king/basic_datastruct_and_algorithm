/*
 * File: bfs_min_distance.cpp
 * Purpose:
 *   Implements an unweighted directed graph using adjacency lists and provides
 *   BFS traversal, DFS traversal, and single-source shortest path (minimum number
 *   of edges) from a given source vertex using BFS. The graph has a fixed number
 *   of vertices (VERTEX_NUM = 8). Interactive console commands allow adding arcs,
 *   displaying traversal orders, and computing shortest distances.
 * Input:
 *   Commands from standard input:
 *     - 'a' <arc_count> <tail1> <head1> ... : add <arc_count> directed arcs.
 *     - 't' : print BFS traversal order and DFS traversal order (each on a new line).
 *     - 'f' <source> : compute and print the shortest distances (in edges) from
 *                      <source> to all vertices, in vertex-index order. Unreachable
 *                      vertices are printed as INT_MAX/2.
 *     - any other character : terminates the program.
 *   All vertex indices are assumed to be in [0, VERTEX_NUM-1].
 * Output:
 *   - For 't': two lines, first with BFS order (space-separated), second with DFS order.
 *   - For 'f': one line with VERTEX_NUM integers, the distances from the source.
 *   - For invalid or malformed input, behavior is undefined (no error handling).
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <queue>

#define VERTEX_NUM 8

int visit[VERTEX_NUM];

std::queue<int> my_queue;

typedef struct arc_node{
    int head_vertex;
    struct arc_node *next_arc;
}arc_node;

typedef struct vertex_node{
    arc_node *first_arc;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_arc(graph *g, int tail, int head){
    arc_node *new_node = (arc_node *)malloc(sizeof(arc_node));
    new_node->head_vertex = head;
    new_node->next_arc = g->vertex_list[tail].first_arc;
    g->vertex_list[tail].first_arc = new_node;
}

void bfs(graph *g, int source){
    printf("%d ", source);
    visit[source] = 1;
    my_queue.push(source);

    while(!my_queue.empty()){
        int current = my_queue.front();
        my_queue.pop();
        for(arc_node *p = g->vertex_list[current].first_arc; p != NULL; p = p->next_arc){
            if(!visit[p->head_vertex]){
                visit[p->head_vertex] = 1;
                printf("%d ", p->head_vertex);
                my_queue.push(p->head_vertex);
            }
        }
    }
}

void bfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));
    while(!my_queue.empty())
        my_queue.pop();
    for(int i = 0; i < VERTEX_NUM; i++){
        if(!visit[i])
            bfs(g, i);
    }
    printf("\n");
}

void dfs(graph *g, int current){
    visit[current] = 1;
    printf("%d ", current);

    for(arc_node *p = g->vertex_list[current].first_arc; p != NULL; p = p->next_arc){
        if(!visit[p->head_vertex]){
            dfs(g, p->head_vertex);
        }
    }
}

void dfs_traverse(graph *g){
    memset(visit, 0 ,sizeof(visit));
    
    for(int i = 0 ; i < VERTEX_NUM; i++){
        if(!visit[i])
            dfs(g, i);
    }
    printf("\n");
}

void bfs_min_distance(graph *g, int source, int distance[]){
    memset(visit, 0, sizeof(visit));
    while(!my_queue.empty())
        my_queue.pop();
    for(int i = 0; i < VERTEX_NUM; i++)
        distance[i] = INT_MAX / 2;

    distance[source] = 0;
    visit[source] = 1;
    my_queue.push(source);

    while(!my_queue.empty()){
        int current = my_queue.front();
        my_queue.pop();
        for(arc_node *arc = g->vertex_list[current].first_arc; arc != NULL; arc = arc->next_arc){
            if(!visit[arc->head_vertex]){
                visit[arc->head_vertex] = 1;
                distance[arc->head_vertex] = distance[current] + 1;
                my_queue.push(arc->head_vertex);
            }
        }
    }
}

int main(){
    graph *g = init_graph();
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
                int dist[VERTEX_NUM];
                bfs_min_distance(g, vertex, dist);
                for(int i = 0; i <VERTEX_NUM; i++)
                    printf("%d ", dist[i]);
                printf("\n");
                break;

            default:
                return 0;
                break;
        }
    }
}
