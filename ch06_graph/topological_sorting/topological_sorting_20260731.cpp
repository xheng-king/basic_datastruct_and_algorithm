/*
 * File: topological_sorting_20260713.cpp
 * Purpose: Perform topological sorting on a directed acyclic graph (DAG) with 8 vertices.
 *          The algorithm uses a stack to iteratively output vertices with zero indegree
 *          and removes their outgoing edges, thereby producing a linear ordering.
 * Input:  The number of directed arcs, followed by that many pairs of (tail, head)
 *         representing edges from tail to head. Vertices are indexed 0 to 7.
 * Output: The topological order of the vertices, printed as a space‑separated sequence.
 *         If the graph contains a cycle, not all vertices will be printed.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stack>

#define VERTEX_NUM 8

typedef struct graph{
    int indegree[VERTEX_NUM];
    int arc[VERTEX_NUM][VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_arc(graph *g, int tail, int head){
    g->arc[tail][head] = 1;
    g->indegree[head]++;
}

void delete_graph(graph *g){
    if(g != NULL)
        free(g);
}

void topological_sort(graph *g){
    std::stack<int> my_stack;
    
    //find the source vertex
    int source;
    for(int i = 0; i < VERTEX_NUM; i++){
        if(g->indegree[i] == 0){
            source = i;
            break;
        }
    }

    //start topological sorting
    printf("%d ", source);
    my_stack.push(source);

    while(!my_stack.empty()){
        int current = my_stack.top();
        my_stack.pop();

        for(int i = 0; i < VERTEX_NUM; i++){
            if(g->arc[current][i]){
                g->indegree[i]--;
                if(g->indegree[i] == 0){
                    printf("%d ", i);
                    my_stack.push(i);
                }
            }
        }
    }

    printf("\n");
}

int main(){
    graph *g = init_graph();
    int tail, head;
    int arc_num;

    printf("input arc's num:");
    scanf("%d", &arc_num);

    printf("input arcs:");
    for(int i = 0; i < arc_num; i++){
        scanf(" %d %d", &tail, &head);
        add_arc(g, tail, head);
    }

    printf("topological sorting's result:\n");
    topological_sort(g);

    delete_graph(g);
    return 0;
}