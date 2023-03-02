/*
    Name: Julfikaraehmad
    Course: M.Tech. Data Science (Semester-1)
    Subject: Data Structures & Algorithms
    Timestamp: December 26, 2022 17.38.05 IST
    Objective:
*/

#include<stdio.h>

//List of processes is given as an array
int processQueue[][3] = {
    //{ProcessID, BurstTime, ArrivalTime}
    {0, 2, 0},
    {1, 5, 5},
    {2, 10, 0},
    {3, 12, 3},
    {4, 4, 6}
};

int print(int numberOfProcesses){
    int i;
    printf("Process ID\tBurst Time\tArrivalTime\n");
    for(i = 0; i < numberOfProcesses; i++){
        printf("%d\t\t%d\t\t%d\n", processQueue[i][0], processQueue[i][1], processQueue[i][2]);
    }
    return 0;
}

//This function is not finished
int deleteWithoutShifting(int numberOfProcesses){
    int i, j, minProcessBurstTime, minProcessIndex, sumOfBurstTime = 0;
    for(i = 0; i < numberOfProcesses; i++){
        j = 0;
        while((processQueue[j][1] == 0) || (processQueue[j][2] > sumOfBurstTime)){
            j++;
        }
        minProcessBurstTime = processQueue[j][1];
        minProcessIndex = j;
        for(; j < numberOfProcesses; j++){
            if((processQueue[j][1] != 0) && ((processQueue[j][2] <= sumOfBurstTime) && (processQueue[j][1] <= minProcessBurstTime))){
                minProcessBurstTime = processQueue[j][1];
                minProcessIndex = j;
            }
        }
        sumOfBurstTime += minProcessBurstTime;
        printf("Min Process: {%d, %d, %d}\n", processQueue[minProcessIndex][0], minProcessBurstTime, processQueue[minProcessIndex][2]);
        printf("Time elapsed: %d\n", sumOfBurstTime);
        processQueue[minProcessIndex][1] = 0;
    }
    return 0;
}

int delete(int numberOfProcesses){
    int i, j, availableProcesses, currProcessArrivalTime, minProcessArrivalTime, minProcessBurstTime, minProcessIndex, elapsedTime = 0;
    int * minProcess, * currProcess;
    int minProcessValues[3];
    availableProcesses = numberOfProcesses;
    for(i = 0; i < numberOfProcesses; i++){
        print(numberOfProcesses);
        j = 0;
        minProcess = processQueue[j];
        minProcessIndex = j;
        minProcessArrivalTime = minProcess[2];
        currProcessArrivalTime = minProcessArrivalTime;
        while(currProcessArrivalTime > elapsedTime){
            if(j + 1 < availableProcesses){
                j++;
                currProcessArrivalTime = processQueue[j][2];
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
                minProcessArrivalTime = minProcess[2];
            }
        }
        j = minProcessIndex;
        minProcessBurstTime = minProcess[1];
        for(; j < availableProcesses; j++){
            currProcess = processQueue[j];
            if((currProcess[2] <= elapsedTime) && (currProcess[1] <= minProcessBurstTime)){
                minProcess = currProcess;
                minProcessIndex = j;
                minProcessBurstTime = minProcess[1];
            }
        }
        availableProcesses--;
        elapsedTime += minProcessBurstTime;
        printf("Min Process: {%d, %d, %d}\n", minProcess[0], minProcessBurstTime, minProcess[2]);
        printf("Time elapsed: %d\n**************************************\n", elapsedTime);
        minProcessValues[0] = minProcess[0];
        minProcessValues[1] = minProcessBurstTime;
        minProcessValues[2] = minProcess[2];
        for(j = minProcessIndex; j < numberOfProcesses; j++){
            if(j + 1 != numberOfProcesses){
                processQueue[j][0] = processQueue[j + 1][0];
                processQueue[j][1] = processQueue[j + 1][1];
                processQueue[j][2] = processQueue[j + 1][2];
            } else {
                processQueue[j][0] = minProcessValues[0];
                processQueue[j][1] = minProcessValues[1];
                processQueue[j][2] = minProcessValues[2];
            }
        }
    }
    print(numberOfProcesses);
    printf("There are no more processes available.\n");
    return 0;
}

int main(){
    int numberOfProcesses = 5;
    //print(numberOfProcesses);
    //deleteWithoutShifting(numberOfProcesses);
    delete(numberOfProcesses);
    return 0;
}
