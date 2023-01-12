/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: January 5, 2023 19.00.05 IST
    Objective:
        You have two processors.
        Maintain 2 queues.
        For insertion, insert in the queue which has smallest time interval (sum of the time of all jobs).
        For deletion, delete with option1 & option2, for processor 1 & 2, respectively.
        Suppose, one processor fails.
        Job from that processor have to be transferred to the processor which is in working condition.
        a)  Delete the element that is minimum from both the queues.
        b)  Merge elements of both the queues and process as usual.
        c)  Delete elements from queue of failed processor and insert them one-by-one to the working one and then proceed as usual.
*/

#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<stdbool.h>

struct Process{
    int processID;
    int burstTime;
};

//True shows that the processor is in working condition.
bool processor1 = true, processor2 = true;
//This shows the number of queues associated with single processor.
int numberOfQueues;
/*
Array of structures.
processQueue1 is the queue for processor1 and processQueue2 is the queue for processor2.
*/
struct Process processQueue1[5], processQueue2[5];
//Size of both the queues.
int queueSize1 = 5, queueSize2 = 5;
/*
At the time of insertion, this two varibles (elapsedTime1 & elapsedTime2), helps to decide where the new process should be inserted.
If elapsedTime1 is lesser or equal to elapsedTime2 then process will be inserted in queue1 else it will be inserted in queue2.
At the time of deletion, this shows the time elapsed.
*/
int elapsedTime1 = 0, elapsedTime2 = 0;

//This prints processes from heap
int printHeap(struct Process processQueue[], int queueSize){
    int i, j, power, currProcessIndex = 0;
    for(i = 0; (i < queueSize) && (currProcessIndex < queueSize); i++){
        /*
            i       Indexex to print    Number of iterations
            0   ->  0                   1 == pow(2, 0)
            1   ->  1, 2                2 == pow(2, 1)
            2   ->  3, 4, 5, 6          4 == pow(2, 2)
        */
        power = (int) pow(2, i);
        //When currProcessIndex == numberOfProcesses, means loop arrived on leaf node
        for(j = 0; (j < power) && (currProcessIndex < queueSize); j++){
            printf("{%d, %d}\t", processQueue[currProcessIndex].processID, processQueue[currProcessIndex].burstTime);
            currProcessIndex++;
        }
        printf("\n");
    }
}

//This ensures that heap preserves its min-heap characteristics.
int heapify(struct Process processQueue[], struct Process tempProcess, int parentIndex, int queueSize){
    //Left child must be on (parentIndex * 2) index, but indexing starts from 0 so increment of 1 is necessary.
    int childProcessIndex = parentIndex * 2 + 1;
    //Checks whether left child exists or not.
    while(childProcessIndex < queueSize){
        /*
        Checks whether right child exists or not and gets the index of smallest child among all the children of current parent node.
        Gets the index of smallest child among all the children of current parent node.
        */
        printf("LChild: {%d, %d},", processQueue[childProcessIndex].processID, processQueue[childProcessIndex].burstTime);
        if(childProcessIndex + 1 < queueSize){
            printf("RChild: {%d, %d},", processQueue[childProcessIndex + 1].processID, processQueue[childProcessIndex + 1].burstTime);
        }
        printf("Parent: {%d, %d}\n", tempProcess.processID, tempProcess.burstTime);
        if((childProcessIndex + 1 < queueSize) && (processQueue[childProcessIndex].burstTime > processQueue[childProcessIndex + 1].burstTime)){
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

//Nodes are already inserted into queues and then it heapifies them to min-heaps.
int heapSort(struct Process processQueue[], int queueSize){
    int i;
    /*
    This loop will iterate for every sub-tree.
    i will act as a rootNodeIndex or parentNodeIndex for every sub-tree being heapified.
    Parent of an element must be on (index of that element - 1) / 2. Since, indexing starts from 0, parent index = ((index of that element - 1) - 1) / 2
    Here, numberOfElements are 5. So, last element's index is 4 and its parent is on (4 - 2) / 2 = 2 / 2 = 1 index.
    */
    for(i = (queueSize - 2) / 2; i >= 0; i--){
        heapify(processQueue, processQueue[i], i, queueSize);
    }
    return 0;
}

//Inserts nodes in queues.
int insert(int processList[], int numberOfProcesses){
    int i;
    int processQueuePointer1 = 0, processQueuePointer2 = 0;
    for(i = 0; i < numberOfProcesses; i++){
        //Checks whether queue1 is empty or not. If not, insert remaining jobs into the queue which is not full yet.
        if(processQueuePointer1 < queueSize1){
            //Checks whether queue2 is empty or not and if it is empty then inserts job into queue2 if sum of burst time of queue2 is lesser else inserts in queue1.
            if((processQueuePointer2 < queueSize2) && (elapsedTime1 > elapsedTime2)){
                processQueue2[processQueuePointer2].processID = i;
                processQueue2[processQueuePointer2++].burstTime = processList[i];
                elapsedTime2 += processList[i];
            } else {
                processQueue1[processQueuePointer1].processID = i;
                processQueue1[processQueuePointer1++].burstTime = processList[i];
                elapsedTime1 += processList[i];
            }
        } else {
            processQueue2[processQueuePointer2].processID = i;
            processQueue2[processQueuePointer2++].burstTime = processList[i];
            elapsedTime2 += processList[i];
        }
    }
    //Converts queue1 into min-heap.
    heapSort(processQueue1, queueSize1);
    //Converts queue2 into min-heap.
    heapSort(processQueue2, queueSize2);
    //Prints them.
    printf("Queue1:\n");
    printHeap(processQueue1, queueSize1);
    printf("-----------------------------\nQueue2:\n");
    printHeap(processQueue2, queueSize2);
    printf("**************************************\n");
    return 0;
}

//Deletes the first node from given heap and re-heapifies it.
int deleteHeap(struct Process processQueue[], int queueSize){
    int burstTime = 0;
    struct Process tempProcess;
    printHeap(processQueue, queueSize);
    burstTime = processQueue[0].burstTime;
    printf("Min Process: {%d, %d}\n", processQueue[0].processID, processQueue[0].burstTime);
    tempProcess = processQueue[--queueSize];
    processQueue[queueSize] = processQueue[0];
    heapify(processQueue, tempProcess, 0, queueSize);
    return burstTime;
}

//This function deletes element from queue1/heap1.
int deleteFromQueue1(){
    printf("Queue1:\n");
    //heap1 is not empty, delete element from it and re-heapify.
    if(queueSize1 > 0) {
        elapsedTime1 += deleteHeap(processQueue1, queueSize1--);
        //If both the processors are working then show the time only associated to that processor.
        if(processor1 && processor2){
            printf("Time elapsed: %d\n", elapsedTime1);
        }
    } else {
        printf("Queue1 is empty.\n");
    }
    //If a processor is working on more than one heaps, the print the other also.
    if(numberOfQueues > 1){
        printf("-----------------------------\nQueue2:\n");
        if(queueSize2 > 0) {
            printHeap(processQueue2, queueSize2);
        } else {
            printf("Queue2 is empty.\n");
        }
    }
    //If only a single processor running then print overall time consumed.
    if(!processor1 || !processor2){
        printf("-----------------------------\nTime elapsed: %d\n**************************************\n", elapsedTime1 + elapsedTime2);
    }
    return 0;
}

//This function deletes element from queue2/heap2.
int deleteFromQueue2(){
    //If a processor is working on more than one heaps, the print the other also.
    if(numberOfQueues > 1){
        printf("Queue1:\n");
        if(queueSize1 > 0){
            printHeap(processQueue1, queueSize1);
        } else {
            printf("Queue1 is empty.\n");
        }
        printf("-----------------------------\n");
    }
    printf("Queue2:\n");
    //heap2 is not empty, delete element from it and re-heapify.
    if(queueSize2 > 0){
        elapsedTime2 += deleteHeap(processQueue2, queueSize2--);
        //If both the processors are working then show the time only associated to that processor.
        if(processor1 && processor2){
            printf("Time elapsed: %d\n", elapsedTime2);
        }
    } else {
        printf("Queue2 is empty.\n");
    }
    //If only a single processor running then print overall time consumed.
    if(!processor1 || !processor2){
        printf("-----------------------------\nTime elapsed: %d\n**************************************\n", elapsedTime1 + elapsedTime2);
    }
}

//Deletes the minimum from both the queues/heaps.
int deleteA(){
    //numberOfProcesses will have number of un-processed jobs.
    int i;
    numberOfQueues = 2;
    while(queueSize1 > 0 || queueSize2 > 0){
        if(queueSize1 > 0){
            if((queueSize2 > 0) && (processQueue1[0].burstTime > processQueue2[0].burstTime)){
                deleteFromQueue2();
            } else {
                deleteFromQueue1();
            }
        } else {
            deleteFromQueue2();
        }
    }
    return 0;
}

/*
Here, all the queues are merged. So, assume that the elements of other queues are insrted at the end of the queue associated with the working processor.
So, this function ensures that the working processor first process all the jobs assigned to its own queue and then go for other queues.
*/
int deleteB(){
    //numberOfProcesses will have number of un-processed jobs.
    int i, j;
    printf("Assume that both the queues are merged.\nSo, the processor which is in working condition will execute queue of its own first, till then queue (or elements) of failed processor will be ignored. The elements of ignored queue will be deleted such that it will look like, they are coming in linear way from the first queue itself.\n\n");
    numberOfQueues = 2;
    if(processor1){
        while(queueSize1 > 0){
            deleteFromQueue1();
        }
        while(queueSize2 > 0){
            deleteFromQueue2();
        }
    } else {
        while(queueSize2 > 0){
            deleteFromQueue2();
        }
        while(queueSize1 > 0){
            deleteFromQueue1();
        }
    }
    return 0;
}

/*
Here, all elememts of the queue associated with non-working processor are being inserted one-by-one in the queue of working processor.
Then that queue gets heapified to make min-heap and then processor works as usual.
*/
int deleteC(){
    //numberOfProcesses will have number of un-processed jobs.
    int i, j, numberOfProcesses = queueSize1 + queueSize2;
    int time1 = elapsedTime1, time2 = elapsedTime2;
    //processQueue is taken with the new size. Size of queue1 + size of queue2.
    struct Process processQueue[numberOfProcesses];
    numberOfQueues = 1;
    if(processor1){
        //Processes from queue1 are being inserted in new bigger queue.
        for(i = 0; i < queueSize1; i++){
            processQueue[i] = processQueue1[i];
        }
        //queue1 is now the bigger queue.
        * processQueue1 = * processQueue;
        //Processes from queue2 are being inserted in queue1.
        for(i = queueSize1, j = 0; i < numberOfProcesses && j < queueSize2; i++, j++){
            processQueue1[i] = processQueue2[j];
            /*
            If you wish, you can delete processes from queue2. Which is of no use now.
            deleteHeap(processQueue2, queueSize2--);
            */
        }
        queueSize1 = numberOfProcesses;
        queueSize2 = 0;
        //Converts queue1 into min-heap.
        heapSort(processQueue1, queueSize1);
        //Deletes processes from queue1.
        for(i = queueSize1 - 1; i >= 0; i--){
            deleteFromQueue1();
        }
    } else {
        //Processes from queue1 are being inserted in new bigger queue.
        for(i = 0; i < queueSize2; i++){
            processQueue[i] = processQueue2[i];
        }
        //queue2 is now the bigger queue.
        * processQueue2 = * processQueue;
        //Processes from queue1 are being inserted in queue2.
        for(i = queueSize2, j = 0; i < numberOfProcesses && j < queueSize1; i++, j++){
            printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
            processQueue2[i] = processQueue1[j];
            printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
            /*
            If you wish, you can delete processes from queue1. Which is of no use now.
            deleteHeap(processQueue1, queueSize1--);
            */
        }
        queueSize1 = 0;
        queueSize2 = numberOfProcesses;
        printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
        //Converts queue2 into min-heap.
        heapSort(processQueue2, queueSize2);
        printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
        //Deletes processes from queue2.
        for(i = queueSize2 - 1; i >= 0; i--){
            printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
            deleteFromQueue2();
            printf("Time1: %d, %d, Time2: %d, %d\n", elapsedTime1, time1, elapsedTime2, time2);
        }
    }
    return 0;
}

//Contains functions call for different ways of deletion.
int delete(int numberOfProcesses){
    int choice;
    elapsedTime1 = 0, elapsedTime2 = 0;
    while(queueSize1 > 0 || queueSize2 > 0){
        do {
            printf("Here, two processors are working on two different queues.\nWhich processor should stop working?\n1. Processor1\n2. Processor2\n3. None\n\nEnter your choice here: ");
            scanf("%d", &choice);
            switch(choice){
                case 1:     processor1 = false;
                            break;
                case 2:     processor2 = false;
                            break;
                case 3:     break;
                default:    printf("Given choice is invalid, please choose again.\n\n");
                            break;
            }
        } while(choice < 1 || choice > 3);
        printf("\n");
        //If both the processors are working, then remove minimum from both of them simultaniously.
        if(processor1 && processor2){
            numberOfQueues = 1;
            deleteFromQueue1();
            printf("-----------------------------\n");
            deleteFromQueue2();
            printf("**************************************\n");
        } else {
            /*
            Till now both the processors were working simultaniously but now one of them stopped working.
            So, elapsed time will be the maximum of the time spent by both the processors.
            */
            if(processor1){
                elapsedTime1 = elapsedTime1 >= elapsedTime2 ? elapsedTime1 : elapsedTime2;
                elapsedTime2 = 0;
            } else {
                elapsedTime2 = elapsedTime2 >= elapsedTime1 ? elapsedTime2 : elapsedTime1;
                elapsedTime1 = 0;
            }
            do {
                printf("One of the two processeors is failed.\nNow, how single processor is going to process both the queues?\n1. Delete the element that is minimum from both the queues.\n2. Merge elements of both the queues and process as usual.\n3. Delete elements from queue of failed processor and insert them one-by-one to the working one and then proceed as usual.\n\nEnter your choice here: ");
                scanf("%d", &choice);
                printf("\n");
                switch(choice){
                    case 1:     deleteA(numberOfProcesses);
                                break;
                    case 2:     deleteB(numberOfProcesses);
                                break;
                    case 3:     deleteC(numberOfProcesses);
                                break;
                    default:    printf("Given choice is invalid, please choose again.\n\n");
                                break;
                }
            } while(choice < 1 || choice > 3);
        }
    }
    return 0;
}

int main(){
    int processList[] = {2, 5, 10, 2, 4, 12, 12, 1, 9, 3};
    insert(processList, 10);
    delete(10);
    return 0;
}
