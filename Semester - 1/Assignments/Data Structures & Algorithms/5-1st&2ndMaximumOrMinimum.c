/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective: Find 1st & 2nd maximum as well as minimum elements from given sequence.
*/

#include<stdio.h>
#include<math.h>

int sequence[] = {2, 5, 10, 2, 4};

//This prints elements from heap
int printHeap(int heap[], int numberOfElements){
    int i, j, power, index = 0;
    for(i = 0; (i < numberOfElements) && (index < numberOfElements); i++){
        /*
            i       Indexex to print    Number of iterations
            0   ->  0                   1 == pow(2, 0)
            1   ->  1, 2                2 == pow(2, 1)
            2   ->  3, 4, 5, 6          4 == pow(2, 2)
        */
        power = (int) pow(2, i);
        //When index == numberOfElements, means loop arrived on leaf node
        for(j = 0; (j < power) && (index < numberOfElements); j++){
            printf("%d\t", heap[index]);
            index++;
        }
        printf("\n");
    }
}

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

/*
Built using selection sort with outer loop restricted for only 2 elements
So the time complexity is 2 * n ~ O(n)
int findMinimum(int sequence[], int numberOfElements){
    int i, j, minValue, minValueIndex, firstMinValue, firstMinValueIndex;
    for(i = 0; i < 2; i++){
        minValue = sequence[0];
        minValueIndex = 0;
        for(j = 1; j < numberOfElements; j++){
            if(i > 0){
                if((sequence[j] < minValue && sequence[j] >= firstMinValue) && (j != firstMinValueIndex)){
                    minValue = sequence[j];
                    minValueIndex = j;
                }
            } else {
                if(sequence[j] < minValue){
                    minValue = sequence[j];
                    minValueIndex = j;
                }
            }
        }
        if(i == 0) {
            firstMinValue = minValue;
            firstMinValueIndex = minValueIndex;
        }
    }
    print(numberOfElements);
    printf("So the 1st & 2nd minimums are %d & %d, respectively.\n", firstMinValue, minValue);
    printf("******************************************\n");
    return 0;
}

int findMaximum(int sequence[], int numberOfElements){
    int i, j, maxValue, maxValueIndex, firstMaxValue, firstMaxValueIndex;
    for(i = 0; i < 2; i++){
        maxValue = sequence[0];
        maxValueIndex = 0;
        for(j = 1; j < numberOfElements; j++){
            if(i > 0){
                if((sequence[j] > maxValue && sequence[j] <= firstMaxValue) && (j != firstMaxValueIndex)){
                    maxValue = sequence[j];
                    maxValueIndex = j;
                }
            } else {
                if(sequence[j] > maxValue){
                    maxValue = sequence[j];
                    maxValueIndex = j;
                }
            }
        }
        if(i == 0){
            firstMaxValue = maxValue;
            firstMaxValueIndex = maxValueIndex;
        }
    }
    print(numberOfElements);
    printf("So the 1st & 2nd maximums are %d & %d, respectively.\n", firstMaxValue, maxValue);
    printf("******************************************\n");
    return 0;
}
*/

/*
Built using heap data structure, so the time complexity is O(logn).
Here, two separate heaps (minHeap & maxHeap) is taken so that original data won't get modified.
But, instead of minHeap & maxHeap, sequence (the original array) can also be heapified in same way.
*/
int findMinimum(int sequence[], int numberOfElements){
    int i, childIndex, temp;
    //Taking new minHeap and inserting elements into it.
    int minHeap[numberOfElements];
    for(i = 0; i < numberOfElements; i++){
        minHeap[i] = sequence[i];
    }
    /*
    This loop will iterate for every sub-tree.
    i will act as a rootNodeIndex or parentNodeIndex for every sub-tree being heapified.
    Parent of an element must be on (index of that element - 1) / 2. Since, indexing starts from 0, parent index = ((index of that element - 1) - 1) / 2
    Here, numberOfElements are 5. So, last element's index is 4 and its parent is on (4 - 2) / 2 = 2 / 2 = 1 index.
    */
    for(i = (numberOfElements - 2) / 2; i >= 0; i--){
        temp = minHeap[i];
        //Left child must be on (parentIndex * 2) index, but indexing starts from 0 so increment of 1 is necessary.
        childIndex = i * 2 + 1;
        //Checks whether left child exists or not.
        while(childIndex < numberOfElements) {
            //Checks whether right child exists or not and gets the index of smallest child among all the children of current parent node.
            if((childIndex + 1 < numberOfElements) && (sequence[childIndex] > sequence[childIndex + 1])){
                childIndex++;
            }
            /*
            temp holds parent node.
            So when parent becomes greater than child, it just move child to its parent index, no need of swapping.
            After completion of while loop, childIndex will be on the node which is greater than the node we stored as temp.
            So, insert it on childIndex / 2, but indexing starts from 0 so insert it on (childIndex - 1) / 2.
            */
            if(temp > minHeap[childIndex]){
                minHeap[(childIndex - 1) / 2] = minHeap[childIndex];
                childIndex = childIndex * 2 + 1;
            } else {
                break;
            }
        }
        minHeap[(childIndex - 1) / 2] = temp;
    }
    /*
    printf("Min heap:\n");
    printHeap(minHeap, numberOfElements);
    */
    print(numberOfElements);
    printf("So the 1st & 2nd minimums are %d & %d, respectively.\n", minHeap[0], minHeap[1]);
    printf("******************************************\n");
    return 0;
}

int findMaximum(int sequence[], int numberOfElements){
    int i, childIndex, temp;
    //Taking new maxHeap and inserting elements into it.
    int maxHeap[numberOfElements];
    for(i = 0; i < numberOfElements; i++){
        maxHeap[i] = sequence[i];
    }
    /*
    This loop will iterate for every sub-tree.
    i will act as a rootNodeIndex or parentNodeIndex for every sub-tree being heapified.
    Parent of an element must be on (index of that element - 1) / 2. Since, indexing starts from 0, parent index = ((index of that element - 1) - 1) / 2
    Here, numberOfElements are 5. So, last element's index is 4 and its parent is on (4 - 2) / 2 = 2 / 2 = 1 index.
    */
    for(i = (numberOfElements - 2) / 2; i >= 0; i--){
        temp = maxHeap[i];
        //Left child must be on parentIndex * 2 index, but indexing starts from 0 so increment of 1 is necessary.
        childIndex = i * 2 + 1;
        //Checks whether left child exists or not.
        while(childIndex < numberOfElements) {
            //Checks whether right child exists or not and gets the index of greatest child among all the children of current parent node.
            if((childIndex + 1 < numberOfElements) && (sequence[childIndex] < sequence[childIndex + 1])){
                childIndex++;
            }
            /*
            temp holds parent node.
            So when parent becomes greater than child, it just move child to its parent index, no need of swapping.
            After completion of while loop, childIndex will be on the node which is greater than the node we stored as temp. So, insert it on childIndex / 2.
            */
            if(temp < maxHeap[childIndex]){
                maxHeap[(childIndex - 1) / 2] = maxHeap[childIndex];
                childIndex = childIndex * 2 + 1;
            } else {
                break;
            }
        }
        maxHeap[(childIndex - 1) / 2] = temp;
    }
    /*
    printf("Max heap:\n");
    printHeap(maxHeap, numberOfElements);
    */
    print(numberOfElements);
    printf("So the 1st & 2nd maximums are %d & %d, respectively.\n", maxHeap[0], maxHeap[1]);
    printf("******************************************\n");
    return 0;
}

int main(){
    findMinimum(sequence, 5);
    findMaximum(sequence, 5);
    return 0;
}
