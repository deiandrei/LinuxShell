//
//  Utils.h
//  LinuxShell
//
//  Created by Andrei on 09/01/2019.
//  Copyright © 2019 Andrei. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>

char* read_line(FILE* location) {
    char* line = NULL;
    size_t temp = 0;
    
    getline(&line, &temp, location);
    
    return line;
}

char** split_line(char *line) {
    int maxElements = 32, position = 0;
    
    char** array = malloc(maxElements * sizeof(char*));
    if (!array) {
        fprintf(stderr, "[Error] Argument array alocation\n");
        exit(EXIT_FAILURE);
    }
    
    char* element = strtok(line, " \t\r\n\a");
    while (element != NULL) {
        array[position] = element;
        position++;
        
        //Daca am trecut de limita de elemente, marim limita cu 32 si realocam spatiul
        if (position >= maxElements) {
            maxElements += 32;
            array = realloc(array, maxElements * sizeof(char*));
            
            if (!array) {
                fprintf(stderr, "[Error] Argument array realocation\n");
                exit(EXIT_FAILURE);
            }
        }
        
        //Continuam cu tokul
        element = strtok(NULL, " \t\r\n\a");
    }
    
    //Punem pe ultima pozitie un terminator
    array[position] = NULL;
    
    return array;
}

#endif /* Utils_h */
