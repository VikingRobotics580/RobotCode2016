
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct command_struct {
    char* com;
    int com_length;
} command;

typedef struct instruction_struct {
    int num_commands;
    command** commands;
} instruction;

#endif

