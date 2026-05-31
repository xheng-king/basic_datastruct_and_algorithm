/*
 * Purpose: Check whether brackets in an expression are valid (using stack)
 * Input:  An expression (may include parentheses, square brackets, curly braces)
 * Output: Valid / Invalid with specific error message
 *
 * Improvements over original:
 * 1. Initialize stack top properly.
 * 2. Use int for top index and return error codes.
 * 3. Increase stack size to handle deeper nesting.
 * 4. Use fgets() instead of scanf() to accept spaces.
 * 5. More descriptive error messages.
 * 6. Fixed typos (lenth -> length, Expresion -> Expression).
 */

#include <stdio.h>
#include <string.h>

#define MAXSIZE 100          /* Enough for most expressions */
#define EXPR_LEN 200

typedef struct {
    char storage[MAXSIZE];
    int top;                 /* Index of top element; 0 means empty stack */
} stack;

/* Initialize stack: set top to 0 (empty) */
void initStack(stack *st) {
    st->top = 0;
}

/* Push a character onto stack. Returns 0 on success, -1 on overflow */
int push(stack *st, char ch) {
    if (st->top >= MAXSIZE - 1) {
        return -1;           /* Stack overflow */
    }
    st->storage[++st->top] = ch;
    return 0;
}

/* Pop a character from stack. Returns the char, or '\0' if empty */
char pop(stack *st) {
    if (st->top == 0) {
        return '\0';         /* Empty stack, return null character */
    }
    return st->storage[st->top--];
}

/* Check if stack is empty */
int isEmpty(stack *st) {
    return st->top == 0;
}

int main() {
    stack st;
    initStack(&st);          /* MUST initialize before use */

    char expr[EXPR_LEN];
    printf("Input an expression (supports (), [], {}): ");
    fgets(expr, sizeof(expr), stdin);
    /* Remove trailing newline from fgets */
    expr[strcspn(expr, "\n")] = '\0';

    int len = strlen(expr);
    for (int i = 0; i < len; i++) {
        char c = expr[i];
        switch (c) {
            case '(':
            case '[':
            case '{':
                if (push(&st, c) == -1) {
                    printf("Error: Too many nested brackets (stack overflow).\n");
                    return 1;
                }
                break;
            case ')':
                if (pop(&st) != '(') {
                    printf("Expression is wrong: Unmatched ')' at position %d.\n", i);
                    return 1;
                }
                break;
            case ']':
                if (pop(&st) != '[') {
                    printf("Expression is wrong: Unmatched ']' at position %d.\n", i);
                    return 1;
                }
                break;
            case '}':
                if (pop(&st) != '{') {
                    printf("Expression is wrong: Unmatched '}' at position %d.\n", i);
                    return 1;
                }
                break;
            default:
                /* Ignore non-bracket characters */
                break;
        }
    }

    if (isEmpty(&st)) {
        printf("Expression is valid.\n");
        return 0;
    } else {
        printf("Expression is wrong: Missing closing bracket(s).\n");
        return 1;
    }
}