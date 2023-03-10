/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective:
        a)  Write a program using linked list with header node & sentinel value to read & print a polynomial.
        b)  Write another program to insert & deletea term of polynomial.
        c)  Write a program to add & multiply two polynomials.
*/

#include<stdio.h>
#include<stdlib.h>

//Node to store a term of a polynomial expression
struct Operation{
    int co_officient;
    int power;
    char operator;
    struct Operation * nextOperation;
};

struct Operation * operationHead1, * operationHead2, * operationHead3, * operationHead4;

//This function print a polynomial expression on screen
int printPolynomial(struct Operation * operationHead){
    struct Operation * operation;
    operation = operationHead -> nextOperation;
    while(operation -> nextOperation != NULL){
        printf("(%d * (x ^ %d)) %c ", operation -> co_officient, operation -> power, operation -> operator);
        operation = operation -> nextOperation;
    }
    printf("((%d * x) ^ %d)\n", operation -> co_officient, operation -> power);
    return 0;
}

//This function sorts a polynomial expression in decreasing order based on power of a variable
int sortPolynomial(struct Operation * operationHead){
    //Since it is insertion sort, we need to take care of unsorted as well as sorted part
    struct Operation * unsortedOperation, *sortedOperationTraverser, *unsortedOperationTraverser;
    unsortedOperationTraverser = operationHead -> nextOperation;
    //Check whether list is empty or not
    if(unsortedOperationTraverser != NULL){
        //This pointer points to first element of unsorted part
        unsortedOperation = unsortedOperationTraverser -> nextOperation;
        //Continue till elements are there in unsorted part
        while(unsortedOperation != NULL){
            /*
            Start from first element of sorted part, compare power of each element of sorted part with the first element of unsorted part
            If power is greater than then leave it as it is
            */
            sortedOperationTraverser = operationHead;
            while(sortedOperationTraverser -> nextOperation -> power > unsortedOperation -> power && sortedOperationTraverser -> nextOperation != unsortedOperation) {
                sortedOperationTraverser = sortedOperationTraverser -> nextOperation;
            }
            /*
            If loop stopped on the element which has less than or equal power as first element of unsorted part
            AND
            the element shouldn't be the first element of unsorted part
            */
            if(sortedOperationTraverser -> nextOperation -> power <= unsortedOperation -> power && sortedOperationTraverser -> nextOperation != unsortedOperation){
                //If power is lesser than unsorted one then remove element from unsorted part and append just before the element with lesser power in sorted partss
                if(sortedOperationTraverser -> nextOperation -> power < unsortedOperation -> power){
                    unsortedOperationTraverser -> nextOperation = unsortedOperation -> nextOperation;
                    unsortedOperation -> nextOperation = sortedOperationTraverser -> nextOperation;
                    sortedOperationTraverser -> nextOperation = unsortedOperation;
                    unsortedOperation -> operator = '+';
                } else {
                    //If power is same then add co-officient of both the elements and remove element from unsorted part
                    unsortedOperationTraverser -> nextOperation = unsortedOperation -> nextOperation;
                    unsortedOperation -> nextOperation = NULL;
                    sortedOperationTraverser -> nextOperation -> co_officient = (unsortedOperation -> co_officient) + (sortedOperationTraverser -> nextOperation -> co_officient);
                    free(unsortedOperation);
                    //If sum of co-officients become 0 then remove that element from sorted parts
                    if(sortedOperationTraverser -> nextOperation -> co_officient == 0){
                        sortedOperationTraverser -> nextOperation = sortedOperationTraverser -> nextOperation -> nextOperation;
                        free(sortedOperationTraverser -> nextOperation);
                    }
                }
            } else {
                //If loop stopped on the first element of unsorted part then move beginning pointer of unsorted part to one element right
                unsortedOperationTraverser = unsortedOperationTraverser -> nextOperation;
            }
            //Choose new element from unsorted parts
            unsortedOperation = unsortedOperationTraverser -> nextOperation;
        }
        //Make nextOperation pointer NULL of the last element
        unsortedOperationTraverser -> nextOperation = NULL;
    }
    return 0;
}

//This function add two polynomials and return its result
int addition(struct Operation * operationHead1, struct Operation * operationHead2, struct Operation * operationHead3){
    struct Operation * currOperation1, * currOperation2, * currOperation3, * operation;
    currOperation1 = operationHead1 -> nextOperation;
    currOperation2 = operationHead2 -> nextOperation;
    currOperation3 = operationHead3;
    //Go untill one of the expression is processed
    while(currOperation1 != NULL && currOperation2 != NULL){
        operation = (struct Operation *) malloc(sizeof(struct Operation));
        //Copy the term which has higher power among both the expressions else add their co-officients
        if(currOperation1 -> power > currOperation2 -> power){
            operation -> co_officient = currOperation1 -> co_officient;
            operation -> power = currOperation1 -> power;
            operation -> operator = currOperation1 -> operator;
            operation -> nextOperation = NULL;
            currOperation1 = currOperation1 -> nextOperation;
        } else if(currOperation1 -> power < currOperation2 -> power){
            operation -> co_officient = currOperation2 -> co_officient;
            operation -> power = currOperation2 -> power;
            operation -> operator = currOperation2 -> operator;
            operation -> nextOperation = NULL;
            currOperation2 = currOperation2 -> nextOperation;
        } else {
            operation -> co_officient = (currOperation1 -> co_officient) + (currOperation2 -> co_officient);
            operation -> power = currOperation1 -> power;
            operation -> operator = currOperation1 -> operator;
            operation -> nextOperation = NULL;
            currOperation1 = currOperation1 -> nextOperation;
            currOperation2 = currOperation2 -> nextOperation;
        }
        currOperation3 -> nextOperation = operation;
        currOperation3 = operation;
    }
    //Copy remaining terms from polynomial1
    while(currOperation1 != NULL){
        operation = (struct Operation *) malloc(sizeof(struct Operation));
        operation -> co_officient = currOperation1 -> co_officient;
        operation -> power = currOperation1 -> power;
        operation -> operator = currOperation1 -> operator;
        operation -> nextOperation = NULL;
        currOperation1 = currOperation1 -> nextOperation;
        currOperation3 -> nextOperation = operation;
        currOperation3 = operation;
    }
    //Copy remaining terms from polynomial2
    while(currOperation2 != NULL){
        operation = (struct Operation *) malloc(sizeof(struct Operation));
        operation -> co_officient = currOperation2 -> co_officient;
        operation -> power = currOperation2 -> power;
        operation -> operator = currOperation2 -> operator;
        operation -> nextOperation = NULL;
        currOperation2 = currOperation2 -> nextOperation;
        currOperation3 -> nextOperation = operation;
        currOperation3 = operation;
    }
    //In last term of resulting polynomial, put '\0' as operator
    currOperation3 -> operator = '\0';
    return 0;
}

//This function multiplies two polynomial expressions and return the result
int multiplication(struct Operation * operationHead1, struct Operation * operationHead2, struct Operation * operationHead4){
    struct Operation * currOperation1, * currOperation2, * currOperation3, * operation;
    currOperation1 = operationHead1 -> nextOperation;
    currOperation3 = operationHead4;
    //Multiply each term of polynomial1 with each term of polynomial2
    while(currOperation1 != NULL){
        currOperation2 = operationHead2 -> nextOperation;
        while(currOperation2 != NULL){
            operation = (struct Operation *) malloc(sizeof(struct Operation));
            operation -> co_officient = (currOperation1 -> co_officient) * (currOperation2 -> co_officient);
            operation -> power = (currOperation1 -> power) + (currOperation2 -> power);
            operation -> operator = currOperation1 -> operator;
            operation -> nextOperation = NULL;
            currOperation2 = currOperation2 -> nextOperation;
            currOperation3 -> nextOperation = operation;
            currOperation3 = operation;
        }
        currOperation1 = currOperation1 -> nextOperation;
    }
    //In last term of resulting polynomial, put '\0' as operator
    currOperation3 -> operator = '\0';
    //Sorting is needed here because after multiplication it requires to simplify it, this will remove redundar terms (terms with same power)
    sortPolynomial(operationHead4);
    return 0;
}

//This function ask for polynomial expression from user
int readPolynomial(struct Operation * operationHead){
    int i, numberOfTerms;
    struct Operation * operation, * prevOperation;
    prevOperation = operationHead;
    //Ask for total number of term a polynomial will have
    printf("Enter number of terms the polynomial will have: ");
    scanf("%d", &numberOfTerms);
    for(i = 0; i < numberOfTerms; i++){
        operation = (struct Operation *) malloc(sizeof(struct Operation));
        //Ask for co-officient of each term
        printf("Enter co-officient for this term: ");
        scanf("%d", &(operation -> co_officient));
        //If the term has '-' operator in left then replace it with '+' and negate the value of co-officient
        if(prevOperation != operationHead && prevOperation -> operator == '-'){
            operation -> co_officient = -(operation -> co_officient);
            prevOperation -> operator = '+';
        }
        //Ask for power of term
        printf("Enter power of this term: ");
        scanf("%d", &(operation -> power));
        //If the term is not last one then ask for operator else insert '\0' in operator part
        if(i + 1 < numberOfTerms){
            do {
                printf("Enter operator(+ or -): ");
                scanf(" %c", &(operation -> operator));
            } while(operation -> operator != '+' && operation -> operator != '-');
        } else {
            operation -> operator = '\0';
        }
        operation -> nextOperation = NULL;
        prevOperation -> nextOperation = operation;
        prevOperation = operation;
    }
}

int main() {
    operationHead1 = (struct Operation *) malloc(sizeof(struct Operation));
    operationHead1 -> nextOperation = NULL;
    readPolynomial(operationHead1);
    printf("------------------------------------------\n");
    operationHead2 = (struct Operation *) malloc(sizeof(struct Operation));
    operationHead2 -> nextOperation = NULL;
    readPolynomial(operationHead2);
    printf("------------------------------------------\n");
    printf("Before sorting:\n");
    printf("Expression1:\t");
    printPolynomial(operationHead1);
    sortPolynomial(operationHead1);
    printf("Expression2:\t");
    printPolynomial(operationHead2);
    sortPolynomial(operationHead2);
    printf("------------------------------------------\n");
    printf("After sorting:\n");
    printf("Expression1:\t");
    if(operationHead1 -> nextOperation != NULL){
        printPolynomial(operationHead1);
    } else {
        printf("Expression is empty.\n");
    }
    printf("Expression2:\t");
    if(operationHead2 -> nextOperation != NULL){
        printPolynomial(operationHead2);
    } else {
        printf("Expression is empty.\n");
    }
    printf("------------------------------------------\n");
    printf("Addition of expression1 & expression2:\n");
    operationHead3 = (struct Operation *) malloc(sizeof(struct Operation));
    operationHead3 -> nextOperation = NULL;
    if(operationHead1 -> nextOperation != NULL || operationHead2 -> nextOperation != NULL){
        addition(operationHead1, operationHead2, operationHead3);
        printPolynomial(operationHead3);
    } else {
        printf("Addition is 0.\n");
    }
    printf("------------------------------------------\n");
    printf("Multiplication of expression1 & expression2:\n");
    operationHead4 = (struct Operation *) malloc(sizeof(struct Operation));
    operationHead4 -> nextOperation = NULL;
    if(operationHead1 -> nextOperation != NULL && operationHead2 -> nextOperation != NULL){
        multiplication(operationHead1, operationHead2, operationHead4);
        printPolynomial(operationHead4);
    } else {
        printf("Multiplication is 0.\n");
    }
    return 0;
}
