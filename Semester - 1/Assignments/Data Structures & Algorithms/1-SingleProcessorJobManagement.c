/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective:
        Consider a processor that is to be assigned jobs in order of time (Shortest Job First).
        Maintain a priority queue.
        Perfom insert & delete operations.
        a)  Maintain a FIFO queue.
            For deletion, select shortest job (highest priority element), delete it and re-arrang the queue by shifting elements.
        b)  1.  Use insertion sort to maintain a sorted array.
                For insertion, place element at proper position.
                For deletion, delete first element and re-arrange the queue by shifting elements.
            2.  Maintain queue in reverse order.
                Delete last element.
        c)  Use heap to maintain priority queue.
            For insertion, insert the element in a heap so that heap property is maintained.
            For deletion, delete first element. Delete and copy last element to first position, and re-heapify to arrange the first element in heap.
*/

#include<stdio.h>
#include<math.h>

struct Process{
    int processID;
    int burstTime;
    int arrivalTime;
};

//Array of structures
struct Process processQueue[5];

//This prints processes from queue
int print(int numberOfProcesses) {
    int i;
    printf("Process ID\tBurst Time\n");
    for(i = 0; i < numberOfProcesses; i++){
        printf("%d\t\t%d\n", processQueue[i].processID, processQueue[i].burstTime);
    }
    return 0;
}

//This prints processes from heap
int printHeap(int numberOfProcesses){
    int i, j, power, currProcessIndex = 0;
    for(i = 0; (i < numberOfProcesses) && (currProcessIndex < numberOfProcesses); i++){
        /*
            i       Indexex to print    Number of iterations
            0   ->  0                   1 == pow(2, 0)
            1   ->  1, 2                2 == pow(2, 1)
            2   ->  3, 4, 5, 6          4 == pow(2, 2)
        */
        power = (int) pow(2, i);
        //When currProcessIndex == numberOfProcesses, means loop arrived on leaf node
        for(j = 0; (j < power) && (currProcessIndex < numberOfProcesses); j++){
            printf("{%d, %d}\t", processQueue[currProcessIndex].processID, processQueue[currProcessIndex].burstTime);
            currProcessIndex++;
        }
        printf("\n");
    }
}

int heapify(int parentProcessIndex, int numberOfProcesses, struct Process tempProcess){
    //Left child must be on (parentIndex * 2) index, but indexing starts from 0 so increment of 1 is necessary.
    int childProcessIndex = parentProcessIndex * 2 + 1;
    //Checks whether left child exists or not.
    while(childProcessIndex < numberOfProcesses){
        /*
        Checks whether right child exists or not and gets the index of smallest child among all the children of current parent node.
        Gets the index of smallest child among all the children of current parent node.
        */
        if((childProcessIndex + 1 < numberOfProcesses) && (processQueue[childProcessIndex].burstTime > processQueue[childProcessIndex + 1].burstTime)){
            childProcessIndex++;
        }
        /*
        temp holds parent node.
        So when parent becomes greater than child, it just move child to its parent index, no need of swapping.
        After completion of while loop, childProcessIndex will be on the node which is greater than the node we stored as temp. So, insert it on childProcessIndex / 2.
        */
        if(tempProcess.burstTime > processQueue[childProcessIndex].burstTime){
            processQueue[(childProcessIndex - 1) / 2] = processQueue[childProcessIndex];
            childProcessIndex = childProcessIndex * 2 + 1;
        } else {
            break;
        }
    }
    processQueue[(childProcessIndex - 1) / 2] = tempProcess;
    return 0;
}

//Inserts new process at the end of queue
int insertA(int processList[], int numberOfProcesses){
    int i;
    for(i = 0; i < numberOfProcesses; i++){
        processQueue[i].processID = i;
        processQueue[i].burstTime = processList[i];
    }
    return 0;
}

//Inserts new process in ascending order to a sorted queue using insertion sort
int insertB1(int processList[], int numberOfProcesses){
    int i, j, currProcessIndex, currProcessBurstTime;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        currProcessBurstTime = processList[i];
        //Finds the location where process can be inserted
        while((j < i) && (processQueue[j].burstTime <= currProcessBurstTime)){
            j++;
        }
        currProcessIndex = j;
        //Shifts processes to right and makes a slot for new process
        for(j = i; j > currProcessIndex; j--){
            processQueue[j] = processQueue[j - 1];
        }
        //Insertion of new process
        processQueue[currProcessIndex].processID = i;
        processQueue[currProcessIndex].burstTime = currProcessBurstTime;
    }
    return 0;
}

/*
//Inserts new process in descending order to a sorted queue but starts looking from starting index
int insertB2(int processList[], int numberOfProcesses){
    int i, j, currProcessIndex, currProcessBurstTime;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        currProcessBurstTime = processList[i];
        //Finds the location where proceess can be inserted but start looking from starting index
        while((j < i) && (processQueue[j].burstTime > currProcessBurstTime)){
            j++;
        }
        currProcessIndex = j;
        //Shifts processes to right and makes a slot for new process
        for(j = i; j > currProcessIndex; j--){
            processQueue[j] = processQueue[j - 1];
        }
        //Insertion of new process
        processQueue[currProcessIndex].processID = i;
        processQueue[currProcessIndex].burstTime = currProcessBurstTime;
    }
    return 0;
}
*/

//Insert new process in descending order to a sorted queue using insertion sort
int insertB2(int processList[], int numberOfProcesses){
    int i, j, availableProcesses, currProcessIndex, currProcessBurstTime;
    for(i = 0; i < numberOfProcesses; i++){
        j = numberOfProcesses - 1;
        availableProcesses = numberOfProcesses - (i + 1);
        currProcessBurstTime = processList[i];
        //Finds the location where process can be inserted but starts looking from last index
        while((j > availableProcesses) && (processQueue[j].burstTime <= currProcessBurstTime)){
            j--;
        }
        currProcessIndex = j;
        //Shifts processes to left and makes slot for new process
        for(j = 0; j < currProcessIndex; j++){
            processQueue[j] = processQueue[j + 1];
        }
        //Insertion of new process
        processQueue[currProcessIndex].processID = i;
        processQueue[currProcessIndex].burstTime = currProcessBurstTime;
    }
    return 0;
}

/*
Inserts new process in heap.
Assumes that the heap is heapified except the last node which is being inserted.
So, after insertion, it hepifies the heap.
int insertC(int processList[], int numberOfProcesses){
    int i, j, parentIndex;
    //i will always be on last index where node can be inserted
    for(i = 0; i < numberOfProcesses; i++){
        j = i;
        //Finds the location where process can be inserted/shifted to
        while(j > 0){
            parentIndex = j / 2;
            //Shifts parent to one level down and assign the blank position to new process/parent
            if(processQueue[parentIndex].burstTime > processList[i]){
                processQueue[j] = processQueue[parentIndex];
                j = parentIndex;
            } else {
                break;
            }
        }
        //Insertion of new process
        processQueue[j].processID = i;
        processQueue[j].burstTime = processList[i];
    }
    return 0;
}
*/

//Nodes are inserted into queue and then it heapifies it to min-heap.
int insertC(int processList[], int numberOfProcesses){
    int i, j, childProcessIndex;
    struct Process tempProcess;
    for(i = 0; i < numberOfProcesses; i++){
        processQueue[i].processID = i;
        processQueue[i].burstTime = processList[i];
    }
    /*
    This loop will iterate for every sub-tree.
    i will act as a rootNodeIndex or parentNodeIndex for every sub-tree being heapified.
    Parent of an element must be on (index of that element - 1) / 2. Since, indexing starts from 0, parent index = ((index of that element - 1) - 1) / 2
    Here, numberOfElements are 5. So, last element's index is 4 and its parent is on (4 - 2) / 2 = 2 / 2 = 1 index.
    */
    for(i = (numberOfProcesses - 2) / 2; i >= 0; i--){
        heapify(i, numberOfProcesses, processQueue[i]);
    }
    return 0;
}

//Finds out process with minimum burst time using insertion sort & shifts it to the end of the queue
int deleteA(int numberOfProcesses){
    int i, j, minProcessIndex, minProcessBurstTime, elapsedTime = 0, availableProcesses = numberOfProcesses;
    struct Process minProcess;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        minProcess = processQueue[0];
        minProcessIndex = 0;
        minProcessBurstTime = minProcess.burstTime;
        //Finds out the location of process with minimum burst time
        for(j = 1; j < availableProcesses; j++){
            if(processQueue[j].burstTime < minProcessBurstTime){
                minProcess = processQueue[j];
                minProcessIndex = j;
                minProcessBurstTime = minProcess.burstTime;
            }
        }
        availableProcesses--;
        elapsedTime += minProcessBurstTime;
        printf("Min Process: {%d, %d}\n", minProcess.processID, minProcessBurstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        //Shifts processes to left and add the deleted process at the end of the queue
        for(j = minProcessIndex; j < numberOfProcesses; j++){
            processQueue[j] = (j + 1 != numberOfProcesses ? processQueue[j + 1] : minProcess);
        }      
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

//Deletes process from the start of the queue
int deleteB1(int numberOfProcesses){
    int i, j, availableProcesses = numberOfProcesses, elapsedTime = 0;
    struct Process minProcess;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        minProcess = processQueue[0];
        elapsedTime += minProcess.burstTime;
        printf("Min Process: {%d, %d}\n", minProcess.processID, minProcess.burstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        //Shifts processes to left and add the deleted process at the end of the queue
        for(j = 0; j < availableProcesses; j++){
            processQueue[j] = (j + 1 != numberOfProcesses ? processQueue[j + 1] : minProcess);
        }
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

//Deletes process from the end of the queue
int deleteB2(int numberOfProcesses){
    int i, elapsedTime = 0;
    for(i = numberOfProcesses - 1; i >= 0; i--){
        print(numberOfProcesses);
        elapsedTime += processQueue[i].burstTime;
        printf("Min Process: {%d, %d}\n", processQueue[i].processID, processQueue[i].burstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
    }
    return 0;
}

/*
//Deletes process from the heap
int deleteC(int numberOfProcesses){
    int i, j, currProcessIndex, elapsedTime = 0, availableProcesses = 5;
    struct Process currProcess;
    for(i = numberOfProcesses - 1; i >= 0; i--){
        printHeap(numberOfProcesses);
        elapsedTime += processQueue[0].burstTime;
        printf("Min Process: {%d, %d}\n", processQueue[0].processID, processQueue[0].burstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        currProcess = processQueue[0];
        processQueue[0] = processQueue[i];
        processQueue[i] = currProcess;
        availableProcesses--;
        j = 0;
        //Heapify the min heap
        while((j < availableProcesses) && (j * 2 + 1 < availableProcesses)) {
            //Checks if right child available
            if(j * 2 + 2 < availableProcesses){
                currProcessIndex = (processQueue[j * 2 + 1].burstTime <= processQueue[j * 2 + 2].burstTime) ? j * 2 + 1 : j * 2 + 2;
            } else {
                currProcessIndex = j * 2 + 1;
            }
            //Compares parent and the smalled child, and swaps their position
            if(processQueue[j].burstTime > processQueue[currProcessIndex].burstTime){
                currProcess = processQueue[currProcessIndex];
                processQueue[currProcessIndex] = processQueue[j];
                processQueue[j] = currProcess;
                j = currProcessIndex;
            } else {
                break;
            }
        }
    }
    return 0;
}
*/

//Deletes process from the heap
int deleteC(int numberOfProcesses){
    int i, childProcessIndex, elapsedTime = 0;
    struct Process tempProcess;
    //This loop helps in swapping of last element with the first of heap.
    for(i = numberOfProcesses - 1; i >= 0; i--){
        printHeap(numberOfProcesses);
        elapsedTime += processQueue[0].burstTime;
        printf("Min Process: {%d, %d}\n", processQueue[0].processID, processQueue[0].burstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        tempProcess = processQueue[i];
        processQueue[i] = processQueue[0];
        processQueue[0] = tempProcess;
        heapify(0, i, tempProcess);
    }
    return 0;
}

int main(){
    int numberOfProcesses = 5, choice;
    //List of processes is given as an array
    int processList [] = {2, 5, 10, 2, 4};
    do {
        printf("Which way the processor will insert the job in queue?\n1. As of arriving sequence\n2. Shortest job on front\n3. Shortest job on rear\n4. Using min-heap\n\nEnter your choice here: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:     insertA(processList, numberOfProcesses);
                        deleteA(numberOfProcesses);
                        break;
            case 2:     insertB1(processList, numberOfProcesses);
                        deleteB1(numberOfProcesses);
                        break;
            case 3:     insertB2(processList, numberOfProcesses);
                        deleteB2(numberOfProcesses);
                        break;
            case 4:     insertC(processList, numberOfProcesses);
                        deleteC(numberOfProcesses);
                        break;
            default:    printf("Given choice is invalid, please choose again.\n");
                        break;
        }
    } while(choice < 1 || choice > 4);
    return 0;
}
