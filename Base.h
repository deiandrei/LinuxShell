//
//  base.h
//  LinuxShell
//
//  Created by the team on 09/01/2019.
//  Copyright © 2019 Andrei Mazilu, Robert-Valentin Avramescu and Radu Onetiu. All rights reserved.
//

#ifndef Base_h
#define Base_h

#include "Utils.h"
#include <dirent.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <errno.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/reboot.h>

int function_quit(char** args);

// Andrei
int function_cd(char** args);
int function_ls(char** args);
int function_pwd(char** args);
int function_exec(char** args);

// Robert
int function_time(char** args);
int function_date(char** args);
int function_sysinfo(char** args);
int function_clear(char** args);
int function_find(char** args);

// Radu
int function_cp(char** args);
int function_mkdir(char** args);
int function_rm(char** args);
int function_shutdown(char** args);
int function_reboot(char** args);

#endif /* base_h */
