//
//  Base.c
//  LinuxShell
//
//  Created by the team on 09/01/2019.
//  Copyright © 2019 Andrei Mazilu, Robert-Valentin Avramescu and Radu Onetiu. All rights reserved.
//

#include "Base.h"

int function_quit(char** args) {
    return 0;
}

/////// Andrei
int function_cd(char** args) {
    if (args[1] == NULL) {
        fprintf(stderr, "[Error] No argument given to \"cd\"\n");
    } else {
        if (chdir(args[1]) != 0) {
            perror("[Error] cd");
        }
    }
    
    return 1;
}

int function_ls(char** args) {
    DIR* p;
    struct dirent *d;
    
    p = opendir("./");
    d = readdir(p);
    while(d) {
        if(strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..")) printf("%s ",d->d_name);
        
        d = readdir(p);
    }
    printf("\n");
    
    return 1;
}

int function_pwd(char** args) {
    char cwd[1024];
    
    getcwd(cwd, sizeof(cwd));
    printf("Current working dir: %s\n", cwd);
    
    return 1;
}

int function_exec(char** args) {
    char command[1024];
    
    int nrcom = num_args(args);
    if(nrcom < 2) return 1;
    
    strcpy(command, args[1]);
    int i; for(i = 2; i < nrcom; ++i) {
        strcat(command, " ");
        strcat(command, args[i]);
    }
    
    system(command);
    
    return 1;
}
///////

/////// Robert
int function_time(char** args) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("Time: %d:%d \n", tm->tm_hour, tm->tm_min);
    return 1;
}

int function_date(char** args) {
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    printf("Date: %d-%d-%d \n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900);
    return 1;
}

int function_sysinfo(char** args) {
    int z;
    struct utsname u_name;
    z = uname(&u_name);
    if(z == -1)
    {
        fprintf(stderr,"%s:uname(2)\n",strerror(errno));
        exit (1);
    }
    
    printf("System infomation: \n");
    printf(" sysname = %s;\n", u_name.sysname);
    printf(" nodename = %s;\n", u_name.nodename);
    printf(" release = %s;\n", u_name.release);
    printf(" version = %s;\n", u_name.version);
    printf(" machine = %s;\n", u_name.machine);
    
    return 1;
}

int function_clear(char** args) {
    printf("\x1b[H\x1b[J");
    return 1;
}

int function_find(char** args) {
    int fd1[2];
    int fd2[2];
    char input_str[100];
    pid_t p;
    if (pipe(fd1)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    if (pipe(fd2)==-1)
    {
        fprintf(stderr, "Pipe Failed" );
        return 1;
    }
    printf("File name \n");
    scanf("%s", input_str);
    p = fork();
    if (p < 0)
    {
        fprintf(stderr, "fork Failed" );
        return 1;
    }
    if(p > 0)
    {
        char answer[5];
        close(fd1[0]);
        write(fd1[1], input_str, strlen(input_str)+1);
        close(fd1[1]);
        wait(NULL);
        close(fd2[1]);
        read(fd2[0], answer, 4);
        printf("Answer is: %s\n", answer);
        close(fd2[0]);
    }
    else
    {
        struct dirent *de;
        char file_name[30];
        char answer[5];
        DIR *dr = opendir(".");
        close(fd1[1]);
        read(fd1[0], file_name, 30);
        strcpy(answer, "no");
        if (dr == NULL)
        {
            printf("Could not open current directory" );
            return 1;
        }
        while ((de = readdir(dr)) != NULL)
        {
            if(strcmp(file_name, de->d_name) == 0)
                strcpy(answer, "yes");
        }
        closedir(dr);
        close(fd1[0]);
        close(fd2[0]);
        write(fd2[1], answer, 4);
        close(fd2[1]);
        exit(0);
    }
    return 1;
}
///////

/////// Radu
int function_cp(char** args) {
    
    char ch, source_file[20], target_file[20];
    FILE *source, *target;
    
    //if(argc != 3) return 0;
    strcpy(source_file, args[1]);
    strcpy(target_file, args[2]);
    
    source = fopen(source_file, "r");
    
    if(source == NULL)
    {
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    
    target = fopen(target_file, "w");
    
    if(target == NULL)
    {
        fclose(source);
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    
    while((ch = fgetc(source)) != EOF)
        fputc(ch, target);
    
    printf("File copied successfully.\n");
    
    fclose(source);
    fclose(target);
    
    return 1;
}

int function_mkdir(char** args) {

  char temp[50];
  strcpy(temp, args[1]);
  if(mkdir(temp, 0777) == -1)
    printf("Error\n");
  else
    printf("Directory created\n");
  return 1;
}

int function_rm(char** args) {
    int delete_status;
    delete_status = unlink(args[1]);
    if(delete_status != 0)
        return errno;
    
    printf("File %s has been deleted succesfully!\n", args[1]);
    
    return 1;
}

int function_shutdown(char** args) {
    sync();
    system("shutdown -P now");
    return 0;
}

int function_reboot(char** args) {
    sync();
    system("reboot");
    return(0);
}
//////
