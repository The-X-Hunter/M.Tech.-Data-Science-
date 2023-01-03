/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Objective: 
*/

#include<stdio.h>

int findMonotonicallyIncreasing(int sequence[], int numberOfElements){
    int i, startIndex = 0, currIndex, monotonicallyIncreasingElements = 0;
    i = 0;
    while(i < numberOfElements){
        currIndex = 1;
        while((sequence[i] <= sequence[i + 1]) && (i + 1 < numberOfElements)){
            currIndex++;
            i++;
        }
        if(currIndex > monotonicallyIncreasingElements){
            monotonicallyIncreasingElements = currIndex;
            startIndex = (i + 1) - monotonicallyIncreasingElements;
        }
        i++;
    }
    printf("\nMonotonically increasing sub-sequence with %d element(s) is as follow:\n", monotonicallyIncreasingElements);
    for(i = 0; i < monotonicallyIncreasingElements; i++){
        printf("%d\t", sequence[startIndex + i]);
    }
    printf("\n");
    return 0;
}

int main(){
    int sequence[] = {5, 2, 7, 92, 36, 78, 31, 11, 67321, 334};
    int i;
    printf("Original sequence:\n");
    for(i = 0; i < 10; i++){
        printf("%d\t", sequence[i]);
    }
    findMonotonicallyIncreasing(sequence, 10);
    return 0;
}
