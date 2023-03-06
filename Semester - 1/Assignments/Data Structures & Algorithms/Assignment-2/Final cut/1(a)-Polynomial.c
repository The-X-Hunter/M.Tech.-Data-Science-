#include<stdio.h>
#include<stdlib.h>

//Node to store a term of a polynomial expression
struct Operation{
    int co_officient;
    int power;
    char operator;
};

//Total number of terms a polynomial expression can have
int numberOfTerms1;

//An array to store polynomial expression
struct Operation * operation1;

//This function print a polynomial expression on screen
int printPolynomial(struct Operation operation[], int numberOfTerms){
    int i;
    for(i = 0; i < numberOfTerms; i++){
        printf("(%d * %c) ^ %d", operation[i].co_officient, 'x', operation[i].power);
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
    printf("Before sorting:\n");
    printf("Expression1:\t");
    printPolynomial(operation1, numberOfTerms1);
    sortPolynomial(operation1, &numberOfTerms1);
    printf("After sorting:\n");
    printf("Expression1:\t");
    operation1 = (struct Operation *) realloc(operation1, sizeof(struct Operation) * numberOfTerms1);
    if(numberOfTerms1 > 0){
        printPolynomial(operation1, numberOfTerms1);
    } else {
        printf("Expression is empty.\n");
    }
    return 0;
}
