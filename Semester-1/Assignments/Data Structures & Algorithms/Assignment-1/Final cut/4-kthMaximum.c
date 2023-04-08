/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: January 3, 2023 12.30.05 IST
    Objective: Find kth maximum element by partitioning the array.
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

//Finding kth maximum element using quick sort
int kthMaximum(int elements[], int low, int high, int k){
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
                //If j was the index of pivot element then update pivot index by the index with which pivot is swapped
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
        //If k is on left side of pivot, swap only left portion, else if it is on right side of pivot, swap only right portion
        if((k < pivot) && (low < pivot)){
            kthMaximum(elements, low, pivot - 1, k);
        } else if((k > pivot) && (high > pivot)){
            kthMaximum(elements, pivot + 1, high, k);
        }
    }
    return 0;
}

int main(){
    int i, elements[10], numberOfElements = 10, k = 6;
    for(i = 0; i < numberOfElements; i++){
        printf("Enter element %d: ", i + 1);
        scanf("%d", &elements[i]);
    }
    printf("Unsorted elements:\n");
    print(elements, numberOfElements);
    //This will find and print kth maximum element. Because it checks from ending of the array.
    kthMaximum(elements, 0, numberOfElements - 1, numberOfElements - k);
    printf("%d", k);
    if(k == 0 || k > 3){
        printf("th");
    } else if(k == 3){
        printf("rd");
    } else if(k == 2){
        printf("nd");
    } else {
        printf("st");
    }
    printf(" maximum element: %d\n", elements[numberOfElements - k]);
    return 0;
}
