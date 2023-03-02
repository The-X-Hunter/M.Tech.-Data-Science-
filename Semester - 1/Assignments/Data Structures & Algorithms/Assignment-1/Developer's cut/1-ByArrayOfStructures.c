/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective:
*/

#include<stdio.h>

struct Process{
    int processID;
    int burstTime;
    int arrivalTime;
};

struct Process processQueue[5];

int print(int numberOfProcesses) {
    int i;
    printf("Process ID\tBurst Time\tArrival Time\n");
    for(i = 0; i < numberOfProcesses; i++){
        printf("%d\t\t%d\t\t%d\n", processQueue[i].processID, processQueue[i].burstTime, processQueue[i].arrivalTime);
    }
    return 0;
}

int insert(int processList[][2], int numberOfProcesses){
    int i;
    for(i = 0; i < numberOfProcesses; i++){
        processQueue[i].processID = i;
        processQueue[i].burstTime = processList[i][0];
        processQueue[i].arrivalTime = processList[i][1];
    }
    return 0;
}

//This function is not finished
int deleteWithoutShifting(int numberOfProcesses){
    int i, j, minProcessBurstTime, minProcessIndex, elapsedTime = 0;
    struct Process process;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        while((processQueue[j].burstTime == 0) || (processQueue[j].arrivalTime > elapsedTime)){
            j++;
        }
        minProcessBurstTime = processQueue[j].burstTime;
        minProcessIndex = j;
        for(; j < numberOfProcesses; j++){
            process = processQueue[j];
            if((process.burstTime != 0) && ((process.arrivalTime <= elapsedTime) && (process.burstTime <= minProcessBurstTime))){
                minProcessBurstTime = process.burstTime;
                minProcessIndex = j;
            }
        }
        elapsedTime += minProcessBurstTime;
        printf("Min Process: {%d, %d, %d}\n", processQueue[minProcessIndex].processID, minProcessBurstTime, processQueue[minProcessIndex].arrivalTime);
        printf("Time elapsed: %d\n", elapsedTime);
        processQueue[minProcessIndex].burstTime = 0;
    }
    printf("There are no more processes available.\n");
    return 0;
}

int delete(int numberOfProcesses){
    int i, j, availableProcesses, currProcessArrivalTime, minProcessArrivalTime, minProcessBurstTime, minProcessIndex, elapsedTime = 0;
    struct Process currProcess, minProcess;
    availableProcesses = numberOfProcesses;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        j = 0;
        minProcess = processQueue[j];
        minProcessIndex = j;
        minProcessArrivalTime = minProcess.arrivalTime;
        currProcessArrivalTime = minProcessArrivalTime;
        while(currProcessArrivalTime > elapsedTime){
            if(j + 1 < availableProcesses){
                j++;
                currProcessArrivalTime = processQueue[j].arrivalTime;
            } else {
                printf("No min process at time %d.\n", elapsedTime);
                elapsedTime = minProcessArrivalTime;
                currProcessArrivalTime = minProcessArrivalTime;
                printf("Time elapsed: %d\n**************************************\n", elapsedTime);
                print(numberOfProcesses);
            }
            if(currProcessArrivalTime < minProcessArrivalTime){
                minProcess = processQueue[j];
                minProcessIndex = j;
                minProcessArrivalTime = currProcessArrivalTime;
            }
        }
        j = minProcessIndex;
        minProcessBurstTime = minProcess.burstTime;
        for(; j < availableProcesses; j++){
            currProcess = processQueue[j];
            if((currProcess.arrivalTime <= elapsedTime) && (currProcess.burstTime <= minProcessBurstTime)){
                minProcess = currProcess;
                minProcessIndex = j;
                minProcessBurstTime = minProcess.burstTime;
            }
        }
        availableProcesses--;
        elapsedTime += minProcessBurstTime;
        printf("Min Process: {%d, %d, %d}\n", minProcess.processID, minProcessBurstTime, minProcess.arrivalTime);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        for(j = minProcessIndex; j < numberOfProcesses; j++){
            processQueue[j] = (j + 1 != numberOfProcesses ? processQueue[j + 1] : minProcess);
        }
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

int main(){
    int numberOfProcesses = 5;
    //List of processes is given as an array
    int processList[][2] = {
        //{BurstTime, ArrivalTime}
        //Array index is treated as a Process ID
        {2, 0},
        {5, 5},
        {10, 0},
        {2, 3},
        {4, 6}
    };
    insert(processList, numberOfProcesses);
    //deleteWithoutShifting(numberOfProcesses);
    delete(numberOfProcesses);
    return 0;
}
