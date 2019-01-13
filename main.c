//
//  main.c
//  LinuxShell
//
//  Created by the team on 09/01/2019.
//  Copyright © 2019 Andrei Mazilu, Robert-Valentin Avramescu and Radu Onetiu. All rights reserved.
//

#include "Utils.h"
#include "Base.h"

char** cmdHistory;
int hMax = 64, hCount = 0;

void add_to_history(char* text) {
    int i;
    for(i = hMax - 1; i > 0; --i) {
        strcpy(cmdHistory[i], cmdHistory[i-1]);
    }
    
    strcpy(cmdHistory[0], text);
    
    if(hCount < 64) hCount++;
}

int function_history(char** args) {
    int i;
    for(i = 0; i < hCount; ++i)
        printf("%s \n", cmdHistory[i]);
    
    return 1;
}

///////Listele de functii
char *functions_list[] = {
    //Base
    "exit", "close", "quit",
    //Andrei
    "cd", "ls", "pwd", "history", "exec",
    //Robert
    "time", "date", "sysinfo", "clear", "find",
    //Radu
    "cp", "mkdir", "rm", "shutdown", "reboot"
};

int (*functions_pointer[]) (char **) = {
    &function_quit, &function_quit, &function_quit,
    &function_cd, &function_ls, &function_pwd, &function_history, &function_exec,
    &function_time, &function_date, &function_sysinfo, &function_clear, &function_find,
    &function_cp, &function_mkdir, &function_rm, &function_shutdown, &function_reboot
};
/////

int parse(char** args) {
    //Pentru o comanda goala, adica args gol
    if (args[0] == NULL) {
        return 1;
    }
    
    int i, numFunctions;
    numFunctions = sizeof(functions_list) / sizeof(functions_list[0]);
    
    for (i = 0; i < numFunctions; i++) {
        if (strcmp(args[0], functions_list[i]) == 0) {
            return (*functions_pointer[i])(args);
        }
    }
    
    //Daca nu gaseste nicio comanda disponibila, continua loopul
    printf("Unknown command...\n");
    return 1;
}

int main(int argc, char** argv) {
    char *line;
    char **argarray;
    int loop = 1;
    
    cmdHistory = malloc(hMax * sizeof(char*));
    int i; for(i = 0; i < hMax; ++i) cmdHistory[i] = malloc(512 * sizeof(char));
    
    while(loop) {
        printf("LinuxShell > ");
        
        line = read_line(stdin);
        argarray = split_line(line);
        
        add_to_history(line);
        
        loop = parse(argarray);
        
        free(line);
        free(argarray);
    }
    
    return EXIT_SUCCESS;
}
