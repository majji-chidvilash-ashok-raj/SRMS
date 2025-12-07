#include <stdio.h>
#include <string.h>

#define SIZE 50

char stack[SIZE];
int top = -1;

void push(char c) {
    if(top < SIZE - 1) {
        top++;
        stack[top] = c;
    }
}

char pop() {
    if(top >= 0) {
        return stack[top--];
    }
    return '0';
}

int isMatch(char a, char b) {
    if(a == '(' && b == ')') return 1;
    if(a == '{' && b == '}') return 1;
    if(a == '[' && b == ']') return 1;
    return 0;
}

int main() {
    char exp[100];
    int i, valid = 1;
    scanf("%s", exp);

    for(i = 0; i < strlen(exp); i++) {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            push(exp[i]);
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            char topChar = pop();
            if(!isMatch(topChar, exp[i])) {
                valid = 0;
                break;
            }
        }
    }

    if(valid && top == -1) printf("Balanced\n");
    else printf("Not Balanced\n");

    return 0;
}
