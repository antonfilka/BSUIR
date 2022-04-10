#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <locale.h>

int compare(const void *s1, const void *s2);
char* cut(char *str, int index);

int main(int argc, char **argv, char **envp){
    system("clear");
    if(argc < 2){
        printf("too low arguments!\n");
        return 0;
    }
    if(!fopen(argv[1], "r")){
        printf("can't open file!\n");
        return 0;
    }

    setlocale(LC_COLLATE,"C");
    pid_t pid, ppid;

    extern char **environ;

    int size = 0, i = 0;
    while(envp[i]){
        size++;
        i++;
    } 
    qsort(envp, size, sizeof(char*), compare);
    i = 0;
    while(envp[i]){
        printf("%s\n", envp[i]);
        i++;
    } 
    printf("\n");


    char n, **args = NULL, **envpChild = NULL, str, *buff = NULL, **env;
    int counter = 0;

    args = malloc(4 * sizeof(char*));
    args[1] = malloc(strlen(argv[1]) * sizeof(char));
    args[3] = malloc(2*sizeof(char*));

    strcat(args[1], argv[1]);
    strcat(args[3], (char*)"0");

    pid_t childPid;

    while(1){
        printf("option: ");
        scanf("%s", &n);

        system("clear");

        
        args[0] = malloc(9 * sizeof(char));
        args[2] = malloc(2 * sizeof(char));


        strcat(args[0], "child_");

        str = counter/10+'0';
        strncat(args[0], &str, 1);
        str = counter%10+'0';
        strncat(args[0], &str, 1);
        
        switch (n)
        {
        case '+':
            strcat(args[2], "+");
            childPid = fork();
            if(childPid == 0) execve(strcat(getenv("CHILD_PATH"), "child"), args, envp);
            counter++;
            break;
        case '*':
            env = envp;
            strcat(args[2], "*");
            while(*env){
                if(strstr(*env, "CHILD_PATH")){
                    buff = malloc((strlen(*env)-strlen("CHILD_PATH")) * sizeof(char));                    
                    childPid = fork();
                    if(childPid == 0) execve(strcat(cut(*env, strlen("CHILD_PATH")+1), "child"), args, envp);
                    break;
                }
                *env += 1;
            }
            counter++;
            break;
        case '&':
            env = environ;
            strcat(args[2], "&");
            while(*env){
                if(strstr(*env, "CHILD_PATH")){
                    buff = malloc((strlen(*env)-strlen("CHILD_PATH")) * sizeof(char));                    
                    childPid = fork();
                    if(childPid == 0) execve(strcat(cut(*env, strlen("CHILD_PATH")+1), "child"), args, envp);
                    break;
                }
                *env += 1;
            }
            counter++;
            break;
        case '-':
            return 0;
            break;
        default:
            printf("bad option!\n");
            break;
        }
        wait(NULL);
    }

    return 0;
}

int compare(const void *s1, const void *s2){
    return strcmp(s1,s2);
}

char* cut(char *str, int index){
    char *rez = malloc((strlen(str)-index) * sizeof(char));

    for(int i = index; i < (int)strlen(str); i++) strncat(rez, &str[i], 1);
    return rez;
}
