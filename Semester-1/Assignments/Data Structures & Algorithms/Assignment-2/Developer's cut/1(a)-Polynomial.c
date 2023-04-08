#include<stdio.h>
#include<stdlib.h>

struct Operation{
    int co_officient;
    char variable;
    int power;
    char operator;
};

int numberOfTerms;
struct Operation * operation;

int printPolynomial(){
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

int quickSort(int low, int high){
    int i, j, pivotIndex, pivotTermPower;
    struct Operation temp;
    char tempOperator;
    if(low < high){
        pivotIndex = high;
        i = low;
        j = i;
        pivotTermPower = operation[pivotIndex].power;
        while(i < high){
            if(operation[i].power >= pivotTermPower){
                temp = operation[j];
                operation[j] = operation[i];
                operation[i] = temp;
                j++;
            }
            i++;
        }
        tempOperator = operation[pivotIndex].operator;
        operation[pivotIndex].operator = operation[j].operator;
        operation[j].operator = tempOperator;
        temp = operation[pivotIndex];
        operation[pivotIndex] = operation[j];
        operation[j] = temp;
        quickSort(low, j - 1);
        quickSort(j + 1, high);
    }
    return 0;
}

int sortPolynomial(){
    int i, j;
    quickSort(0, numberOfTerms - 1);
    printPolynomial();
    return 0;
}

int readPolynomial(){
    int i;
    printf("Enter number of terms the polynomial will have: ");
    scanf("%d", &numberOfTerms);
    operation = (struct Operation *) malloc(sizeof(struct Operation *) * numberOfTerms);
    for(i = 0; i < numberOfTerms; i++){
        printf("Enter co-officient for this term: ");
        scanf("%d", &(operation[i].co_officient));
        printf("Enter variable: ");
        scanf(" %c", &(operation[i].variable));
        printf("Enter power of this term: ");
        scanf("%d", &(operation[i].power));
        //printf("%d * %c ^ %d\n", operation[i].co_officient, operation[i].variable, operation[i].power);
        if(i + 1 < numberOfTerms){
            printf("Enter operator: ");
            scanf(" %c", &(operation[i].operator));
        } else {
            operation[i].operator = '\0';
        }
    }
    return 0;
}

int main(){
    readPolynomial();
    printPolynomial();
    sortPolynomial();
    return 0;
}
