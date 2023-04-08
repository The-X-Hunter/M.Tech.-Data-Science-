#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Define the structure for the binary tree node
typedef struct node {
    char data;
    struct node* left;
    struct node* right;
} node;

// Function to create a new node for the binary tree
node* newNode(char data) {
    node* temp = (node*)malloc(sizeof(node));
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

// Function to build the binary tree from the expression string
node* buildTree(char* exp, int start, int end) {
    if (start > end) {
        return NULL;
    }
    node* root = newNode(exp[start]);

    // If the current character is an operand, return the node
    if (start == end) {
        return root;
    }

    // Otherwise, find the index of the operator that separates the expression into left and right sub-trees
    int index = -1;
    int parenthesesCount = 0;
    for (int i = start + 1; i <= end; i++) {
        if (exp[i] == '(') {
            parenthesesCount++;
        } else if (exp[i] == ')') {
            parenthesesCount--;
        } else if (parenthesesCount == 0) {
            if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/') {
                index = i;
                break;
            }
        }
    }

    // Build the left and right sub-trees recursively
    if (index != -1) {
        //root->left = buildTree(exp, start+1, index-1);
        //root->right = buildTree(exp, index+1, end);
        node* operator = newNode(exp[index]);
        operator->left = root;
        root = operator;
        node* new = buildTree(exp, index+1, end);
        switch(operator->data){
            case '+':   operator->right = new;
                        break;
            case '-':   if(new->data == '+' || new->data == '-'){
                            operator->right = new->left;
                            new->left = operator;
                            root = new;
                        } else {
                            operator->right = new;
                        }
                        break;
            case '*':
            case '/':   if(new->data == '+' || new->data == '-'){
                            operator->right = new->left;
                            new->left = operator;
                            root = new;
                        } else {
                            operator->right = new;
                        }
                        break;
        }
    }
    return root;
}

// Function to evaluate the binary tree
int evaluate(node* root) {
    int x;
    if (root->left == NULL && root->right == NULL) {
        return (int)(root->data - '0');
    }
    //printf("Hello\n");
    int leftValue = 0;
    if(root->left != NULL){
        leftValue = evaluate(root->left);
    }
    //printf("%d\n", leftValue);
    int rightValue = 0;
    if(root->right != NULL){
        rightValue = evaluate(root->right);
    }
    //printf("%d\t%c\t%d\n", leftValue, root->data, rightValue);
    switch (root->data) {
        case '+':
            return leftValue + rightValue;
        case '-':
            return leftValue - rightValue;
        case '*':
            return leftValue * rightValue;
        case '/':
            return leftValue / rightValue;
        default:
            return 0;
    }
}

// Main function to test the program
int main() {
    char expression[100];
    printf("Enter an arithmetic expression: ");
    scanf("%s", expression);

    node* root = buildTree(expression, 0, strlen(expression)-1);
    printf("Result = %d\n", evaluate(root));

    return 0;
}
