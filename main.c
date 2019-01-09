//
//  main.c
//  LinuxShell
//
//  Created by Andrei on 09/01/2019.
//  Copyright © 2019 Andrei. All rights reserved.
//

#include <stdlib.h>
#include "Utils.h"
#include "Base.h"

///////Listele de functii
char *functions_list[] = {
    "exit", "close", "quit"
};

int (*functions_pointer[]) (char **) = {
    &function_quit, &function_quit, &function_quit
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
    return 1;
}

int main(int argc, char** argv) {
    char *line;
    char **argarray;
    int loop = 1;
    
    while(loop) {
        printf("LinuxShell > ");
        line = read_line(stdin);
        argarray = split_line(line);
        loop = parse(argarray);
        
        free(line);
        free(argarray);
    }
    
    return EXIT_SUCCESS;
}
