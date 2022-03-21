#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>   
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <time.h>
#include "struct.h"

typedef int bool;

#define true 1
#define false 0

#define STARTOWY_MIODEK 200
#define CZEKANIE_MISIA 10
#define KOSZT_ROBOTNICY 7
#define KOSZT_ZOLNIERZA 10
#define KOSZT_KROLOWEJ 500
#define CZAS_REKR_ROBOTNICY 3
#define CZAS_REKR_ZOLNIERZA 5
#define CZAS_REKR_KROLOWEJ 9
#define WSKAZNIK_GLODU 10
#define PRZYROST_GLODU 10
#define PRODUKCJA_MIODKU 2
#define CZAS_PRODUKCJI_MIODKU 3
#define ZJADANY_MIODEK 1
#define SZANSA_NA_ZAWOLANIE 5
#define CO_ILE_PCOLKA_JE 14
#define ILE_WOJOW_NA_MISIA 10
#define ILE_MIODKU_JE_MIS 50

bool *koniecGry;
bool *misAtakuje;
int *magazynMiodku;
int *semKeyID;
int *iloscRobotnic;
int *iloscWojownikow;
int *iloscMisiow;
int *iloscKrolowych;

void cliffhanger(){}

int check_if_convertible(char* var)
{
    int x = 0;
    int i = 0;
    do
    {
        if (var[i] == '-' && i == 0) 
        {
            i++;
            continue;
        }
        if (var[i] < '0' || var[i] > '9')
        {
            x = 1;
            break;
        }
        else
            i++;
    } while(var[i] != '\0' && var[i] != '\n');
    if (x == 0) 
    {
        long temp = atol(var);
        if (temp > 2147483647 || temp < -2147483648)
            x = 1; 
    }
    if (x == 1) printf("Nieprawidłowe wejście. Podaj liczbę jeszcze raz\n");
    return x;
}

char* scan_integer_once()
{
    size_t size = 11;
    char *term = malloc(sizeof(char)*11);
    getline(&term, &size, stdin);
    term[10] = '\0';
    return term;
}

void scan_integer(int* x)
{
    char* ptrbuf;
    do
    {
        ptrbuf = scan_integer_once();
    } while (check_if_convertible(ptrbuf));
    *x = atoi(ptrbuf);
    free(ptrbuf);
}

void sem_operation(int semGroupID, int sem_num, int howMuch)
{
    struct sembuf buf;
        buf.sem_num = sem_num;
        buf.sem_op = howMuch;
        buf.sem_flg = 0;
    semop(semGroupID, &buf, 1);
}

bool zatwierdz_rekrutacje(int typ_pszczoly, int ilosc)
{
    bool udalo_sie = false;
    int naleznosc;
    if (typ_pszczoly == 1)
    {
        naleznosc = ilosc * KOSZT_ROBOTNICY;
    }
    else if (typ_pszczoly == 2)
    {
        naleznosc = ilosc * KOSZT_ZOLNIERZA;
    }

    else if (typ_pszczoly == 3)
    {
        naleznosc = ilosc * KOSZT_KROLOWEJ;
    }
    sem_operation(*semKeyID, 1, -1);
    if (((*magazynMiodku) - naleznosc) > 0)
    {
        udalo_sie = true;
        *magazynMiodku -= naleznosc;
    }
    sem_operation(*semKeyID, 1, 1);
    return udalo_sie;
}

/* Funkcja tworząca pszczółkę.
 * Typ 1: robotnica
 * Typ 2: wojownik
 */
int pszczolka(int typ_pszczoly, bool czy_czekaj)
{
    int pid = fork();
    if (pid == 0)
    {
        int key = shmget(getpid(), sizeof(bool), IPC_CREAT | 0640);
        bool *working = shmat(key, NULL, 0);
        *working = true;
        if (typ_pszczoly == 1)
        {
            if (czy_czekaj) sleep(CZAS_REKR_ROBOTNICY);
            sem_operation(*semKeyID, 5, -1);
            (*iloscRobotnic)++;
            sem_operation(*semKeyID, 5, 1);
            if (fork() == 0) //PROCES JEDZĄCY
            {
                while(true)
                {
                    sleep(CO_ILE_PCOLKA_JE);
                    if (*working == true)
                    {
                        while(*misAtakuje == true)
                        {
                            usleep(20000);
                        }
                        sem_operation(*semKeyID, 0, -1);
                        sem_operation(*semKeyID, 1, -1);
                        if (*magazynMiodku >= ZJADANY_MIODEK)
                        {
                            *magazynMiodku -= ZJADANY_MIODEK;
                            sem_operation(*semKeyID, 1, 1);
                            sem_operation(*semKeyID, 0, 1);
                        }
                        else 
                        {
                            kill(getppid(), SIGUSR1);
                            sem_operation(*semKeyID, 1, 1);
                            sem_operation(*semKeyID, 0, 1);
                            break;
                        }
                    }
                    else break;
                }

                // Jeśli nie ma wystarczająco miodku żeby wykarmić
                // pszczółkę to ona ginie - wyślij do rodzica (procesu, który
                // produkuje miodek) sygnał SIGUSR.
                exit(0);
            }
            else if (fork() == 0)
            {
                while(true) //proces produkujący
                {
                    sleep(CZAS_PRODUKCJI_MIODKU);
                    if (*working == true)
                    {
                        while(*misAtakuje == true)
                        {
                            usleep(20000);
                        }
                        sem_operation(*semKeyID, 0, -1);
                        sem_operation(*semKeyID, 1, -1);
                        *magazynMiodku += PRODUKCJA_MIODKU;
                        sem_operation(*semKeyID, 1, 1);
                        sem_operation(*semKeyID, 0, 1);
                    }
                    else break;
                }
                exit(0);
            }
            else    // proces czekający 
            {
                pause();
                *working = false;
                sem_operation(*semKeyID, 5, -1);
                (*iloscRobotnic)--;
                sem_operation(*semKeyID, 5, 1);
                shmdt(working);
                shmctl(key, IPC_RMID, 0);
                exit(0);
            }
        }

        else if (typ_pszczoly == 2) // pszczoła wojownik
        {
            if (czy_czekaj) sleep(CZAS_REKR_ZOLNIERZA);
            sem_operation(*semKeyID, 6, -1);
            (*iloscWojownikow)++;
            sem_operation(*semKeyID, 6, 1);
            if (fork() == 0)
            {
                while(true)
                {
                    sleep(CO_ILE_PCOLKA_JE);
                    if (*working == true)
                    {
                        while(*misAtakuje == true)
                        {
                            usleep(20000);
                        }
                        sem_operation(*semKeyID, 0, -1);
                        sem_operation(*semKeyID, 1, -1);
                        if (*magazynMiodku >= ZJADANY_MIODEK)
                        {
                            *magazynMiodku -= ZJADANY_MIODEK;
                            sem_operation(*semKeyID, 1, 1);
                            sem_operation(*semKeyID, 0, 1);
                        }
                        else 
                        {
                            kill(getppid(), SIGUSR1);
                            sem_operation(*semKeyID, 1, 1);
                            sem_operation(*semKeyID, 0, 1);
                            break;
                        }
                    }
                    else break;
                }
                exit(0);
            }
            else    // proces czekający 
            {
                pause();
                *working = false;
                sem_operation(*semKeyID, 6, -1);
                (*iloscWojownikow)--;
                sem_operation(*semKeyID, 6, 1);
                shmdt(working);
                shmctl(key, IPC_RMID, 0);
                exit(0);
            }
        }
    }
    else
    {   
        return pid;
    }
    
}
int mis(int msgqid)
{
    *iloscMisiow += 1;
    int pid = fork();
    if (pid == 0)
    {   
        int wskaznikGloduMisia = WSKAZNIK_GLODU;
        int szansaNaZawolanie = SZANSA_NA_ZAWOLANIE;
        srand(time(0) % getpid());
        // czekaj ile masz czekać
        while(true)
        {
            sleep(CZEKANIE_MISIA);
            int todo = (rand() % 100) + 1;
            
            // oblicz czy atak, mniejszy/równy - pomyślny, 
            // większy - miś niegłodny;
            if (todo <=  wskaznikGloduMisia)
            {
                sem_operation(*semKeyID, 2, -1);
                *misAtakuje == true;
                int ile = *iloscWojownikow;
                // atak pomyslny - mniej wojowników
                if (ile < ILE_WOJOW_NA_MISIA)
                {
                    struct msgbuf rozkaz;
                        rozkaz.mtype = 1;
                        rozkaz.zamowienie.typ = 2;
                        rozkaz.zamowienie.typ_pszczoly = 2;
                        rozkaz.zamowienie.ilosc = ile;
                    msgsnd(msgqid, &rozkaz, sizeof(rozkaz), 0);
                        rozkaz.zamowienie.typ_pszczoly = 1;
                        rozkaz.zamowienie.ilosc = ILE_WOJOW_NA_MISIA - ile; 
                    msgsnd(msgqid, &rozkaz, sizeof(rozkaz), 0);

                    sem_operation(*semKeyID, 0, -10);
                    sem_operation(*semKeyID, 1, -1);
                    if (*magazynMiodku < ILE_MIODKU_JE_MIS)
                    {
                        (*magazynMiodku) = 0;
                    }
                    else
                    {
                        *magazynMiodku -= ILE_MIODKU_JE_MIS;
                    }
                    sem_operation(*semKeyID, 1, 1);
                    sem_operation(*semKeyID, 0, 10);
                }
                // atak niepomyślny - więcej wojowników
                else
                {
                    struct msgbuf rozkaz;
                        rozkaz.mtype = 1;
                        rozkaz.zamowienie.typ = 2;
                        rozkaz.zamowienie.typ_pszczoly = 2;
                        rozkaz.zamowienie.ilosc = ILE_WOJOW_NA_MISIA;
                    msgsnd(msgqid, &rozkaz, sizeof(rozkaz), 0);
                }
                wskaznikGloduMisia = WSKAZNIK_GLODU;
                *misAtakuje = false;
                sem_operation(*semKeyID, 2, 1);
            }
            todo = (rand()%100) + 1;
            if (todo <= szansaNaZawolanie)
            {
                struct msgpid msg;
                    msg.mtype = 5;
                    msg.processPID = 0;
                msgsnd(msgqid, &msg, sizeof(msg), 0);
                szansaNaZawolanie = SZANSA_NA_ZAWOLANIE; // zawołaj i resetuj
            }
            else
            {
                szansaNaZawolanie += SZANSA_NA_ZAWOLANIE;
            }
        }
        exit(0);
    }
    else return pid; 
}

int obslugaMisiow(int msgqid)
{
    int pid = fork();
    if (pid == 0)
    {
        mis(msgqid);
        struct msgpid wiadom;
        while(true)
        {
            msgrcv(msgqid, &wiadom, sizeof(wiadom), 5, 0);  //czekaj na wiadomość typu 5 - zrób misia.
            mis(msgqid);
        }
        exit(0);
    }
    else return pid;
}
// Parametry:
// -ID kolejki komunikatów, którą będziemy komunikować procesy.
// -Wskaźnik na współdzielony obszar pamięci przechowujący ilość miodku.
int obslugaPszczolek(int msgqid)
{
    int pid = fork();
    if (pid == 0)
    {
       /*
        * Proces obsługuje procesy robotnic - odpowiada
        * za ich rekrutację, śmierć i przechowuje ich
        * PID. Rozkazy do procesu przechwytywane są rzucając
        * typ wiadomości 1 do komunikatów w kolejce.
        */
    
        int rozm_tab_wojow = 200;
        int rozm_tab_robot = 200;
        int *deskr_wojownikow = malloc(sizeof(int)*200);
        int *deskr_robotnic = malloc(sizeof(int)*200);
        struct msgbuf rozkaz;
        while(true)
        {
            // proces czeka na rozkaz rekrutacji/zabicia od misiów itd.
            msgrcv(msgqid, &rozkaz, sizeof(rozkaz), 1, 0);

            //sprawdź typ rozkazu (1 - rekrutacja, 2 - zabicie) 
            switch(rozkaz.zamowienie.typ)
            {
                case 1:
                {
                    switch(rozkaz.zamowienie.typ_pszczoly)
                    {
                        case 1:
                        {   
                            // stwórz pszczółkę - robotnicę
                            for(int i = 0; i < rozkaz.zamowienie.ilosc; i++)
                            {
                                int index;
                                bool przypisano = false;       
                                
                                // znajdź pierwszy indeks, który jest równy zero (nie ma tam
                                // zapisanego żadnego deskryptora pszczoły)
                                for (int i = 0; i < rozm_tab_robot; i++)
                                {
                                    if (deskr_robotnic[i] <= 0)
                                    {
                                        przypisano = true;
                                        index = i;
                                        break;
                                    }
                                }

                                if (przypisano == false)
                                {
                                    int* tmp = (int*) realloc(deskr_robotnic, sizeof(int)*(rozm_tab_robot + 100));
                                    deskr_robotnic = tmp;
                                    index = rozm_tab_robot;
                                    rozm_tab_robot = rozm_tab_robot + 100;
                                }
                                deskr_robotnic[index] = pszczolka(1, true);
                            }
                            break;
                        }
                        case 2:
                        {
                        // stwórz pszczółkę - wojownika
                            for(int i = 0; i < rozkaz.zamowienie.ilosc; i++)
                            {
                                int index;
                                bool przypisano = false;       
                                
                                // znajdź pierwszy indeks, który jest równy zero (nie ma tam
                                // zapisanego żadnego deskryptora pszczoły)
                                for (int i = 0; i < rozm_tab_robot; i++)
                                {
                                    if (deskr_wojownikow[i] <= 0)
                                    {
                                        przypisano = true;
                                        index = i;
                                        break;
                                    }
                                }

                                if (przypisano == false)
                                {
                                    int *tmp = (int*) realloc(deskr_wojownikow, sizeof(int)*(rozm_tab_wojow + 100));
                                    deskr_wojownikow = tmp;
                                    index = rozm_tab_wojow;
                                    rozm_tab_wojow = rozm_tab_wojow + 100;
                                }
                                deskr_wojownikow[index] = pszczolka(2, true);
                            }
                            break;
                        }
                        case 3:
                        {
                            sleep(CZAS_REKR_KROLOWEJ);
                            srand(time(0));
                            // Który rodzaj pcółki
                            int x = (rand() % 3) + 1;
                            if (x == 1)
                            {
                                printf("Narodziny robotnicy!\n");
                                pszczolka(1, false);
                            }
                            else if (x == 2)
                            {
                                printf("Narodziny żołnierza!\n");
                                pszczolka(2, false);
                            }
                            else 
                            {
                                printf("Narodziny królowej!\n");
                                sem_operation(*semKeyID, 3, -1);
                                (*iloscKrolowych)++;
                                if (*iloscKrolowych >= 3)
                                {
                                    printf("Gratulacje! Zwycięstwo!\n");
                                    *koniecGry = true;
                                }
                                sem_operation(*semKeyID, 3, 1);
                            }
                            break;
                        }
                    }
                    break;
                }
                case 2:
                {
                    int i = 0, ileZabito = 0;
                    switch (rozkaz.zamowienie.typ_pszczoly)
                    {
                        // zabijanie robotnic
                        case 1:
                        {

                            //póki nie dojdziemy do końca tablicy albo nie zabijemy tylu pszczółek ile jest w rozkazie
                            while(i < rozm_tab_robot && ileZabito < rozkaz.zamowienie.ilosc)
                            {
                                if (deskr_robotnic[i] != 0)
                                {
                                    kill(deskr_robotnic[i], SIGUSR1);
                                    deskr_robotnic[i] = 0;
                                    ileZabito++;
                                }
                                
                                i++;
                            }
                            break;
                        }
                        case 2:
                        {
                            while(i < rozm_tab_wojow && ileZabito < rozkaz.zamowienie.ilosc)
                            {
                                if (deskr_wojownikow[i] != 0)
                                {
                                    kill(deskr_wojownikow[i], SIGUSR1);
                                    deskr_wojownikow[i] = 0;
                                    ileZabito++;
                                }
                                i++;
                            }
                            break;
                        }
                    }
                    break;
                }
            }

        }
        free(deskr_robotnic);
        free(deskr_wojownikow);
        exit(0);
    }
    else
    {
        return pid;
    }
}

int main(int argc, char* argv[])
{
    int msgqid = msgget(163, IPC_CREAT | 0640);
    int msgqid2 = msgget(190, IPC_CREAT | 0640);
    int shared_id = shmget(21, sizeof(int) * 8, IPC_CREAT | 0640);

    signal(SIGUSR1, cliffhanger);

    magazynMiodku = shmat(shared_id, NULL, 0);
    iloscRobotnic = shmat(shared_id, NULL, 0) + sizeof(int);
    iloscWojownikow = shmat(shared_id, NULL, 0) + sizeof(int) * 2;
    iloscMisiow = shmat(shared_id, NULL, 0) + sizeof(int) * 3;
    iloscKrolowych = shmat(shared_id, NULL, 0) + sizeof(int) * 4;
    semKeyID = shmat(shared_id, NULL, 0) + sizeof(int) * 5;
    misAtakuje = shmat(shared_id, NULL, 0) + sizeof(int) * 6;
    koniecGry = shmat(shared_id, NULL, 0) + sizeof(int) * 7;

    *koniecGry = false;
    *magazynMiodku = STARTOWY_MIODEK;
    *misAtakuje = false;
    *iloscKrolowych = 0;
    *iloscMisiow = 0;
    *iloscRobotnic = 0;
    *iloscWojownikow = 0;

    *semKeyID = semget(1, 7, IPC_CREAT | 0640);
    
    /* 
     * Inicjalizacja semaforów:
     * 0 - oznaczający 100 miejsc w magazynie
     * Pozostałe zapewniają wyłączny dostęp do zmiennych, odpowiednio:
     * 1 - magazynMiodku
     * 2 - misAtakuje
     * 3 - iloscKrolowych
     * 4 - iloscMisiow
     * 5 - iloscRobotnic
     * 6 - iloscWojownikow
     */

    semctl(*semKeyID, 0, SETVAL, 100);
    semctl(*semKeyID, 1, SETVAL, 1);
    semctl(*semKeyID, 2, SETVAL, 1);
    semctl(*semKeyID, 3, SETVAL, 1);
    semctl(*semKeyID, 4, SETVAL, 1);
    semctl(*semKeyID, 5, SETVAL, 1);
    semctl(*semKeyID, 6, SETVAL, 1);

    int command;
    printf("Menu:\n1) Start gry\n2) Wyjście z gry\n");
    
    struct msgpid msg;
    msgrcv(msgqid2, &msg, sizeof(msg), 3, 0);

    int pidDataDisplay = msg.processPID;

    while(command != 1)
    {
        scan_integer(&command);
        if (command == 2)
        {
            // Wyjście przedwczesne - usuwanie czego trzeba z systemu
            kill(pidDataDisplay, 9);
            shmdt(iloscKrolowych);
            shmdt(iloscMisiow);
            shmdt(iloscRobotnic);
            shmdt(iloscWojownikow);
            shmdt(magazynMiodku);
            shmdt(semKeyID);
            shmctl(shared_id, IPC_RMID, 0);
            msgctl(msgqid, IPC_RMID, 0);
            msgctl(msgqid2, IPC_RMID, 0);
            exit(0);
        }
        else if (command != 1)
        {
            printf("Nie rozpoznano komendy.\n");
        }
    }
    printf("Start gry\n");

    //Wiadomość startująca program pokazujący dane.
    msgsnd(msgqid, &msg, sizeof(msg), 0);
    
    int pidObslugiPszczolek = obslugaPszczolek(msgqid);
    int pidObslugiMisiow = obslugaMisiow(msgqid);

    // Proces przesyłający dane do podprogramu
    // Typ wiadomości do podprogramu (msgtyp) = 4

    if (fork() == 0) 
    {
        while((*koniecGry) == false)
        {
            struct msg wiad;
            wiad.msgtyp = 4;
            wiad.ilosc_krolowych = *iloscKrolowych;
            wiad.ilosc_miodku = *magazynMiodku;
            wiad.ilosc_misiow = *iloscMisiow;
            wiad.ilosc_robotnic = *iloscRobotnic;
            wiad.ilosc_wojownikow = *iloscWojownikow;
            msgsnd(msgqid, &wiad, sizeof(wiad), 0);
            if((*iloscRobotnic < 1) && (*magazynMiodku < KOSZT_ROBOTNICY))
            {
                printf("Misie zniszczyły Twój ul do końca. Przegrałeś...\n");
                *koniecGry = true;
            }
            usleep(50000);
        }
        exit(0);
    }
    else    // Menu właściwe
    {
        while(true)
        {
            if (*koniecGry == true)
            {
                break;
            }
            else
            {
                int todo;
                printf("-------------------------\n");
                printf("1) Rekrutacja robotnicy (%d miodku)\n", KOSZT_ROBOTNICY);
                printf("2) Rekrutacja wojownika (%d miodku)\n", KOSZT_ZOLNIERZA);
                printf("3) Rekrutacja królowej (%d miodku)\n", KOSZT_KROLOWEJ);
                printf("4) Wyjście z gry\n");

                scan_integer(&todo);
                if (todo == 1 || todo == 2)
                {
                    printf("Podaj ilość: \n");
                    int ile;
                    scan_integer(&ile);
                    if (ile > 0 && ile < 500)
                    {
                        if (zatwierdz_rekrutacje(todo, ile))
                        {
                            struct msgbuf wiad;
                            wiad.mtype = 1;
                            wiad.zamowienie.typ = 1;
                            wiad.zamowienie.typ_pszczoly = todo;
                            wiad.zamowienie.ilosc = ile;
                            msgsnd(msgqid, &wiad, sizeof(wiad), 0);
                        }                    
                        else printf("Niewystarczająco miodku\n");
                    }
                    else 
                    {
                        printf("Podano nieprawidłową ilość.\n");
                        printf("Jednocześnie można rekrutować maksymalnie 500 pszczółek\n");
                    }
                }
                else if (todo == 3)
                {
                    if(zatwierdz_rekrutacje(todo, 1))
                    {
                        struct msgbuf wiad;
                            wiad.mtype = 1;
                            wiad.zamowienie.typ = 1;
                            wiad.zamowienie.typ_pszczoly = todo;
                            wiad.zamowienie.ilosc = 1;
                        msgsnd(msgqid, &wiad, sizeof(wiad), 0);
                    }
                }
                else if (todo == 4)
                {
                    break;
                }
                else printf("Nie rozpoznano komendy.\n");
            }
        }
    }
    

    //Usuwanie czego trzeba z systemu
    kill(pidDataDisplay, 9);
    shmdt(iloscKrolowych);
    shmdt(iloscMisiow);
    shmdt(iloscRobotnic);
    shmdt(iloscWojownikow);
    shmdt(magazynMiodku);
    shmdt(semKeyID);
    shmctl(shared_id, IPC_RMID, 0);
    msgctl(msgqid, IPC_RMID, 0);
    msgctl(msgqid2, IPC_RMID, 0);
    return 0;
}