#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

struct msginfoxd
{
    long msgtyp;
    int buf1;
    int buf2;
    int buf3;
};

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
    return x;
}

char* scan_integer_once()
{
    size_t size = 11;
    char *term = malloc(sizeof(char)*11);
    getline(&term, &size, stdin);
    term[10] = '\0';
    printf("Wczytano: %s\n", term);
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


int main(int argc, char* argv[])
{
    int i;
    scan_integer(&i);
    printf("Liczba %d\n", i);
    return 0;
}