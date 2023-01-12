/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: January 3, 2023 12.45.05 IST
    Objective: Find longest monotonically increasing sequence from an array.
*/

#include<stdio.h>

int findMonotonicallyIncreasing(int sequence[], int numberOfElements){
    int i, startIndex = 0, sequenceLength, monotonicallyIncreasingElements = 0;
    //This loop will traverse entire sequence.
    for(i = 0; i < numberOfElements; i++){
        //If there are not a single increasing sequence then the first element will be considered as an element of monotonically increasing sequence and length will be 1.
        sequenceLength = 1;
        //This loop compares adjacent elements and increase length if they are in increasing fashion.
        while((i + 1 < numberOfElements) && (sequence[i] <= sequence[i + 1])){
            sequenceLength++;
            i++;
        }
        //If the previously found sub-sequence length is lesser than the new one then update length field and save starting index of new sub-sequence.
        if(sequenceLength > monotonicallyIncreasingElements){
            monotonicallyIncreasingElements = sequenceLength;
            startIndex = (i + 1) - monotonicallyIncreasingElements;
        }
    }
    //Prints monotonically increasing sequence.
    monotonicallyIncreasingElements += startIndex;
    printf("\nMonotonically increasing sub-sequence with %d element(s) is as follow:\n", monotonicallyIncreasingElements);
    for(i = startIndex; i < monotonicallyIncreasingElements; i++){
        printf("%d\t", sequence[i]);
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
