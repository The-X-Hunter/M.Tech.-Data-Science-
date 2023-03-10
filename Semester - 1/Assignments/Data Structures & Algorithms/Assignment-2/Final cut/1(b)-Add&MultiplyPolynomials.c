/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective:
        a)  Write a program using arrays to read & print a polynomial.
        b)  Write a program to add & multiply two polynomials.
*/

#include<stdio.h>
#include<stdlib.h>

//Node to store a term of a polynomial expression
struct Operation{
    int co_officient;
    int power;
    char operator;
};

//Sizes of plynomial expressions
int numberOfTerms1, numberOfTerms2, numberOfTerms3, numberOfTerms4;
//Arrays to store polynomial expressions
struct Operation * operation1, * operation2, * operation3, * operation4;

//This function print a polynomial expression on screen
int printPolynomial(struct Operation operation[], int numberOfTerms){
    int i;
    for(i = 0; i < numberOfTerms; i++){
        printf("(%d * (x ^ %d))", operation[i].co_officient, operation[i].power);
        if(i + 1 < numberOfTerms){
            printf(" %c ", operation[i].operator);
        }
    }
    printf("\n");
    return 0;
}

//This function sorts a polynomial expression in decreasing order based on power of a variable & returns updated size of polynomial expression
int quickSort(struct Operation operation[], int low, int high, int numberOfTerms){
    int i, j, k, pivotIndex, pivotTermPower;
    struct Operation temp;
    char tempOperator;
    if(low < high){
        pivotIndex = high;
        i = low;
        j = i;
        pivotTermPower = operation[pivotIndex].power;
        while(i < high){
            if(operation[i].power >= pivotTermPower){
                //If power of ith element is greater than power of the element on pivot index then swap them
                if(operation[i].power > pivotTermPower){
                    temp = operation[j];
                    operation[j] = operation[i];
                    operation[i] = temp;
                    j++;
                } else {
                    //If power of ith element and power of the element on pivot index are same then first copy operator from right side of ith element and insert at left
                    if(i > 0){
                        operation[i - 1].operator = operation[i].operator;
                    }
                    //Then add both elements' co-officients
                    operation[pivotIndex].co_officient += operation[i].co_officient;
                    //Now to remove ith element, start from ith position & shift every element to its left.
                    k = i;
                    while(k < numberOfTerms){
                        operation[k] = operation[k + 1];
                        k++;
                    }
                    //Pivot should have shifted to one position left so decrease the pivot index as well as high & total number of terms a polynomial has
                    pivotIndex--;
                    high--;
                    numberOfTerms--;
                    //Since each element shifted to left, i also should go one step down for better comparison
                    i--;
                }
            }
            i++;
        }
        //If power of jth element is less than power of the element on pivot index then only swap them and also swap their respective operators
        if(operation[j].power < operation[pivotIndex].power){
            tempOperator = operation[pivotIndex].operator;
            operation[pivotIndex].operator = operation[j].operator;
            operation[j].operator = tempOperator;
            temp = operation[pivotIndex];
            operation[pivotIndex] = operation[j];
            operation[j] = temp;
        }
        numberOfTerms = quickSort(operation, low, j - 1, numberOfTerms);
        numberOfTerms = quickSort(operation, j + 1, high, numberOfTerms);
    }
    return numberOfTerms;
}

//This function call the sorting function and after sort it check for elements with co-officient 0 and remove them
int sortPolynomial(struct Operation operation[], int * numberOfTerms){
    int i, j, tempNumberOfTerms;
    tempNumberOfTerms = * numberOfTerms;
    * numberOfTerms = quickSort(operation, 0, tempNumberOfTerms - 1, tempNumberOfTerms);
    tempNumberOfTerms = * numberOfTerms;
    for(i = 0; i < tempNumberOfTerms; i++){
        if(operation[i].co_officient == 0){
            if(i + 1 < tempNumberOfTerms){
                operation[i] = operation[i + 1];
                * numberOfTerms = --tempNumberOfTerms;
                i--;
            } else {
                * numberOfTerms = --tempNumberOfTerms;
            }
        }
    }
    return 0;
}

//This function multiplies two polynomial expressions and return the result
struct Operation * multiplication(struct Operation operation1[], int numberOfTerms1, struct Operation operation2[], int numberOfTerms2, int * numberOfTerms){
    int i, j, k;
    //This could be the maximum size of multiplication result of two polynomials
    * numberOfTerms = numberOfTerms1 * numberOfTerms2;
    //This store the result of multiplication of two polynomils
    struct Operation * operation;
    operation = (struct Operation *) malloc(sizeof(struct Operation) * (* numberOfTerms));
    i = 0;
    k = 0;
    while(i < numberOfTerms1){
        j = 0;
        while(j < numberOfTerms2){
            //Multiplies co-officients of both the polynomials
            operation[k].co_officient = operation1[i].co_officient * operation2[j].co_officient;
            //Add power of both the multiplied polynomial terms
            operation[k].power = operation1[i].power + operation2[j++].power;
            operation[k++].operator = '+';
        }
        i++;
    }
    operation[k - 1].operator = '\0';
    //Sorting is needed here because after multiplication it requires to simplify it, this will remove redundar terms (terms with same power)
    sortPolynomial(operation, numberOfTerms);
    return operation;
}

//This function add two polynomials and return its result
struct Operation * addition(struct Operation operation1[], int numberOfTerms1, struct Operation operation2[], int numberOfTerms2, int * numberOfTerms){
    int i, j, k;
    struct Operation * operation;
    //This could be the maximum size of addition result of two polynomials
    operation = (struct Operation *) malloc(sizeof(struct Operation) * (numberOfTerms1 + numberOfTerms2));
    if(numberOfTerms1 == 0){
        //If first polynomial expression is empty then only second polynomial will be the result of addition
        operation = operation2;
        * numberOfTerms = numberOfTerms2;
    } else {
        if(numberOfTerms2 == 0){
            //If second polynomial expression is empty then only first polynomial will be the result of addition
            operation = operation1;
            * numberOfTerms = numberOfTerms1;
        } else {
            i = 0, j = 0, k = 0;
            do {
                //If power are same then add co-officient of both the terms and copy power of those terms
                if(operation1[i].power == operation2[j].power){
                    operation[k].co_officient = operation1[i].co_officient + operation2[j++].co_officient;
                    operation[k].power = operation1[i++].power;
                } else {
                    //Copy that term which has greater power
                    if(operation1[i].power > operation2[j].power){
                        operation[k] = operation1[i++];
                    } else {
                        operation[k] = operation2[j++];
                    }
                }
                operation[k++].operator = '+';
            } while(i < numberOfTerms1 && j < numberOfTerms2);
            //Copy any left term from first polynomial expression
            while(i < numberOfTerms1){
                operation[k++] = operation1[i++];
            }
            //Copy any left term from second polynomial expression
            while(j < numberOfTerms2){
                operation[k++] = operation2[j++];
            }
            operation[k - 1].operator = '\0';
            * numberOfTerms = k;
        }
    }
    return operation;
}

//This function ask for polynomial expression from user
struct Operation * readPolynomial(int * numberOfTerms){
    int i, tempNumberOfTerms;
    struct Operation * operation;
    //Ask for total number of term a polynomial will have
    printf("Enter number of terms the polynomial will have: ");
    scanf("%d", &tempNumberOfTerms);
    operation = (struct Operation *) malloc(sizeof(struct Operation) * tempNumberOfTerms);
    for(i = 0; i < tempNumberOfTerms; i++){
        //Ask for co-officient of each term
        printf("Enter co-officient for this term: ");
        scanf("%d", &(operation[i].co_officient));
        //If the term has '-' operator in left then replace it with '+' and negate the value of co-officient
        if(i > 0 && operation[i - 1].operator == '-'){
            operation[i].co_officient = -operation[i].co_officient;
            operation[i - 1].operator = '+';
        }
        //Ask for power of term
        printf("Enter power of this term: ");
        scanf("%d", &(operation[i].power));
        //If the term is not last one then ask for operator else insert '\0' in operator part
        if(i + 1 < tempNumberOfTerms){
            do {
                printf("Enter operator(+ or -): ");
                scanf(" %c", &(operation[i].operator));
            } while(operation[i].operator != '+' && operation[i].operator != '-');
        } else {
            operation[i].operator = '\0';
        }
    }
    * numberOfTerms = tempNumberOfTerms;
    return operation;
}

int main(){
    operation1 = readPolynomial(&numberOfTerms1);
    printf("------------------------------------------\n");
    operation2 = readPolynomial(&numberOfTerms2);
    printf("------------------------------------------\n");
    printf("Before sorting:\n");
    printf("Expression1:\t");
    printPolynomial(operation1, numberOfTerms1);
    printf("Expression2:\t");
    printPolynomial(operation2, numberOfTerms2);
    sortPolynomial(operation1, &numberOfTerms1);
    sortPolynomial(operation2, &numberOfTerms2);
    printf("After sorting:\n");
    printf("Expression1:\t");
    operation1 = (struct Operation *) realloc(operation1, sizeof(struct Operation) * numberOfTerms1);
    operation2 = (struct Operation *) realloc(operation2, sizeof(struct Operation) * numberOfTerms2);
    if(numberOfTerms1 > 0){
        printPolynomial(operation1, numberOfTerms1);
    } else {
        printf("Expression is empty.\n");
    }
    printf("Expression2:\t");
    if(numberOfTerms2 > 0){
        printPolynomial(operation2, numberOfTerms2);
    } else {
        printf("Expression is empty.\n");
    }
    printf("------------------------------------------\n");
    printf("Addition of expression1 & expression2:\n");
    if(numberOfTerms1 > 0 || numberOfTerms2 > 0){
        operation3 = addition(operation1, numberOfTerms1, operation2, numberOfTerms2, &numberOfTerms3);
        operation3 = (struct Operation *) realloc(operation3, sizeof(struct Operation) * numberOfTerms3);
        printPolynomial(operation3, numberOfTerms3);
    } else {
        printf("Addition is 0.\n");
    }
    printf("Multiplication of expression1 & expression2:\n");
    if(numberOfTerms1 > 0 && numberOfTerms2 > 0){
        operation4 = multiplication(operation1, numberOfTerms1, operation2, numberOfTerms2, &numberOfTerms4);
        operation4 = (struct Operation *) realloc(operation4, sizeof(struct Operation) * numberOfTerms4);
        printPolynomial(operation4, numberOfTerms4);
    } else {
        printf("Multiplication is 0.\n");
    }
    return 0;
}
