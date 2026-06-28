/*
 * File: topological_sorting.c
 * Purpose: Implements topological sorting on a fixed-size directed graph 
 *          (5 vertices) using Kahn's algorithm. The graph is built interactively 
 *          via user commands and can output one valid topological order if the 
 *          graph is a DAG, or report failure if a cycle exists.
 * Input:   Interactive commands from stdin:
 *          - 'a' followed by an integer arc_num and arc_num pairs of vertices 
 *            (v1 v2), adds directed edges v1 -> v2.
 *          - 'f' performs and prints the topological sorting result.
 *          - 'd' deletes all existing edges.
 *          - Any other character terminates the program.
 * Output:  On 'f': prints "result: " followed by the topological order (space-separated) 
 *          if successful, otherwise prints "fail". Also prints each vertex's in-degree 
 *          during sorting (debug output, currently present). On other commands, 
 *          no output except implicit prompts.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define VERTEX_NUM 5

#define STACK_SIZE 2*VERTEX_NUM

typedef struct stack{
    int data[STACK_SIZE];
    int top;
}stack;

stack *init_stack(void){
    stack *s = (stack *)malloc(sizeof(stack));
    memset(s, 0, sizeof(stack));
    return s;
}

void push(stack *s, int item){
    s->data[s->top++] = item;
}

int pop(stack *s){
    s->top--;
    return s->data[s->top];
}

int stack_is_empty(stack *s){
    return s->top == 0;
}

void delete_stack(stack *s){
    free(s);
}

typedef struct graph{
    int arc[VERTEX_NUM][VERTEX_NUM];
}graph;

graph *init_graph(void){
    graph *g = (graph *)malloc(sizeof(graph));
    memset(g, 0, sizeof(graph));
    return g;
}

void add_arc(graph *g, int v1, int v2){
    g->arc[v1][v2] = 1;
}

void delete_arc(graph *g){
    memset(g, 0, sizeof(graph));
}

void delete_graph(graph *g){
    free(g);
}

int topological_sort(graph *g, int result[]){
    int pointor = 0;
    stack *s = init_stack();
    int in_degree[VERTEX_NUM];

    for(int i = 0; i < VERTEX_NUM; i++){
        int sum = 0;
        for(int j = 0; j < VERTEX_NUM; j++){
            sum += g->arc[j][i];
        }
        in_degree[i] = sum;
        printf("%d ", sum);
        if(sum == 0)
            push(s, i);
    }

    while(!stack_is_empty(s)){
        int item = pop(s);
        result[pointor++] = item;
        for(int i = 0; i < VERTEX_NUM; i++){
            if(g->arc[item][i] == 1){
                if(!(--in_degree[i]))
                    push(s, i);
            }
        }
    }

    if(pointor == VERTEX_NUM)
        return 1;
    else
        return 0;
}

int main(){
    graph *g = init_graph();
    char choice;
    int v1, v2;

    printf("input example:\n");
    printf("a 2 0 1 3 4: add 2 arcs between 0&1 and 3&4\n");
    printf("f: print topological sorting's result\n");
    printf("d: delete all edges\n");

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
            
            case 'f':
                int result[VERTEX_NUM];
                int success = topological_sort(g, result);
                if(success){
                    printf("result: ");
                    for(int i = 0; i < VERTEX_NUM; i++){
                        printf("%d ", result[i]);
                    }
                    printf("\n");
                }else
                    printf("fail\n");
                break;

            case 'd':
                delete_arc(g);
                break;

            default:
                delete_graph(g);
                return 0;
        }
    }
}
