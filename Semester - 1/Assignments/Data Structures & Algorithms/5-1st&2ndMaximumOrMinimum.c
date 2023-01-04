/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective:
*/

#include<stdio.h>
#include<math.h>

int sequence[] = {2, 5, 10, 2, 4};

int printHeap(int heap[], int numberOfElements){
    int i, j, power, index = 0;
    for(i = 0; (i < numberOfElements) && (index < numberOfElements); i++){
        power = (int) pow(2, i);
        for(j = 0; (j < power) && (index < numberOfElements); j++){
            printf("%d\t", heap[index]);
            index++;
        }
        printf("\n");
    }
}

int findMinimum(int sequence[], int numberOfElements){
    int i, j, parentIndex;
    int minHeap[numberOfElements];
    for(i = 0; i < numberOfElements; i++){
        minHeap[i] = sequence[i];
    }
    for(i = 0; i < numberOfElements; i++){
        j = i;
        while(j > 0){
            parentIndex = j / 2;
            if(minHeap[parentIndex] > sequence[i]){
                minHeap[j] = minHeap[parentIndex];
                j = parentIndex;
            } else {
                break;
            }
        }
        minHeap[j] = sequence[i];
    }
    printf("Min heap:\n");
    printHeap(minHeap, numberOfElements);
    printf("So the 1st & 2nd minimums are %d & %d, respectively.\n", minHeap[0], minHeap[1]);
    printf("******************************************\n");
    return 0;
}

int findMaximum(int sequence[], int numberOfElements){
    int i, j, parentIndex;
    int maxHeap[numberOfElements];
    for(i = 0; i < numberOfElements; i++){
        maxHeap[i] = sequence[i];
    }
    for(i = 0; i < numberOfElements; i++){
        j = i;
        while(j > 0){
            parentIndex = j / 2;
            if(maxHeap[parentIndex] < sequence[i]){
                maxHeap[j] = maxHeap[parentIndex];
                j = parentIndex;
            } else {
                break;
            }
        }
        maxHeap[j] = sequence[i];
    }
    printf("Max heap:\n");
    printHeap(maxHeap, numberOfElements);
    printf("So the 1st & 2nd maximums are %d & %d, respectively.\n", maxHeap[0], maxHeap[1]);
    printf("******************************************\n");
    return 0;
}

int main(){
    findMinimum(sequence, 5);
    findMaximum(sequence, 5);
    return 0;
}
