
/*
name: Krishna Nandipaty

studentnumber: 23437162

I acknowledge the DCU Academic Integrity Policy

*/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include "header.h"
#include <errno.h>
int main(int argc, char **argv)
{
    char buf[MAX_BUFFER];
    char *args[MAX_ARGS];

    // If theres 2 arguments aka a batchfile then it runs batchmode
    if (argc == 2) {
        batchmode(argv[1]);
        return 0;
    } 
    else {

        //else its runs an interactive terminal
        while (!feof(stdin)) {
            // prints the current working directory as the prompt
            if (getcwd(buf, sizeof(buf)) != NULL) {
                printf("%s $ ", buf);
            } else {
                perror("getcwd");
                break;
            }

            // reads 1 line of input
            if (!fgets(buf, MAX_BUFFER, stdin)) {
                // If EOF is reached or error, exit loop
                printf("\n");
                break;
            }

            // turns the inputs into tokens
            int argcount = tokeninput(buf, args);

            // if there is a token then process it
            if (argcount > 0) {
                // if the processcommand returns a 1 it means the users wants to quit the program
                if (process_command(args) == 1) {
                    break;
                }
            }
        }
        return 0;
    }
}


// tokenizes the inputs and returns the number of tokens
int tokeninput(char *buf, char *args[]) {
    char **argpoint = args;

    // first token
    *argpoint++ = strtok(buf, SEPARATORS);

    // tokens after that
    while ((*argpoint++ = strtok(NULL, SEPARATORS)))
        ;

    // counting tokens
    int count = 0;
    while (args[count] != NULL) {
        count++;
    } 
    return count;
}


// processes the commands of through input
int process_command(char *args[]) {

    if (args[0]) {
        // clear screen
        if (!strcmp(args[0], "clr")) {
            clear_screen();  
            return 0;
        }

        // returns 1 which indicates to the main function that it should quit/ break out of the loop
        if (!strcmp(args[0], "quit")) {
            return 1;
        }

        // changes directories
        if(!strcmp(args[0], "cd")){
            change_directory(args[1]);
            return 0;
        }

        // lists the contents of a directory
        if(!strcmp(args[0], "dir")){
            list_directory(args[1]);
            return 0;
        }

        // displays input from user
        if(!strcmp(args[0], "echo")){
            echo_input(args);
            return 0;
        }

        //lists enviornment variables
        if(!strcmp(args[0], "environ")){
            enviornment();
            return 0;
        }

        //prints out user manual from the readme
        if(!strcmp(args[0], "help")){
            get_help();
            return 0;
        }

        //pauses the process until enter
        if(!strcmp(args[0], "pause")){
            //pause_shell();
            return 0;
        }

                    
             //creates a child process
             pid_t pid = fork();

             //if making child process is successful
             if(pid == 0){

                // file pointers
                FILE *in_file = NULL;
                FILE *out_file = NULL;

                // loop through command line arguments
                for (int i = 0; args[i] != NULL; i++){

                    // if there is a "<" symbol in the arguments
                    if (!strcmp(args[i], "<")) {

                        // if there is no file following the < produce error message
                        if (args[i + 1] == NULL){

                            perror("error");
                            exit(EXIT_FAILURE);
                        }

                        // opens the file as read for standard input
                        in_file = freopen(args[i + 1], "r", stdin);
                        if (in_file == NULL){
                            perror("error");
                            exit(EXIT_FAILURE);
                        }

                        //remove the symbol from the list of arguments
                        for(int k = i; args[k+2] != NULL; k++){
                            args[k] = args[k + 2];
                        }

                        args[i] = NULL;
                        continue;
                }

                // if the symbol ">" is present in the arguemnts
                else if (!strcmp(args[i], ">")) {

                    // fail if there is not file present
                    if (args[i + 1] == NULL){

                        perror("error");
                        exit(EXIT_FAILURE);
                    }

                    // opens it as write
                    out_file = freopen(args[i + 1], "w", stdout);
                    if (out_file == NULL){
                        perror("error");
                        exit(EXIT_FAILURE);
                    }

                    else {
                        fprintf(stderr, "stdout successfully redirected to %s\n", args[i + 1]);
                    }

                    // removes it from the list of arguments
                    for(int k = i; args[k+2] != NULL; k++){
                        args[k] = args[k + 2];

                        
                    }

                    args[i] = NULL;
                    continue;
             }

             // if the symbol ">>" is present in the command line
             else if (!strcmp(args[i], ">>")) {

                // produce error if no file is following
                if (args[i + 1] == NULL){

                    perror("error");
                    exit(EXIT_FAILURE);
                }

                // creates the file since it is ">>"
                out_file = freopen(args[i + 1], "a", stdout);
                if (out_file == NULL){
                    perror("error");
                    exit(EXIT_FAILURE);
                }

                // removes the symbols from the list of arguments
                for(int k = i; args[k+2] != NULL; k++){
                    args[k] = args[k + 2];

                    
                }

                args[i] = NULL;
                continue;
         }

        }

        // executes the commands after opening the file 

        if (execvp(args[0], args) == -1) {
            perror("execvp");
            _exit(EXIT_FAILURE);
        }
        setenv("parent", "/customshell", 1);
    }


    // produces an error if forking fails
    else if (pid < 0){  

        perror("error");

    }

}

return 0;
}


void batchmode(const char *file) {

    // opens the file provided
    FILE *batchfile = fopen(file, "r");

    char input[MAX_BUFFER];
    char *args[MAX_ARGS];

    while (fgets(input, MAX_BUFFER, batchfile)) {
        // Remove trailing newline character
        input[strcspn(input, "\n")] = 0; 

        // Skip empty lines

        if (strlen(input) == 0) { 
            continue;
        }

        // tokenizes the input and store it in the args
        int argcount = tokeninput(input, args);

        if (argcount > 0) {
            process_command(args);
        }
    }

    fclose(batchfile);
}



