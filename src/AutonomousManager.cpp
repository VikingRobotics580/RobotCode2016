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

AutonomousManager::AutonomousManager(HardwareManager* hwman):
    BaseManager(),
    m_useHardcodedAuto(false),
    m_finished(false),
    m_mode(0),
    m_mode_start(0)
{
    this->m_hw_man = hwman;
}

AutonomousManager::~AutonomousManager(){
}

int AutonomousManager::Init(){
    log_info("AutonomousManager::Init()");
#ifdef USE_EXPERIMENTAL_AUTO_METHOD
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
#else
    log_info("USE_EXPERIMENTAL_AUTO_METHOD is not defined");
    this->m_useHardcodedAuto = true;
#endif

    this->m_mode_start = m_hw_man->getCurrentTime();
    return 0;
}

int AutonomousManager::Update(){
    return this->mode();
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
    switch(this->m_mode){
        case 0:
            return this->mode0();
        case 1:
            return this->mode1();
        case 2:
            return this->mode2();
        case 3:
            return this->mode3();
        case 4:
            return this->mode4();
        case 5:
            return this->mode5();
        case 6:
            return this->mode6();
        case 7:
            return this->mode7();
        default:
            log_err("For some reason m_mode is some value other than the allowed value. How that is possible is beyond me. The value is %d. Please tell a programmer and promptly panic whenever it is most convenient for you.",m_mode);
            return 1;
    }
}

// mode0 should be left blank, as a way to do nothing
int AutonomousManager::mode0(){
    return 0;
}

int AutonomousManager::mode1(){
    if(m_hw_man->hasPassed(m_mode_start,3)){
        m_hw_man->move(0,0);
    }else{
        m_hw_man->move(-1,1);
    }
    return 0;
}

// Shoot from straight on
int AutonomousManager::mode2(){
    if(m_hw_man->hasPassed(m_mode_start,5)){
        m_hw_man->launch();
    }else if(m_hw_man->hasPassed(m_mode_start,4)){
        m_hw_man->init_launch();
    }else{
        // mode1 does exactly what we want to do 3 seconds and earlier, so we just call it rather than repeat code
        return this->mode1();
    }
    return 0;
}

// Shoot from the left side of the goal (turn to the right to angle ourselves correctly)
int AutonomousManager::mode3(){
    if(m_hw_man->hasPassed(m_mode_start,7)){
        m_hw_man->launch();
    }else if(m_hw_man->hasPassed(m_mode_start,6)){
        m_hw_man->init_launch();
        m_hw_man->move(0,0);
    }else if(m_hw_man->hasPassed(m_mode_start,4)){
        m_hw_man->move(0.5,0);
    }else{
        // mode1 does exactly what we want to do 3 seconds and earlier, so we just call it rather than repeat code
        return this->mode1();
    }
    return 0;
}

// Shoot from the right side of the goal (turn to the left to angle ourselves correctly)
int AutonomousManager::mode4(){
    if(m_hw_man->hasPassed(m_mode_start,7)){
        m_hw_man->launch();
    }else if(m_hw_man->hasPassed(m_mode_start,6)){
        m_hw_man->init_launch();
        m_hw_man->move(0,0);
    }else if(m_hw_man->hasPassed(m_mode_start,4)){
        m_hw_man->move(0,0.5);
    }else{
        // mode1 does exactly what we want to do 3 seconds and earlier, so we just call it rather than repeat code
        return this->mode1();
    }
    return 0;
}

int AutonomousManager::mode5(){
    return 2;
}

int AutonomousManager::mode6(){
    return 2;
}

int AutonomousManager::mode7(){
    return 2;
}

