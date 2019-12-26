//
// Created by Can Doga Ucak on 25.12.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define LINE_MAX 1024

typedef struct linkedList {

    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
}linkedList;

void FCFS(linkedList process[]){

    linkedList temp[SIZE];
    int i;
    int totalWaiting=0;
    double averageWaiting;

    for(i=0;i<SIZE;i++)
        temp[i]=process[i];

    linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) {
            if (temp[b].arrivalTime > temp[b + 1].arrivalTime) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    totalWaiting = temp[0].waitingTime = 0;

    for(i = 1; i < SIZE; i++){
        temp[i].waitingTime = (temp[i-1].burstTime + temp[i-1].arrivalTime + temp[i-1].waitingTime) - temp[i].arrivalTime;
        totalWaiting += temp[i].waitingTime;
    }
    averageWaiting = (double)totalWaiting/SIZE;

    printf("Scheduling Method : First Come First Served\nProcess Waiting Times:");
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaiting);
}

void SJFS_nonpreemptive(linkedList process[]){

}

void SJFS_preemptive(linkedList process[]){

}

void PS_preemptive(linkedList process[]){

}

void PS_nonpreemptive(linkedList process[]){

}

void RR(linkedList process[]){

}

int main(int argc, char **argv) {
    struct linkedList process[SIZE];
    int i = 0;
    int choice;
    FILE *fp;
    char line[LINE_MAX];
    unsigned int num[3];

    opterr = 0;

    while ((choice = getopt (argc, argv, "f:o:")) != -1)
        switch (choice)
        {
            case 'f':
                if ((fp = fopen(optarg, "r")) == NULL)
                    return 0;
                while (fgets(line, LINE_MAX, fp) != NULL) {
                    sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
                    process[i].burstTime = num[0];
                    process[i].arrivalTime = num[1];
                    process[i].priority = num[2];
                    i++;
                }
                fclose(fp);
                break;
            case 'o':

                break;
            default:
                abort ();
        }

    FCFS(process);
    //SJFS_nonpreemptive(process);
    //SJFS_preemptive(process);
    //PS_nonpreemptive(process);
    //PS_preemptive(process);
    //RR(process);

    return 0;
}

