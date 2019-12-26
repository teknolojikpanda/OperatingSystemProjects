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
    int resumeStatus;
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
    int mode = 0;// 0 => Preemptive && 1 => Non-Preemptive
    int choice,option,option2;
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

    do{
        if (mode == 0)
            printf("MODE : Preemptive\n");
        else if (mode == 1)
            printf("MODE : Preemptive\n");
        printf("1) Scheduling Method\n");
        printf("2) Preemptive Mode\n");
        printf("3) Non-Preemptive Mode\n");
        printf("4) Show Result\n");
        printf("5) End Program\n");
        printf("Option> ");
        scanf("%d",&option);
        switch (option){
            case 1:
                if (mode == 0)
                    printf("\n\n\n1\nMODE : Preemptive\n");
                else if (mode == 1)
                    printf("\nMODE : Preemptive\n");
                printf("1) First Come, First Served Scheduling\n");
                printf("2) Shortest-Job-First Scheduling\n");
                printf("3) Priority Scheduling\n");
                printf("4) Round-Robin Scheduling\n");
                printf("5) Back\n");
                printf("Option> ");
                scanf("%d",&option2);
                switch (option2){
                    case 1:
                        FCFS(process);
                        break;
                    case 2:
                        if (mode == 0){
                            //SJFS_preemptive(process);
                        }
                        if (mode == 1){
                            //SJFS_nonpreemptive(process);
                        }
                        break;
                    case 3:
                        if (mode == 0){
                            //PS_preemptive(process);
                        }
                        if (mode == 1){
                            //PS_nonpreemptive(process);
                        }
                        break;
                    case 4:
                        //RR(process);
                        break;
                    case 5:
                        break;
                    default:
                        printf("Invalid Option!\n");
                        break;
                }
                break;
            case 2:
                mode = 0;
                break;
            case 3:
                mode = 1;
                break;
            case 4:

                //Show Result

                break;
            case 5:
                abort();
            default:
                printf("Invalid Option!");
                break;
        }
    }while (option != 5);
    return 0;
}

