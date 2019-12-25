//
// Created by Can Doga Ucak on 25.12.2019.
//

#include <stdio.h>

typedef struct linkedList {

    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
}linkedList;

void FCFS(linkedList process[],int size){

    linkedList temp[10];
    int i;
    int totlWaiting=0;
    double averageWaiting;

    for(i=0;i<size;i++)
        temp[i]=process[i];

    linkedList list;
    int a,b;
    for(a=1;a<size;a++) {
        for (b = 0; b < size - a; b++) {
            if (temp[b].arrivalTime > temp[b + 1].arrivalTime) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    totlWaiting = temp[0].waitingTime = 0;

    for(i=1;i<size;i++){
        temp[i].waitingTime = (temp[i-1].burstTime + temp[i-1].arrivalTime + temp[i-1].waitingTime) - temp[i].arrivalTime;
        totlWaiting+=temp[i].waitingTime;
    }
    averageWaiting = (double)totlWaiting/size;

    printf("Scheduling Method : First Come First Served\nProcess Waiting Times:");
    for(i=0;i<size;i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaiting);
}

int main() {
    struct linkedList process[5];
    process[0].burstTime = 5;
    process[1].burstTime = 4;
    process[2].burstTime = 3;
    process[3].burstTime = 4;
    process[4].burstTime = 3;
    process[0].arrivalTime = 0;
    process[1].arrivalTime = 1;
    process[2].arrivalTime = 1;
    process[3].arrivalTime = 2;
    process[4].arrivalTime = 3;
    process[0].priority = 3;
    process[1].priority = 2;
    process[2].priority = 1;
    process[3].priority = 2;
    process[4].priority = 1;

    FCFS(process,5);

    return 0;
}