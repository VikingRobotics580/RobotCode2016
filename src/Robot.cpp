/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"

Robot::Robot():
    IterativeRobot(),
    m_hardware_disabled(false),
    m_joystick_disabled(false),
    m_autonomo_disabled(false)
{
    Joystick* j = new Joystick(0);
    this->m_joy_man = new JoystickManager(j);
    this->m_hw_man = new HardwareManager(m_joy_man);
    this->m_auto_man = new AutonomousManager(m_joy_man);
}

Robot::~Robot(){
    delete this->m_hw_man;
    delete this->m_joy_man;
    delete this->m_auto_man;
}

void Robot::RobotInit(){
    if(this->m_hw_man->Init()) m_hardware_disabled=true;
    // TODO: Change this hardcoded filename
    //   Create some way to let the driver choose the auto mode they want (Maybe using the button box)
    this->m_auto_man->setFilename("auto_1.joy");
    //if(this->m_auto_man->Init()) m_autonomo_disabled=true;
}
void Robot::AutonomousInit(){
    if(this->m_auto_man->Init()) m_autonomo_disabled=true;
}
void Robot::TeleopInit(){

}
void Robot::TestInit(){

}
void Robot::DisabledInit(){

}

void Robot::AutonomousPeriodic(){
    // If anything is disabled, don't use it
    if(!this->m_joystick_disabled)
        this->m_joy_man->Periodic();
    if(!this->m_autonomo_disabled)
        this->m_auto_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hw_man->Update();
}
void Robot::TeleopPeriodic(){
    if(!this->m_joystick_disabled)
        this->m_joy_man->Periodic();
    if(!this->m_hardware_disabled)
        this->m_hw_man->Update();
}
void Robot::TestPeriodic(){

}
void Robot::DisabledPeriodic(){

}

START_ROBOT_CLASS(Robot);

