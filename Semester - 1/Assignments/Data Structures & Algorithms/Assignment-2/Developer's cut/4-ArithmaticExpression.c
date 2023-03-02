#include<stdio.h>
#include<stdlib.h>

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

int numberOfTerms;
struct Expression * expression, * rootNode;

int printArithmaticExpression(){
    int i;
    struct Expression * prevExpression, * currExpression;
    prevExpression = rootNode;
    currExpression = rootNode;
    while(i < numberOfTerms) {
        if(currExpression -> leftSubTree != NULL){
            prevExpression = currExpression;
            currExpression = currExpression -> leftSubTree;
        }
    }
    printf("Print\n");
    return 0;
}

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

int readArithmaticExpression(){
    int i, operand;
    char operator, prevOperator;
    struct Expression * prevExpression;
    printf("How many number of terms your expression has?: ");
    scanf("%d", &numberOfTerms);
    for(i = 0; i < numberOfTerms; i++){
        printf("Enter operand: ");
        scanf("%d", &operand);
        if(i + 1 < numberOfTerms){
            do {
                printf("Enter operator: ");
                scanf(" %c", &operator);
            } while(operator != '+' && operator != '-' && operator != '*' && operator != '/');
            expression = (struct Expression *) malloc(sizeof(struct Expression *));
            if(i > 0){
                prevOperator = prevExpression -> operator;
                switch(prevOperator){
                    case '+':
                    case '-':   expression -> operator = operator;
                                if(operator == '+' || operator == '-'){
                                    /*
                                    if(prevExpression -> leftSubTree != NULL){
                                        prevExpression -> rightSubTree = expression;
                                        expression -> leftOperand = operand;
                                    } else {
                                        prevExpression -> rightOperand = operand;
                                        expression -> leftSubTree = prevExpression;
                                        rootNode = expression;
                                    }
                                    */
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
                                } else {
                                    /*
                                    expression -> operator = operator;
                                    expression -> leftOperand = operand;
                                    prevExpression -> rightSubTree = expression;
                                    */
                                    expression -> operator = operator;
                                    expression -> leftOperand = operand;
                                    expression -> isLeftSubTree = 0;
                                    prevExpression -> rightSubTree = expression;
                                    prevExpression -> isRightSubTree = 1;
                                }
                                break;
                    case '*':
                    case '/':   expression -> operator = operator;
                                if(operator == '+' || operator == '-'){
                                    /*
                                    prevExpression -> rightOperand = operand;
                                    expression -> leftSubTree = prevExpression;
                                    rootNode = expression;
                                    */
                                    prevExpression -> rightOperand = operand;
                                    prevExpression -> isRightSubTree = 0;
                                    expression -> leftSubTree = prevExpression;
                                    expression -> isLeftSubTree = 1;
                                    rootNode = expression;
                                } else {
                                    /*
                                    if(prevExpression -> leftSubTree != NULL){
                                        prevExpression -> rightSubTree = expression;
                                        expression -> leftOperand = operand;
                                    } else {
                                        prevExpression -> rightOperand = operand;
                                        expression -> leftSubTree = prevExpression;
                                        rootNode = expression;
                                    }
                                    */
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
                expression -> operator = operator;
                expression -> leftOperand = operand;
                expression -> isLeftSubTree = 0;
                rootNode = expression;
            }
            prevExpression = expression;
        } else {
            prevExpression -> rightOperand = operand;
            prevExpression -> isRightSubTree = 0;
        }
    }
    return 0;
}

int main(){
    readArithmaticExpression();
    //printArithmaticExpression();
    inorderTraversal(rootNode);
    printf("\n");
    return 0;
}
