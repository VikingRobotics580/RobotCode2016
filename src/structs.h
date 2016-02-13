
#ifndef _STRUCTS_H_
#define _STRUCTS_H_

typedef struct command_struct {
    ~command_struct(){ delete[] com; };
    char* com;
    int com_length;
} command;

typedef struct instruction_struct {
    ~instruction_struct(){
        for(int i=0; i<num_commands;i++) delete commands[i];
        delete[] commands;
    };
    int num_commands;
    command** commands;
} instruction;

template<typename T>
struct proxy {
    proxy_struct(T& d){ data=d; };
    T data;
};

#endif

