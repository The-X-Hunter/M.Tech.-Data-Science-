/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: 
*/

#include<stdio.h>

int print(int sortedArray[], int numberOfElements){
    int i;
    for(i = 0; i < numberOfElements; i++){
        printf("%d\t", sortedArray[i]);
    }
    printf("\n");
    return 0;
}

int removeDuplicates(int sortedArray[], int numberOfElements){
    int i, j, currElement;
    for(i = 0, j = 0; (i < numberOfElements) && (j < numberOfElements); j++){
        if(sortedArray[j] != sortedArray[j + 1]){
            sortedArray[i++] = sortedArray[j];
        }
    }
    while(i < numberOfElements){
        sortedArray[i++] = 0;
    }
    return 0;
}

int main(){
    int sortedArray[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    printf("Prior removal of duplicates: \n");
    print(sortedArray, 15);
    removeDuplicates(sortedArray, 15);
    printf("After removal of duplicates:\n");
    print(sortedArray, 15);
    return 0;
}
