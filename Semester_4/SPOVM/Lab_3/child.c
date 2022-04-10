#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

char **var;
int numOfVar;
int find(char *str);

int main(int argc, char **argv, char **envp){
    pid_t pid, ppid;

    extern char **environ;

    FILE *f = fopen(argv[1], "r");

    var = NULL;
    numOfVar = 0;
    char *str = (char*)malloc(strlen(argv[1]) * sizeof(char)); 
 
    
    while(1){
        fscanf(f, "%s", str);

        if(feof(f)) break;

        numOfVar++;
        var = (char**)realloc(var, numOfVar * sizeof(char*));
        var[numOfVar-1] = (char*)malloc(strlen(str) * sizeof(char));
        strcpy(var[numOfVar-1], str);
    }

    pid = getpid();
    ppid = getppid();
    printf("Name: %s\npid: %d\nppid: %d\n", argv[0], pid, ppid);
    // puts(argv[2]);
    switch (argv[2][0])
    {
    case '+':
        for(int i = 0; i < numOfVar; i++) if(getenv(var[i])) printf("%s=%s\n", var[i], getenv(var[i]));
        break;
    case '*':
        while(*envp){
             if(find(*envp)) printf("%s\n", *envp);
             *envp++;
        }
        break;
    case '&':
        while(*environ){
             if(find(*environ)) printf("%s\n", *environ);
             *environ++;
        }
        break;
    }

    printf("\n");
    exit(0);
}

int find(char *str){
    char *strForCompare = "";
    for(int i = 0; i < numOfVar; i++){
        strForCompare = (char*)malloc((strlen(var[i])+1) * sizeof(char));
        strcpy(strForCompare, var[i]);
        strcat(strForCompare, "=");
        if(strstr(str, strForCompare)-str == 0) return 1;
    } 
    return 0;
}