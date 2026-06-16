/*
 * File: graph_orthogonal_linked_list.c
 * Purpose:
 * Input:
 * Output:
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>

#define VERTEX_NUM 10

typedef struct arc_node{
    int tail_vertex;
    int head_vertex;
    struct arc_node *next_same_tail;
    struct arc_node *next_same_head;
}arc_node;

typedef struct vertex_node{
    arc_node *first_in;
    arc_node *first_out;
}vertex_node;

typedef struct graph{
    vertex_node vertex_list[VERTEX_NUM];
}graph;

int visit[VERTEX_NUM];

std::queue<int> my_queue;

graph *initial_graph(void);

void add_edge(graph *g, int tail, int head);

void bfs(graph *g, int vertex);

void bfs_traverse(graph *g);

void dfs(graph *g, int vertex);

void dfs_traverse(graph *g);

int main(){
    char choice;
    graph *g = initial_graph();

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

graph *initial_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));

    for(int i = 0; i < VERTEX_NUM; i++){
        //set head node of each link list

        g->vertex_list[i].first_in = (arc_node *)malloc(sizeof(arc_node));
        g->vertex_list[i].first_in->head_vertex = 0;
        g->vertex_list[i].first_in->tail_vertex = 0;
        g->vertex_list[i].first_in->next_same_head = NULL;
        g->vertex_list[i].first_in->next_same_tail = NULL;

        g->vertex_list[i].first_out = (arc_node *)malloc(sizeof(arc_node));
        memcpy(g->vertex_list[i].first_out, g->vertex_list[i].first_in, sizeof(arc_node));
    }
    return g;
}

void add_edge(graph *g, int tail, int head){
    //head insertion
    arc_node *tmp = g->vertex_list[tail].first_out->next_same_tail;
    g->vertex_list[tail].first_out = (arc_node *)malloc(sizeof(arc_node));
    g->vertex_list[tail].first_out->head_vertex = head;
    g->vertex_list[tail].first_out->tail_vertex = tail;
    g->vertex_list[tail].first_out->next_same_tail = tmp;
    g->vertex_list[tail].first_out->next_same_head = 
}

void bfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;
    my_queue.push(vertex);

    while(!my_queue.empty()){
        int pop_vertex = my_queue.front();
        my_queue.pop();

        for(arc_node *p = g->vertex_list[pop_vertex].first_out; p != NULL; p = p->next_tail){
            if(visit[p->head_vertex] == 0){
                printf("%d ", p->head_vertex);
                visit[p->head_vertex] = 1;
                my_queue.push(p->head_vertex);
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

void dfs(graph *g, int vertex){
    printf("%d ", vertex);
    visit[vertex] = 1;

    for(arc_node *p = g->vertex_list[vertex].first_out; p != NULL; p = p->next_tail){
        if(visit[p->head_vertex] == 0)
            bfs(g, p->head_vertex);
    }
}

void dfs_traverse(graph *g){
    memset(visit, 0, sizeof(visit));

    for(int i = 0; i < VERTEX_NUM; i++){
        if(visit[i] == 0)
            bfs(g, i);
    }
}