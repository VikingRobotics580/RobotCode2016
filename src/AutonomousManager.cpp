/*
 * AutonomousManager.cpp
 *
 *  Created on: Dec 14, 2015
 *      Author: tyler
 */

#include <stdio.h>
#include <iostream>
#include <istream>
#include <fstream>
#include "AutonomousManager.h"

//AutonomousManager::AUTO_MAGIC_NUMBER::0x4155544f;

AutonomousManager::AutonomousManager() :
    BaseManager(),
    m_filename(""),
    m_instruction_amt(0)
{
    this->m_instructions=NULL;
    this->m_auto_raw_data=NULL;
}

AutonomousManager::AutonomousManager(std::string& fname) :
    BaseManager(),
    m_filename(fname),
    m_instruction_amt(0)
{
    this->m_instructions=NULL;
    this->m_auto_raw_data=NULL;
}

AutonomousManager::~AutonomousManager(){
}

int AutonomousManager::Init(){
    return 1;
}

int AutonomousManager::Update(){
    return 1;
}

bool AutonomousManager::IsFinished(){
    return true;
}

int AutonomousManager::End(){
    return 1;
}

/*
void AutonomousManager::Interrupted(){
}
*/

int AutonomousManager::mode(){
    return 1;
}

int AutonomousManager::readAutoSyntax(){
    std::ifstream f(this->m_filename,std::ios::in|std::ios::binary);
    std::ifstream::pos_type size;

    if(f.is_open()){
        f.seekg(0,std::ios::end);
        size = f.tellg();
        f.seekg(0,std::ios::beg);
        if(size < 11) return 1; // Autonomous file must be at least 11 bytes long
        this->m_auto_raw_data = new char[size];

        if(!f.read(this->m_auto_raw_data,size)) return 1;
    }else{
        return 1;
    }

    // MAGIC NUMBER! :D
    int magic = (this->m_auto_raw_data[0]<<24)|(this->m_auto_raw_data[1]<<16)|(this->m_auto_raw_data[2]<<8)|(this->m_auto_raw_data[3]);
    if(magic != AutonomousManager::AUTO_MAGIC_NUMBER) return 1;

    int i=4;
    while(i < size){
        char byte = this->m_auto_raw_data[i];
        // HEADER SECTION
        if(byte == 'H'){
// Suppress warnings on ++i operation (because it's bullshit)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"
            this->m_instruction_amt = (this->m_auto_raw_data[++i] << 8)|(this->m_auto_raw_data[++i]);
#pragma GCC diagnostic pop
            while(++i != 'E'); // Are there any other bytes before the end? Who cares, just go until the end of the section has been reached.
        // INSTRUCTION SET SECTION
        }else if(byte == 'T'){
            int n=0;
            // Create a new instruction array
            this->m_instructions = new instruction[this->m_instruction_amt];
            while(n!=this->m_instruction_amt){
                byte = this->m_auto_raw_data[++i];
                // INSTRUCTION SECTION
                if(byte == 'I'){
                    // An array of instruction_structs 
                    instruction* instr = new instruction();
                    int e = i;
                    while(this->m_auto_raw_data[++e] != 'E'); // Get number of commands
                    instr->commands = new command*[e];
                    instr->num_commands = e;
                    // While we aren't yet at the last instruction
                    while(i != e){
                        command* c = new command();

                        int s = i;
                        while(this->m_auto_raw_data[s++] != ','); // Get size of command

                        c->com_length = (s-i);
                        // Read the command into a char array
                        char* com = new char[s-i];
                        while(i<s)
// Suppress warnings on ++i operation (because it's bullshit)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wsequence-point"
                            com[s-i] = this->m_auto_raw_data[++i]; // Continue getting bytes until the end of the command.
#pragma GCC diagnostic pop

                        c->com = com;
                        instr->commands[e-i] = c;
                    }
                    n++;
                }else if(byte == 'E'){
                    // Premature end
                    // This should never happen unless the file is corrupted.
#ifdef AUTO_DRIVE_FILES_TREAT_WARNINGS_AS_ERRORS
                    printf("ERROR! End of Instruction Section found before the number of instructions listed! File may be corrupted.");
                    //printf("Instructions read: %d",n);
                    return 1;
#else
                    printf("WARNING! End of Instruction Section found before the number of instructions listed! File may be corrupted.");
                    printf("Instructions read: %d",n);
                    break;
#endif
                }
            }
        }else if(byte == 0){
            // Do nothing afterthe end of the data has been reached
            break;
        }
    }

    printf("Read %d bytes of %d bytes.",i,(int)size);

    return 0;
}


