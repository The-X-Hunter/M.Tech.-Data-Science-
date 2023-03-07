/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: Write a program to evaluate an arithmatic expression using binary tree
*/

#include<stdio.h>
#include<stdlib.h>

/*
This structure defines a node of binary tree.
Left part of node can have a subtree or an operand. isLeftSubTree is a flag to indicate what is actually stored in union.
Same goes with right part.
*/
struct Expression{
    union{
        struct Expression * leftSubTree;
        int leftOperand;
    };
    int isLeftSubTree;
    char operator;
    int isRightSubTree;
    union{
        struct Expression * rightSubTree;
        int rightOperand;
    };
};

//Stores how many number of terms an arithmaic expression has.
int numberOfTerms;

//Pointer to root of the binary tree.
struct Expression * rootNode;

//Evaluate arithmatic expression using postorder tree traversal. (Left-Right-Root format)
int postorderTraversal(struct Expression * parent){
    int leftOperand, rightOperand;
    leftOperand = 0;
    rightOperand = 0;
    if(parent -> isLeftSubTree == 1){
        leftOperand = postorderTraversal(parent -> leftSubTree);
    } else {
        leftOperand = parent -> leftOperand;
    }
    if(parent -> isRightSubTree == 1){
        rightOperand = postorderTraversal(parent -> rightSubTree);
    } else {
        rightOperand = parent -> rightOperand;
    }
    switch(parent -> operator){
        case '+':   leftOperand = leftOperand + rightOperand;
                    break;
        case '-':   leftOperand = leftOperand - rightOperand;
                    break;
        case '*':   leftOperand = leftOperand * rightOperand;
                    break;
        case '/':   leftOperand = leftOperand / rightOperand;
                    break;
    }
    return leftOperand;
}

//Print arithmatic expression using inorder tree traversal. (Left-Root-Right format)
int inorderTraversal(struct Expression * parent){
    if(parent -> isLeftSubTree == 1){
        inorderTraversal(parent -> leftSubTree);
    } else {
        printf("%d ", parent -> leftOperand);
    }
    printf("%c ", parent -> operator);
    if(parent -> isRightSubTree == 1){
        inorderTraversal(parent -> rightSubTree);
    } else {
        printf("%d ", parent -> rightOperand);
    }
    return 0;
}

//Read & store artithmatic expression.
int readArithmaticExpression(){
    int i, operand;
    char operator, prevOperator;
    struct Expression * expression, * prevExpression;
    //Ask user for total number of terms.
    printf("How many number of terms your expression has?: ");
    scanf("%d", &numberOfTerms);
    for(i = 0; i < numberOfTerms; i++){
        //Ask user for left operand of the operator.
        printf("Enter operand: ");
        scanf("%d", &operand);
        //If it is not last term then go for operator part.
        if(i + 1 < numberOfTerms){
            //Ask user for operator.
            do {
                printf("Enter operator: ");
                scanf(" %c", &operator);
            } while(operator != '+' && operator != '-' && operator != '*' && operator != '/');
            //Create new node for recently read operator.
            expression = (struct Expression *) malloc(sizeof(struct Expression *));
            expression -> operator = operator;
            //If there are already some nodes in tree.
            if(i > 0){
                //Fetch previous operator from previous node.
                prevOperator = prevExpression -> operator;
                //Put it in switch case.
                switch(prevOperator){
                    case '+':   
                    case '-':   //Append new node with help of following rules.
                                //prev -> - & curr -> - then new node will become parent of previous
                                //prev -> - & curr -> + then new node will become parent of previous
                                //prev -> + & curr -> - then new node can be either parent or right child of previous node
                                //prev -> + & curr -> + then new node can be either parent or right child of previous node
                                //prev -> +, - & curr -> *, / then new node will become right child of previous node 
                                if(operator == '+' || operator == '-'){
                                    if(prevOperator == '+' && prevExpression -> isLeftSubTree == 1){
                                        prevExpression -> rightSubTree = expression;
                                        prevExpression -> isRightSubTree = 1;
                                        expression -> leftOperand = operand;
                                        expression -> isLeftSubTree = 0;
                                    } else {
                                        prevExpression -> rightOperand = operand;
                                        prevExpression -> isRightSubTree = 0;
                                        expression -> leftSubTree = prevExpression;
                                        expression -> isLeftSubTree = 1;
                                        rootNode = expression;
                                    }
                                } else {
                                    expression -> leftOperand = operand;
                                    expression -> isLeftSubTree = 0;
                                    prevExpression -> rightSubTree = expression;
                                    prevExpression -> isRightSubTree = 1;
                                }
                                break;
                    case '*':
                    case '/':   //prev -> *, / & curr -> +, - then new node will become parent of previous node
                                //prev -> *, / & curr -> *, / then new node can be either parent or right child of previous node
                                if(operator == '+' || operator == '-'){
                                    prevExpression -> rightOperand = operand;
                                    prevExpression -> isRightSubTree = 0;
                                    expression -> leftSubTree = prevExpression;
                                    expression -> isLeftSubTree = 1;
                                    rootNode = expression;
                                } else {
                                    if(prevExpression -> isLeftSubTree == 1){
                                        prevExpression -> rightSubTree = expression;
                                        prevExpression -> isRightSubTree = 1;
                                        expression -> leftOperand = operand;
                                        expression -> isLeftSubTree = 0;
                                    } else {
                                        prevExpression -> rightOperand = operand;
                                        prevExpression -> isRightSubTree = 0;
                                        expression -> leftSubTree = prevExpression;
                                        expression -> isLeftSubTree = 1;
                                        rootNode = expression;
                                    }
                                }
                                break;
                }
            } else {
                //If it is the first node then enter the operand left to its operator and mark it as root node of tree.
                expression -> leftOperand = operand;
                expression -> isLeftSubTree = 0;
                rootNode = expression;
            }
            //curr node will be previous node for next iteration.
            prevExpression = expression;
        } else {
            //If it is last term then enter operand right to previous operator.
            prevExpression -> rightOperand = operand;
            prevExpression -> isRightSubTree = 0;
        }
    }
    return 0;
}

int main(){
    readArithmaticExpression();
    inorderTraversal(rootNode);
    printf("\t = \t");
    printf("%d\n", postorderTraversal(rootNode));
    return 0;
}
