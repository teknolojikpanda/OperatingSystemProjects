//
// Created by Can Doga Ucak on 25.12.2019.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 5
#define LINE_MAX 1024

struct linkedList {
    int name;
    int burstTime;
    int arrivalTime;
    int priority;
    int waitingTime;
    int resumeStatus; //waiting 0, not waiting 1.
}linkedList;

void FCFS(struct linkedList process[], FILE *fp){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i;
    int totalWaiting=0;
    double averageWaiting;

    for(i=0;i<SIZE;i++)
        temp[i]=process[i];

    struct linkedList list;
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
    //Write Consol
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms\n", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaiting);
    //Write File
    fprintf(fp,"Scheduling Method : First Come First Served\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaiting);
    fclose(fp);
}

void SJFS_nonpreemptive(struct linkedList process[], FILE *fp){
    struct linkedList *temp, list, list2;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i,a,b;
    int totalWaitingTime=0;
    double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
    }

    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) {
            if (temp[b].arrivalTime > temp[b + 1].arrivalTime) {
                list2 = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list2;
            }
        }
    }

    for(a=2;a<SIZE;a++) {
        for (b = 1; b < SIZE - a+1; b++) {
            if (temp[b].burstTime > temp[b + 1].burstTime) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    totalWaitingTime = temp[0].waitingTime = 0;

    for(i = 1; i < SIZE; i++){
        temp[i].waitingTime = (temp[i-1].burstTime + temp[i-1].arrivalTime + temp[i-1].waitingTime) - temp[i].arrivalTime;
        totalWaitingTime += temp[i].waitingTime;
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) {
            if (temp[b].name > temp[b + 1].name) {
                list = temp[b];
                temp[b] = temp[b + 1];
                temp[b + 1] = list;
            }
        }
    }

    printf("Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");
    //Write Consol
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaitingTime);
    //Write File
    fprintf(fp,"Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    fclose(fp);
}

void SJFS_preemptive(struct linkedList process[], FILE *fp){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i,x,timer,shortestJob,totalBurstTime;
    int totalWaitingTime=0;
    double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
        totalBurstTime += process[i].burstTime;
    }

    struct linkedList list;
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

    totalWaitingTime = temp[0].waitingTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) {
        if(temp[i].burstTime > 0 && temp[i].arrivalTime <= timer)
            temp[i].burstTime--;

        if(temp[i].burstTime<=0 && temp[i].resumeStatus != 1)
        {
            temp[i].resumeStatus = 1;
            temp[i].waitingTime = (timer+1) - process[i].burstTime - temp[i].arrivalTime;
            totalWaitingTime+=temp[i].waitingTime;
        }
        shortestJob = 65435;
        for(x = 0; x < SIZE; x++){

            if(temp[x].arrivalTime <= (timer+1) && temp[x].resumeStatus != 1){

                if(shortestJob != temp[x].burstTime && shortestJob > temp[x].burstTime){
                    shortestJob = temp[x].burstTime;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    printf("Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");
    //Write Consol
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaitingTime);
    //Write File
    fprintf(fp,"Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    fclose(fp);
}

void PS_preemptive(struct linkedList process[], FILE *fp){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i,x,timer,minimumPriority,totalBurstTime;
    int totalWaitingTime=0;
    double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
        totalBurstTime += process[i].burstTime;
    }

    struct linkedList list;
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

    totalWaitingTime = temp[0].waitingTime = 0;

    i=0;
    for (timer = 0; timer < totalBurstTime; timer++) {
        if(temp[i].burstTime > 0 && temp[i].arrivalTime <= timer)
            temp[i].burstTime--;

        if(temp[i].burstTime<=0 && temp[i].resumeStatus != 1)
        {
            temp[i].resumeStatus = 1;
            temp[i].waitingTime = (timer+1) - process[i].burstTime - temp[i].arrivalTime;
            totalWaitingTime+=temp[i].waitingTime;
        }
        minimumPriority = 65435;
        for(x = 0; x < SIZE; x++){

            if(temp[x].arrivalTime <= (timer+1) && temp[x].resumeStatus != 1){

                if(minimumPriority != temp[x].priority && minimumPriority > temp[x].priority){
                    minimumPriority = temp[x].priority;
                    i=x;
                }
            }
        }
    }

    averageWaitingTime = (double)totalWaitingTime/SIZE;

    printf("Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");
    //Write Consol
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaitingTime);
    //Write File
    fprintf(fp,"Scheduling Method : Priority Scheduling (Preemptive)\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    fclose(fp);
}

void PS_nonpreemptive(struct linkedList process[], FILE *fp){
    struct linkedList *temp;
    temp = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    struct  linkedList list1,list2;
    int i,j,x,y;
    int totalWaitingTime=0;
    double averageWaitingTime;

    for(i=0;i<SIZE;i++) {
        temp[i] = process[i];
    }

    for(i=2;i<SIZE;i++)
        for(j=1;j<SIZE-i+1;j++){
            if(temp[j].priority > temp[j+1].priority){
                list1 = temp[j];
                temp[j] = temp[j+1];
                temp[j+1] = list1;
            }
        }

    totalWaitingTime = temp[0].waitingTime = 0;

    for(i=1;i<SIZE;i++){
        temp[i].waitingTime = (temp[i-1].burstTime + temp[i-1].arrivalTime + temp[i-1].waitingTime) - temp[i].arrivalTime;
        totalWaitingTime+=temp[i].waitingTime;
    }
    averageWaitingTime = (double)totalWaitingTime/SIZE;

    for(x=1;x<SIZE;x++) {
        for (y = 0; y < SIZE - x; y++) {
            if (temp[y].name > temp[y + 1].name) {
                list2 = temp[y];
                temp[y] = temp[y + 1];
                temp[y + 1] = list2;
            }
        }
    }

    printf("Scheduling Method : Priority Scheduling (Non-Preemptive)\nProcess Waiting Times:");
    //Write Consol
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaitingTime);
    //Write File
    fprintf(fp,"Scheduling Method : Priority Scheduling (Non-Preemptive)\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaitingTime);
    fclose(fp);
}

void RR(struct linkedList process[], int quantumTime, FILE *fp){
    int i,x;
    int y = 0;
    int resumeStatus=0;
    int currentTime=0;
    int totalWaitingTime=0;
    double averageWaiting;
    struct linkedList *temp1, *temp2;
    temp1 = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    temp2 = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));

    for(i=0;i<SIZE;i++)
        temp1[i]=process[i];

    struct linkedList list;
    int a,b;
    for(a=1;a<SIZE;a++) {
        for (b = 0; b < SIZE - a; b++) {
            if (temp1[b].arrivalTime > temp1[b + 1].arrivalTime) {
                list = temp1[b];
                temp1[b] = temp1[b + 1];
                temp1[b + 1] = list;
            }
        }
    }

    for(i = 0;i < SIZE; i++)
        temp2[i]=temp1[i];

    do{
        if(y>SIZE-1){y=0;}

        x=0;
        while(x<quantumTime && temp1[y].burstTime > 0){
            x++;
            currentTime++;
            temp1[y].burstTime--;
        }

        if(temp1[y].burstTime <= 0 && temp1[y].resumeStatus != 1){
            temp1[y].waitingTime = currentTime - temp2[y].burstTime - temp1[y].arrivalTime;
            resumeStatus++;
            temp1[y].resumeStatus = 1;
            totalWaitingTime = totalWaitingTime + temp1[y].waitingTime;
        }
        y++;
    }while (resumeStatus < SIZE);

    averageWaiting = (double)totalWaitingTime/SIZE;
    //Write Consol
    printf("Scheduling Method : Round-Robin\nProcess Waiting Times:");
    for(i = 0; i < SIZE; i++) {
        printf("\nP%d: %d ms", i+1, temp1[i].waitingTime);
    }
    printf("\nAverage waiting time: %f ms\n",averageWaiting);
    //Write File
    fprintf(fp,"Scheduling Method : First Come First Served\nProcess Waiting Times:");

    for(i = 0; i < SIZE; i++) {
        fprintf(fp,"\nP%d: %d ms", i+1, temp1[i].waitingTime);
    }
    fprintf(fp,"\nAverage waiting time: %f ms\n",averageWaiting);
    fclose(fp);
}

int main(int argc, char **argv) {
    struct linkedList *process;
    process = (struct linkedList *) malloc (SIZE*sizeof(struct linkedList));
    int i = 0;
    int mode = 0;// 0 => Preemptive && 1 => Non-Preemptive
    int choice,option,option2,quantumTime;
    FILE *fpRead,*fpWrite;
    char line[LINE_MAX];
    char *ovalue = NULL;
    unsigned int num[3];

    opterr = 0;

    while ((choice = getopt (argc, argv, "f:o:")) != -1)
        switch (choice)
        {
            case 'f':
                if ((fpRead = fopen(optarg, "r")) == NULL)
                    return 0;
                while (fgets(line, LINE_MAX, fpRead) != NULL) {
                    sscanf(line,"%d:%d:%d\n",&num[0],&num[1],&num[2]);
                    process[i].name = i+1;
                    process[i].burstTime = num[0];
                    process[i].arrivalTime = num[1];
                    process[i].priority = num[2];
                    i++;
                }
                fclose(fpRead);
                break;
            case 'o':
                ovalue = optarg;
                fpWrite = fopen(optarg,"w+");
                break;
            default:
                abort ();
        }
    do{
        if (mode == 0)
            printf("MODE : Preemptive\n");
        else if (mode == 1)
            printf("MODE : Non-Preemptive\n");
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
                    printf("\nMODE : Non-Preemptive\n");
                printf("1) First Come, First Served Scheduling\n");
                printf("2) Shortest-Job-First Scheduling\n");
                printf("3) Priority Scheduling\n");
                printf("4) Round-Robin Scheduling\n");
                printf("5) Back\n");
                printf("Option> ");
                scanf("%d",&option2);
                switch (option2){
                    case 1:
                        FCFS(process, fpWrite);
                        break;
                    case 2:
                        if (mode == 0){
                            SJFS_preemptive(process,fpWrite);
                        }
                        if (mode == 1){
                            SJFS_nonpreemptive(process,fpWrite);
                        }
                        break;
                    case 3:
                        if (mode == 0){
                            PS_preemptive(process,fpWrite);
                        }
                        if (mode == 1){
                            PS_nonpreemptive(process,fpWrite);
                        }
                        break;
                    case 4:
                        printf("\n Enter quantum time : ");
                        scanf("%d",&quantumTime);
                        RR(process, quantumTime, fpWrite);
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
                fpRead = fopen(ovalue, "r");
                while (fgets(line, LINE_MAX, fpRead)){
                    printf(line);
                }
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