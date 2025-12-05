#include <stdio.h>

#define SIZE 20

int stack[SIZE];
int top = -1;

void push(int x) {
    if (top == SIZE - 1) {
        printf("Stack overflow\n");
        return;
    }
    top++;
    stack[top] = x;
    printf("Pushed %d\n", x);
}

void pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        return;
    }
    printf("Popped %d\n", stack[top]);
    top--;
}

void peek() {
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Top element = %d\n", stack[top]);
}

void display() {
    int i;
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    printf("Stack elements (bottom to top):\n");
    for (i = 0; i <= top; i++)
        printf("%d ", stack[i]);
    printf("\n");
}

void search(int key) {
    int i, pos = -1;
    if (top == -1) {
        printf("Stack is empty\n");
        return;
    }
    for (i = 0; i <= top; i++) {
        if (stack[i] == key) {
            pos = i;
            break;
        }
    }
    if (pos == -1)
        printf("%d not found in stack\n", key);
    else {
        printf("%d found at position %d from bottom\n", key, pos);
        printf("%d found at position %d from top\n", key, top - pos);
    }
}

int main() {
    int ch, x;
    while (1) {
        printf("\n1 Push\n2 Pop\n3 Peek\n4 Display\n5 Search\n6 Exit\n");
        scanf("%d", &ch);
        if (ch == 1) {
            printf("Enter value: ");
            scanf("%d", &x);
            push(x);
        } else if (ch == 2) {
            pop();
        } else if (ch == 3) {
            peek();
        } else if (ch == 4) {
            display();
        } else if (ch == 5) {
            printf("Enter value to search: ");
            scanf("%d", &x);
            search(x);
        } else if (ch == 6) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }
    return 0;
}
