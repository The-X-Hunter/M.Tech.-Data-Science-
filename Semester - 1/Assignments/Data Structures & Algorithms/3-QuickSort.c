/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: Quicksort.
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

int sort(int elements[], int low, int high){
    int pivot, i, j;
    if(low < high){
        pivot = (low + high) / 2;
        i = low;
        j = high;
        while(i < j){
            //Finds smaller than pivot element on the right side of pivot
            while(elements[i] <= elements[pivot]){
                i++;
            }
            //Finds greater than pivot element on the left side of pivot
            while(elements[j] > elements[pivot]){
                j--;
            }
            //When i crosses j then, there are no more smaller elements on the right side of pivot, else swap greater element from left side with smaller element from right side
            if(i < j){
                elements[i] += elements[j];
                elements[j] = elements[i] - elements[j];
                elements[i] -= elements[j];
                //If j were the index of pivot element then update pivot index by the index with which pivot is swapped
                pivot = (j == pivot) ? i : pivot;
            }
        }
        //If j is not on pivot then it is the actual position of pivot hence swap jth element with pivot
        if((j >= low) && (j != pivot)){
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
