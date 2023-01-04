/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective:
*/

#include<stdio.h>
#include<math.h>

struct Process{
    int processID;
    int burstTime;
    int arrivalTime;
};

struct Process processQueue[5];

int print(int numberOfProcesses) {
    int i;
    printf("Process ID\tBurst Time\n");
    for(i = 0; i < numberOfProcesses; i++){
        printf("%d\t\t%d\n", processQueue[i].processID, processQueue[i].burstTime);
    }
    return 0;
}

int printHeap(int numberOfProcesses){
    int i, j, power, currProcessIndex = 0;
    for(i = 0; (i < numberOfProcesses) && (currProcessIndex < numberOfProcesses); i++){
        power = (int) pow(2, i);
        for(j = 0; (j < power) && (currProcessIndex < numberOfProcesses); j++){
            printf("{%d, %d}\t", processQueue[currProcessIndex].processID, processQueue[currProcessIndex].burstTime);
            currProcessIndex++;
        }
        printf("\n");
    }
}

int adjust(int rootProcessIndex, int availableProcesses){
    int greaterChildProcessIndex = rootProcessIndex * 2 + 1;
    struct Process rootProcess = processQueue[rootProcessIndex];
    while(greaterChildProcessIndex <= availableProcesses){
        if((greaterChildProcessIndex < availableProcesses) && (processQueue[greaterChildProcessIndex].burstTime < processQueue[greaterChildProcessIndex + 1].burstTime)){
            greaterChildProcessIndex = greaterChildProcessIndex + 1;
        }
        if(processQueue[rootProcessIndex].burstTime > processQueue[greaterChildProcessIndex].burstTime){
            break;
        } else {
            processQueue[greaterChildProcessIndex / 2] = processQueue[greaterChildProcessIndex];
            greaterChildProcessIndex *= 2;
        }
    }
    processQueue[greaterChildProcessIndex / 2] = rootProcess;
    return 0;
}

int insertA(int processList[], int numberOfProcesses){
    int i;
    for(i = 0; i < numberOfProcesses; i++){
        processQueue[i].processID = i;
        processQueue[i].burstTime = processList[i];
    }
    return 0;
}

int insertB1(int processList[], int numberOfProcesses){
    int i, j, currProcessIndex, currProcessBurstTime;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        currProcessBurstTime = processList[i];
        while((j < i) && (processQueue[j].burstTime <= currProcessBurstTime)){
            j++;
        }
        currProcessIndex = j;
        for(j = i; j > currProcessIndex; j--){
            processQueue[j] = processQueue[j - 1];
        }
        processQueue[currProcessIndex].processID = i;
        processQueue[currProcessIndex].burstTime = currProcessBurstTime;
    }
    return 0;
}

int insertB2(int processList[], int numberOfProcesses){
    int i, j, currProcessIndex, currProcessBurstTime;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        currProcessBurstTime = processList[i];
        while((j < i) && (processQueue[j].burstTime > currProcessBurstTime)){
            j++;
        }
        currProcessIndex = j;
        for(j = i; j > currProcessIndex; j--){
            processQueue[j] = processQueue[j - 1];
        }
        processQueue[currProcessIndex].processID = i;
        processQueue[currProcessIndex].burstTime = currProcessBurstTime;
    }
    return 0;
}

int insertC(int processList[], int numberOfProcesses){
    int i, j, parentIndex;
    struct Process currProcess;
    for(i = 0; i < numberOfProcesses; i++){
        j = i;
        while(j > 0){
            parentIndex = j / 2;
            if(processQueue[parentIndex].burstTime > processList[i]){
                processQueue[j] = processQueue[parentIndex];
                j = parentIndex;
            } else {
                break;
            }
        }
        processQueue[j].processID = i;
        processQueue[j].burstTime = processList[i];
    }
    return 0;
}

int insertC1(int processList[], int numberOfProcesses){
    int i, j, parentIndex;
    for(i = 0; i < numberOfProcesses; i++){
        j = i;
        processQueue[j].processID = i;
        processQueue[j].burstTime = processList[i];
        adjust(0, i);
    }
    return 0;
}

int deleteA(int numberOfProcesses){
    int i, j, minProcessIndex, minProcessBurstTime, elapsedTime = 0, availableProcesses = numberOfProcesses;
    struct Process minProcess, currProcess;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        minProcess = processQueue[0];
        minProcessIndex = 0;
        minProcessBurstTime = minProcess.burstTime;
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
        for(j = minProcessIndex; j < numberOfProcesses; j++){
            processQueue[j] = (j + 1 != numberOfProcesses ? processQueue[j + 1] : minProcess);
        }      
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

int deleteB1(int numberOfProcesses){
    int i, j, availableProcesses = numberOfProcesses, elapsedTime = 0;
    struct Process currProcess;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        currProcess = processQueue[0];
        elapsedTime += currProcess.burstTime;
        printf("Min Process: {%d, %d}\n", currProcess.processID, currProcess.burstTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        for(j = 0; j < availableProcesses; j++){
            processQueue[j] = (j + 1 != numberOfProcesses ? processQueue[j + 1] : currProcess);
        }
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

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
        while((j < availableProcesses) && (j * 2 + 1 < availableProcesses)) {
            if(j * 2 + 2 < availableProcesses){
                currProcessIndex = (processQueue[j * 2 + 1].burstTime <= processQueue[j * 2 + 2].burstTime) ? j * 2 + 1 : j * 2 + 2;
            } else {
                currProcessIndex = j * 2 + 1;
            }
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
