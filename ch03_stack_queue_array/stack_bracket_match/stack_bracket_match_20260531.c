/*
 * Purpose: Check whether brackets in an expression are valid (using stack)
 * Input:  An intetral expression
 * Output: Valid / Invalid with specific error message
 */

#include <stdio.h>
#include <string.h>

#define MAXSIZE 20
typedef struct{
    char storage[MAXSIZE];
    char top; //char is enough 
}stack;

int push(stack *st, char bk){
    if(st->top == MAXSIZE - 1)
        return -1;
    st->storage[++st->top] = bk;
    return 0;
}

char pop(stack *st){
    if(st->top == 0)
        return -1;
    st->top--;
    return st->storage[st->top+1];
}

int isEmpty(stack *st){
    return st->top==0;
}

int main(){
    stack st;
    char iep[100]; //integral expression
    int len; //lenth of the integral expression
    
    printf("input an integral expression:");
    scanf("%s", iep);
    len = strlen(iep);

    for(int i = 0; i < len; i++){
        switch(iep[i]){
            case '(':
            case '[':
            case '{':
            if(push(&st, iep[i]) == -1){
                printf("expression is wrong.\n");
                return 0;
            }
            break;
            case ')':
            if(pop(&st) != '('){
                printf("Expresion is wrong. Unmatched\n");
                return 0;
            }
            break;
            case ']':
            if(pop(&st) != '['){
                printf("Expresion is wrong. Unmatched\n");
                return 0;
            }
            break;
            case '}':
            if(pop(&st) != '{'){
                printf("Expresion is wrong. Unmatched\n");
                return 0;
            }
            break;
            default:
            continue;
        }
    }
    if(isEmpty(&st))
        printf("Expression is valid.\n");
    else
        printf("Expresion is wrong. Lacking bracket.\n");
    return 0;
}