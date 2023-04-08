/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: January 3, 2023 14.10.05 IST
    Objective: Write an efficient program to delete duplicate elements from a sorted array.
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
    int i, j, lastIndex;
    lastIndex = numberOfElements - 1;
    //This loop considers last element as a distinct one. So, it starts from 0th element and go upto second last element.
    for(i = 0, j = 0; i < lastIndex; i++){
        /*
        Checks whether two adjacent elements are equal or not.
        If they aren't then replace jth element with ith element and place j on next position.
        */
        if(sortedArray[i] != sortedArray[i + 1]){
            sortedArray[j++] = sortedArray[i];
        }
    }
    /*
    j will be on position where last distinct element should be inserted.
    Previous loop considered last element as a distinct one, so insert it on jth position.
    */
    sortedArray[j] = sortedArray[lastIndex];
    //j inserted in lastIndex and then incremented.
    lastIndex = j++;
    //All positions after lastIndex will be assiged 0.
    while(j < numberOfElements){
        sortedArray[j++] = 0;
    }
    //This prints sub-array with distinct elements.
    printf("After removal of duplicates:\n");
    print(sortedArray, lastIndex + 1);
    return 0;
}

int main(){
    int sortedArray[] = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5};
    printf("Prior removal of duplicates: \n");
    print(sortedArray, 15);
    removeDuplicates(sortedArray, 15);
    return 0;
}
