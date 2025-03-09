#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "header.h"

void clear_screen(){

    system("clear");
}

void change_directory(char *directory){
    char cwd[1024];

    //if there is no directory inputted it outputs the current working directory instead
    if (directory == NULL){
        if(getcwd(cwd, sizeof(cwd))){
            printf("%s\n", cwd);
        }
        
        else{
            perror("error");
        }
    }

    // if the directory doesnt exist it prints error
    if(chdir(directory) != 0){
        perror("error");
    }

    // otherwise it changes the directory
    else{
        setenv("PWD", cwd, 1);
    }
}

void list_directory(char *directory){

    //making a string to pass to system
    char list[50] = "ls -al ";
    
    // if there is no second input for the directory then it stores the current working directory in the string
    if (directory == NULL){
        strcat(list, ".");
 
    }

    // otherwise it stores the directory name into the string
    else{
        strcat(list, directory);
    }

    //uses the concat string as the system call
    system(list);

}

void echo_input(char ** args){

    //skips the first arg as the first arg is echo
    char **arg = args + 1;

    //prints out the rest of the args provided
    while (*arg){
        printf("%s ", *arg);
        arg++;
    }

    printf("\n");
}


void pause_shell(){

    }


void enviornment(){

    //prints out the enviornment variables of the current working directory
    extern char **environ;
    int i;
    for (i = 0; environ[i] != NULL; i++)
    printf("%s\n",environ[i]);

}

void get_help(){
    // uses the more system function to access the readme which contains a smiple manual of the functions
    system("more ../manual/README.md");
}
