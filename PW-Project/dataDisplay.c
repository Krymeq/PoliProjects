#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>   
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include "struct.h"

#define true 1
#define false 0

int main()
{
    struct msg programData;
        programData.msgtyp = 0;
        programData.ilosc_krolowych = 0;
        programData.ilosc_miodku = 0;
        programData.ilosc_misiow = 0;
        programData.ilosc_robotnic = 0;
        programData.ilosc_wojownikow = 0;
    
    int temp = getpid();

    int msgqid = msgget(163, IPC_CREAT | 0640);
    int msgqid2 = msgget(190, IPC_CREAT | 0640);
    struct msgpid sendPID;
        sendPID.mtype = 3;
        sendPID.processPID = temp;
    
    msgsnd(msgqid2, &sendPID, sizeof(sendPID), 0);
    
    // poniższe odpala programik 
    msgrcv(msgqid, &sendPID, sizeof(sendPID), 3, 0);
    while(true)
    {
        msgrcv(msgqid, &programData, sizeof(programData), 4, 0);
        system("clear");
        printf("Czyhające misie: %d\n", programData.ilosc_misiow);
        printf("Miód w magazynie: %d\n", programData.ilosc_miodku);
        printf("Robotnice: %d\n", programData.ilosc_robotnic);
        printf("Wojownicy: %d\n", programData.ilosc_wojownikow);
        printf("Królowe: %d\n", programData.ilosc_krolowych);
    }
    return 0;
}