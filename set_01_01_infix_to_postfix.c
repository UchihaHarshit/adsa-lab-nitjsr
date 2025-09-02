#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int precedence(char operator) {
    switch (operator) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            return 0;
    }
}
// function to covert infix to postfix
int infixToPostfix(char *expression){
    int length = strlen(expression);
    char stack[length];
    char result[length + 1];
    int top = -1, j = 0;

    for(int i = 0; i < length; i++) {
        char current = expression[i];

        if (isalnum(current)) {
            result[j++] = current; // If the character is an operand, add it to the result
        } else if (current == '(') {
            stack[++top] = current; // Push '(' onto the stack
        } else if (current == ')') {
            while (top != -1 && stack[top] != '(') {
                result[j++] = stack[top--]; // Pop from stack until '(' is found
            }
            top--; // Pop the '(' from the stack
        } else { // Operator
            while (top != -1 && precedence(stack[top]) >= precedence(current)) {
                result[j++] = stack[top--]; // Pop operators from stack to result based on precedence
            }
            stack[++top] = current; // Push the current operator onto the stack
        }
    }
    while (top != -1) {
        result[j++] = stack[top--]; // Pop all remaining operators from the stack
    }
    result[j] = '\0'; // Null-terminate the result string
    printf("Postfix Expression: %s\n", result);
    return 0;
}

int main(){
    char expression[100];
    printf("Enter an infix expression: ");
    fgets(expression, sizeof(expression), stdin);
    
    // Remove newline character if present
    size_t len = strlen(expression);
    if (len > 0 && expression[len - 1] == '\n') {
        expression[len - 1] = '\0';
    }
    infixToPostfix(expression); // Convert the infix expression to postfix
    return 0;
}