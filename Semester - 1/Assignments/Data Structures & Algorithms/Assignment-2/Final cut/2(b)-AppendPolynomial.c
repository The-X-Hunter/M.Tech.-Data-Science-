/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective:
        a)  Write a program using linked list with header node & sentinel value to read & print a polynomial.
        b)  Write another program to insert & delete a term of polynomial.
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

struct Operation * operationHead;

//This function print a polynomial expression on screen
int printPolynomial(struct Operation * operationHead){
    struct Operation * operation;
    operation = operationHead -> nextOperation;
    while(operation -> nextOperation != NULL){
        printf("(%d * (x ^ %d)) %c ", operation -> co_officient, operation -> power, operation -> operator);
        operation = operation -> nextOperation;
    }
    printf("(%d * (x ^ %d))\n", operation -> co_officient, operation -> power);
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

//This function append terms in existing polynomial
int appendPolynomial(struct Operation * operationHead){
    int flag, isAppended;
    struct Operation * operation, * prevOperation;
    flag = 0;
    isAppended = 0;
    prevOperation = operationHead;
    operation = operationHead -> nextOperation;
    //This loop set pointer to last term of given polynomial expresssion
    while(operation != NULL){
        prevOperation = operation;
        operation = operation -> nextOperation;
    }
    //This loop help in appending multiple terms
    do {
        printf("Enter new term:\n");
        operation = (struct Operation *) malloc(sizeof(struct Operation));
        //Ask for co-officient of each term
        printf("Enter co-officient for this term: ");
        scanf("%d", &(operation -> co_officient));
        //If given co-officient is 0 then assume that user don't want to append
        if(operation -> co_officient != 0){
            //If the term has '-' operator in left then replace it with '+' and negate the value of co-officient
            if(prevOperation != operationHead && prevOperation -> operator == '-'){
                operation -> co_officient = -(operation -> co_officient);
                prevOperation -> operator = '+';
            }
            //Ask for power of term
            printf("Enter power of this term: ");
            scanf("%d", &(operation -> power));
            //Ask user if he want to append more or not
            do {
                printf("Do you want to add more(0 or 1): ");
                scanf("%d", &flag);
            } while(flag != 0 && flag != 1);
            //If the term is not last one then ask for operator else insert '\0' in operator part
            if(flag == 1){
                do {
                    printf("Enter operator(+ or -): ");
                    scanf(" %c", &(operation -> operator));
                } while(operation -> operator != '+' && operation -> operator != '-');
            } else {
                operation -> operator = '\0';
            }
            //Append new term at the end of given polynomial expression
            prevOperation -> nextOperation = operation;
            prevOperation = operation;
            isAppended = 1;
        } else {
            //If entered co-officient is 0 then set '\0' as operator in last term of polynomial expresssion
            flag = 0;
            prevOperation -> operator = '\0';
        }
    } while(flag == 1);
    //If anything appended in polynomial expression then only call sort function
    if(isAppended == 1){
        sortPolynomial(operationHead);
    }
    return 0;
}

int deletePolynomialTerm(struct Operation * operationHead){
    int flag, isAppended, co_officient, power;
    struct Operation * operation, * prevOperation;
    flag = 0;
    isAppended = 0;
    if(operationHead -> nextOperation != NULL){
        printf("Enter co-officient of deleting term: ");
        scanf("%d", &co_officient);
        if(co_officient != 0){
            printf("Enter power of deleting term: ");
            scanf("%d", &power);
            prevOperation = operationHead;
            operation = operationHead -> nextOperation;
            while(operation != NULL && (operation -> power != power || operation -> co_officient != co_officient)){
                prevOperation = operation;
                operation = operation -> nextOperation;
            }
            if(operation != NULL){
                prevOperation -> nextOperation = operation -> nextOperation;
                operation -> nextOperation = NULL;
                free(operation);
            } else {
                printf("Given term not found.\n");
            }
        } else {
            printf("0 is not a valid co-officient.\n");
        }
    } else {
        printf("Nothing to delete.\n");
    }
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
    operationHead = (struct Operation *) malloc(sizeof(struct Operation));
    operationHead -> nextOperation = NULL;
    readPolynomial(operationHead);
    printf("------------------------------------------\n");
    printf("Before sorting:\n");
    printf("Expression1:\t");
    printPolynomial(operationHead);
    sortPolynomial(operationHead);
    printf("After sorting:\n");
    printf("Expression1:\t");
    if(operationHead -> nextOperation != NULL){
        printPolynomial(operationHead);
    } else {
        printf("Expression is empty.\n");
    }
    printf("------------------------------------------\n");
    appendPolynomial(operationHead);
    printf("------------------------------------------\n");
    printf("After appending & sorting:\n");
    printf("Expression1:\t");
    if(operationHead -> nextOperation != NULL){
        printPolynomial(operationHead);
    } else {
        printf("Expression is empty.\n");
    }
    printf("------------------------------------------\n");
    deletePolynomialTerm(operationHead);
    printf("After deleting a term from polynomial:\n");
    printf("Expression1:\t");
    if(operationHead -> nextOperation != NULL){
        printPolynomial(operationHead);
    } else {
        printf("Expression is empty.\n");
    }
    return 0;
}
