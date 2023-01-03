/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: 
*/

#include<stdio.h>
#include<stdlib.h>

int print(int elements[], int numberOfElements){
    int i;
    for(i = 0; i < numberOfElements; i++){
        printf("%d\t", elements[i]);
    }
    printf("\n");
    return 0;
}

/*
int insert(int elements[], int numberOfElements){
    printf("Size: %d\n", sizeof(elements)/sizeof(int));
    int i, tempElements[numberOfElements];
    for(i = 0; i < numberOfElements; i++){
        printf("Enter element %d: ", i + 1);
        scanf("%d", elements[i]);
    }
    return 0;
}
*/

int sort(int elements[], int low, int high){
    int pivot, i, j;
    if(low != high){
        pivot = (low + high) / 2;
        i = low;
        j = high;
        while(i <= j){
            while(elements[i] <= elements[pivot]){
                i++;
            }
            while(elements[j] > elements[pivot]){
                j--;
            }
            if(i > j){
                break;
            } else {
                elements[i] += elements[j];
                elements[j] = elements[i] - elements[j];
                elements[i] -= elements[j];
            }
        }
        if((j <= high) && (j != pivot)){
            elements[pivot] += elements[j];
            elements[j] = elements[pivot] - elements[j];
            elements[pivot] -= elements[j];
            pivot = j;
        }
        if(low < pivot){
            sort(elements, low, pivot - 1);
        }
        if(high > pivot){
            sort(elements, pivot + 1, high);
        }
    }
    return 0;
}

int main(){
    /*
    int numberOfElements, * elements;
    printf("Number of elements to be sorted: ");
    scanf("%d", &numberOfElements);
    elements = (int *) malloc(numberOfElements * sizeof(int));
    insert(elements, numberOfElements);
    */
    int i, elements[10];
    for(i = 0; i < 10; i++){
        printf("Enter element %d: ", i + 1);
        scanf("%d", &elements[i]);
    }
    printf("Unsorted elements:\n");
    print(elements, 10);
    sort(elements, 0, 9);
    printf("Sorted elements:\n");
    print(elements, 10);
    return 0;
}
