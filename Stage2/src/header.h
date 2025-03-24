/*
name: Krishna Nandipaty

studentnumber: 23437162

I acknowledge the DCU Academic Integrity Policy

*/


#ifndef HEADER_H
#define HEADER_H
#define MAX_BUFFER 1024                        // max line buffer
#define MAX_ARGS   64                          // max # args
#define SEPARATORS " \t\r\n"                     // token separators

// Function prototypes
int  tokeninput(char *buf, char *args[]);
int  process_command(char *args[]);
void clear_screen();
void change_directory(char *directory);
void list_directory(char *directory);
//void pause_shell();
void echo_input(char **args);
void enviornment();
void get_help();
void batchmode(const char *file);
void inputoutput(char *args[]);

#endif