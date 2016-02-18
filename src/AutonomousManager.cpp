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
#include "HardwareManager.h"
#include "macros.h"

//AutonomousManager::AUTO_MAGIC_NUMBER::0x4155544f;

AutonomousManager::AutonomousManager(JoystickManager* jman) :
    BaseManager(),
    m_filename(""),
    m_current_instruction(0),
    m_instruction_amt(0),
    m_useHardcodedAuto(false),
    m_finished(false)
{
    this->m_instructions=NULL;
    this->m_auto_raw_data=NULL;
    this->m_jman = jman;
    this->m_timer = new Timer();
}

AutonomousManager::AutonomousManager(std::string& fname, JoystickManager* jman) :
    BaseManager(),
    m_filename(fname),
    m_current_instruction(0),
    m_instruction_amt(0),
    m_useHardcodedAuto(false),
    m_finished(false)
{
    this->m_instructions=NULL;
    this->m_auto_raw_data=NULL;
    this->m_jman = jman;
    this->m_timer = new Timer();
}

AutonomousManager::~AutonomousManager(){
    delete[] this->m_auto_raw_data;
    delete[] this->m_instructions;
}

int AutonomousManager::Init(){
    log_info("AutonomousManager::Init()");
    this->m_current_instruction = 0;
    // Don't initialize if the filename hasn't been set yet
    // Print an error as well
    if(this->m_filename == ""){
        log_err("Filename not set.");
        return 1; 
    }

    // If we failed to read the dynamic Autonomous file, then fall back to a hardcoded method
    if(this->parseAutoSyntax()){
        log_err("Failed to parse dynamic Autonomous code.");
        log_info("Falling back to hardcoded Autonomous code.");
        this->m_useHardcodedAuto = true;
    }
    m_timer->Start();
    return 0;
}

int AutonomousManager::Update(){
    if(!this->m_useHardcodedAuto){
        log_info("Executing instruction %d",m_current_instruction);
        if(this->executeInstruction(this->m_instructions[m_current_instruction]))
            return 1;
        if(this->m_current_instruction < this->m_instruction_amt)
            this->m_current_instruction++;
        else
            this->m_finished = true;
        return 0;
    }else{
        return this->mode();
    }
}

bool AutonomousManager::IsFinished(){
    return this->m_finished;
}

int AutonomousManager::End(){
    return 1;
}

/*
void AutonomousManager::Interrupted(){
}
*/

int AutonomousManager::mode(){
    if(this->HasTimePassed(10)){
        this->m_jman->FakePressButton(HardwareManager::HW_LAUNCH_BUTTON_IDX,1);
        log_test("Beep Boop launching.")
    }else
        this->m_jman->FakeJoystickX(1);
    return 0;
}

int AutonomousManager::executeInstruction(instruction* instr){
    int com_count = instr->num_commands;
    if(com_count == 0) return 0;
    command* com = instr->commands[0];
    int type = (*(com->com))&AutonomousManager::AUTO_TYPE_MASK;

    if(type == AutonomousManager::AUTO_AXIS_ID){
        // Axis
        if(com_count < 3) return 1; // INSTR:VAL,DURATION
        command* val_param = instr->commands[1];
        command* dur_param = instr->commands[2];
        float val = ((int)val_param)/1000.0F;
        float dur = ((int)dur_param)/1000.0F;
        int id = (*(com->com))&AutonomousManager::AUTO_ID_MASK;
        m_jman->FakeAxisInput(id,val,dur);
    }else if(type == AutonomousManager::AUTO_BUTT_ID){
        // Button
        if(com_count < 2) return 1; // INSTR:DURATION
        command* dur_param = instr->commands[1];
        // Convert char to int and then to float
        float dur = ((int)dur_param)/1000.0F;
        int id = (*(com->com))&AutonomousManager::AUTO_ID_MASK;
        m_jman->FakePressButton(id,dur);
    }else if(type == AutonomousManager::AUTO_MOVE_ID){
        // NOTE: NOT IMPLEMENTED
        // Generic movement
        // Maybe not actually do anything with this
    }
    return 1;
}

// Read everything
int AutonomousManager::readFile(){
    log_info("AutonomousManager::readFile()");
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
        log_err("Unable to open file %s",m_filename.c_str());
        return 1;
    }

    this->m_raw_data_size = size;

    return 0;
}

// Simple function to parse AUTO files
// Don't touch it
int AutonomousManager::parseAutoSyntax(){
    log_info("AutonomousManager::parseAutoSyntax()");
    if(this->readFile()){
        log_err("Failed to read file.");
        return 1;
    }
    // MAGIC
    int magic = (this->m_auto_raw_data[0]<<24)|(this->m_auto_raw_data[1]<<16)|(this->m_auto_raw_data[2]<<8)|(this->m_auto_raw_data[3]);
    if(magic != AutonomousManager::AUTO_MAGIC_NUMBER) return 1;

    // I have no idea what the hell any of this means
    int i=4;
    while(i < this->m_raw_data_size){
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
            this->m_instructions = new instruction*[this->m_instruction_amt];
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
                    log_err("End of Instruction Section found before the number of instructions listed! File may be corrupted.");
                    //printf("Instructions read: %d",n);
                    return 1;
#else
                    log_warn("End of Instruction Section found before the number of instructions listed! File may be corrupted.\n    Instructions read: %d",n);
                    break;
#endif
                }
            }
        }else if(byte == 0){
            // Do nothing after the end of the data has been reached
            break;
        }
    }

    log_info("Read %d bytes of %d bytes.",i,(int)m_raw_data_size);

    return 0;
}
// Didn't I say not to touch this method?


