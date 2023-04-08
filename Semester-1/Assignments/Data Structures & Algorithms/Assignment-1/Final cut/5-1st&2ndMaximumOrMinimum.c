/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 3, 2022 15.38.05 IST
    Objective: Find 1st & 2nd maximum as well as minimum elements from given sequence.
*/

#include<stdio.h>
#include<math.h>

int sequence[] = {2, 5, 10, 2, 4};

//This prints elements from array
int print(int numberOfElements){
    int i;
    printf("Sequence is:\n");
    for(i = 0; i < numberOfElements; i++){
        printf("%d\t", sequence[i]);
    }
    printf("\n");
    return 0;
}

int main(){
    int i, currElement, firstMinimum, secondMinimum, secondMaximum, firstMaximum, numberOfElements = 5;
    //Following code is for finding 1st, 2nd maximums & minimums without any sorting and also with a single loop.
    print(numberOfElements);
    //Compares 1st & 2nd element and assign appropriate pointer to them.
    if(sequence[0] <= sequence[1]){
        firstMinimum = sequence[0];
        secondMinimum = sequence[1];
        secondMaximum = sequence[0];
        firstMaximum = sequence[1];
    } else {
        firstMinimum = sequence[1];
        secondMinimum = sequence[0];
        secondMaximum = sequence[1];
        firstMaximum = sequence[0];
    }
    //Keeps comparing all the elements of sequence with values pointed by the pointers and updates pointers when neccessary.
    for(i = 2; i < numberOfElements; i++){
        currElement = sequence[i];
        if(currElement > firstMaximum){
            secondMaximum = firstMaximum;
            firstMaximum = currElement;
        } else if(currElement > secondMaximum){
            secondMaximum = currElement;
        }
        if(currElement < firstMinimum){
            secondMinimum = firstMinimum;
            firstMinimum = currElement;
        } else if(currElement < secondMinimum){
            secondMinimum = currElement;
        }
    }
    printf("The 1st & 2nd minimums are %d & %d, respectively.\n", firstMinimum, secondMinimum);
    printf("The 1st & 2nd maximums are %d & %d, respectively.\n", firstMaximum, secondMaximum);
    return 0;
}
