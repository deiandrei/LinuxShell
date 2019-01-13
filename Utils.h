//
//  Utils.h
//  LinuxShell
//
//  Created by the team on 09/01/2019.
//  Copyright © 2019 Andrei Mazilu, Robert-Valentin Avramescu and Radu Onetiu. All rights reserved.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* read_line(FILE* location);
char** split_line(char *line);
int num_args(char** args);

#endif /* Utils_h */
