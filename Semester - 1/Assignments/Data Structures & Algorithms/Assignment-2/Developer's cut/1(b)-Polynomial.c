#include<stdio.h>
#include<stdlib.h>

struct Operation{
    int co_officient;
    char variable;
    int power;
    char operator;
};

int numberOfTerms1, numberOfTerms2, numberOfTerms3, numberOfTerms4;
struct Operation * operation1, * operation2, * operation3, * operation4;

int printPolynomial(struct Operation operation[], int numberOfTerms){
    int i;
    for(i = 0; i < numberOfTerms; i++){
        printf("(%d * %c) ^ %d", operation[i].co_officient, operation[i].variable, operation[i].power);
        if(i + 1 < numberOfTerms){
            printf(" %c ", operation[i].operator);
        }
    }
    printf("\n");
    return 0;
}

struct Operation * multiplication(struct Operation operation1[], int numberOfTerms1, struct Operation operation2[], int numberOfTerms2){
    int i, j, k;
    struct Operation * operation;
    operation = (struct Operation *) malloc(sizeof(struct Operation) * (numberOfTerms1 * numberOfTerms2));
    i = 0;
    k = 0;
    while(i < numberOfTerms1){
        j = 0;
        while(j < numberOfTerms2){
            operation[k].co_officient = operation1[i].co_officient * operation2[j].co_officient;
            operation[k].power = operation1[i].power + operation2[j++].power;
            operation[k++].operator = '+';
        }
        i++;
    }
    operation[k - 1].operator = '\0';
    return operation;
}

struct Operation * addition(struct Operation operation1[], int numberOfTerms1, struct Operation operation2[], int numberOfTerms2){
    int i, j, k;
    struct Operation * operation;
    operation = (struct Operation *) malloc(sizeof(struct Operation) * (numberOfTerms1 + numberOfTerms2));
    if(numberOfTerms1 == 0){
        operation = operation2;
        numberOfTerms3 = numberOfTerms2;
    } else {
        if(numberOfTerms2 == 0){
            operation = operation1;
            numberOfTerms3 = numberOfTerms1;
        } else {
            i = 0, j = 0, k = 0;
            do {
                if(operation1[i].power == operation2[j].power){
                    if(operation1[i].variable == operation2[j].variable){
                        operation[k].co_officient = operation1[i].co_officient + operation2[j++].co_officient;
                        operation[k].variable = operation1[i].variable;
                        operation[k].power = operation1[i++].power;
                        operation[k].operator = '+';
                        /*
                        operation[k] = operation[i];
                        operation[k].co_officient = operation1[i++].co_officient + operation2[j++].co_officient;
                        operation[k].operator = '+';
                        */
                    } else {
                        if(operation1[i].variable > operation2[j].variable){
                            operation[k] = operation[i++];
                        } else {
                            operation[k] = operation[j++];
                        }
                    }
                } else {
                    if(operation1[i].power > operation2[j].power){
                        operation[k] = operation1[i++];
                    } else {
                        operation[k] = operation2[j++];
                    }
                }
                k++;
            } while(i < numberOfTerms1 && j < numberOfTerms2);
            while(i < numberOfTerms1){
                operation[k++] = operation1[i++];
            }
            while(j < numberOfTerms2){
                operation[k++] = operation2[j++];
            }
            operation[k - 1].operator = '\0';
            numberOfTerms3 = k;
        }
    }
    return operation;
}

int quickSort(struct Operation operation[], int low, int high, int * numberOfTerms){
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
                if(operation[i].power > pivotTermPower){
                    temp = operation[j];
                    operation[j] = operation[i];
                    operation[i] = temp;
                    j++;
                } else {
                    if(operation[i].variable == operation[pivotIndex].variable){
                        if(i > 0){
                            operation[i - 1].operator = operation[i].operator;
                        }
                        operation[pivotIndex].co_officient += operation[i].co_officient;
                        k = i;
                        while(k < pivotIndex){
                            operation[k] = operation[k + 1];
                            k++;
                        }
                        pivotIndex--;
                        high--;
                        numberOfTerms--;
                        i--;
                    } else if(operation[i].variable > operation[pivotIndex].variable){
                        tempOperator = operation[pivotIndex].operator;
                        operation[pivotIndex].operator = operation[i].operator;
                        operation[i].operator = tempOperator;
                        temp = operation[pivotIndex];
                        operation[pivotIndex] = operation[i];
                        operation[i] = temp;
                    }
                }
            }
            i++;
        }
        if(operation[j].power < operation[pivotIndex].power || operation[j].variable > operation[pivotIndex].variable){
            tempOperator = operation[pivotIndex].operator;
            operation[pivotIndex].operator = operation[j].operator;
            operation[j].operator = tempOperator;
            temp = operation[pivotIndex];
            operation[pivotIndex] = operation[j];
            operation[j] = temp;
        }
        quickSort(operation, low, j - 1, numberOfTerms);
        quickSort(operation, j + 1, high, numberOfTerms);
    }
    return 0;
}

int sortPolynomial(struct Operation operation[], int * numberOfTerms){
    int i, j, tempNumberOfTerms;
    tempNumberOfTerms = * numberOfTerms;
    for(i = 1; i < tempNumberOfTerms; i++){
        if(operation[i - 1].operator == '-'){
            operation[i - 1].operator = '+';
            operation[i].co_officient = -operation[i].co_officient;
        }
    }
    quickSort(operation, 0, tempNumberOfTerms - 1, numberOfTerms);
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

struct Operation * readPolynomial(int * numberOfTerms){
    int i, tempNumberOfTerms;
    struct Operation * operation;
    printf("Enter number of terms the polynomial will have: ");
    scanf("%d", &tempNumberOfTerms);
    operation = (struct Operation *) malloc(sizeof(struct Operation) * tempNumberOfTerms);
    for(i = 0; i < tempNumberOfTerms; i++){
        printf("Enter co-officient for this term: ");
        scanf("%d", &(operation[i].co_officient));
        printf("Enter variable: ");
        scanf(" %c", &(operation[i].variable));
        printf("Enter power of this term: ");
        scanf("%d", &(operation[i].power));
        //printf("%d * %c ^ %d\n", operation[i].co_officient, operation[i].variable, operation[i].power);
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
    operation2 = readPolynomial(&numberOfTerms2);
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
    if(numberOfTerms1 > 0 || numberOfTerms2 > 0){
        operation3 = addition(operation1, numberOfTerms1, operation2, numberOfTerms2);
        printf("Addition of expression1 & expression2:\n");
        printPolynomial(operation3, numberOfTerms3);
    } else {
        printf("Both expressions are empty.\n");
    }
    return 0;
}
