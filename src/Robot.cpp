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
    m_hardware_disabled = this->m_hw_man->Init();
    // TODO: Find out why the bottom of this method causes the code to SEGFAULT
    // TODO: Change this hardcoded filename
    //   Create some way to let the driver choose the auto mode they want (Maybe using the button box)
    return;
    this->m_auto_man->setFilename((std::string&)"auto_1.joy");
    m_autonomo_disabled = this->m_auto_man->Init();
}
void Robot::AutonomousInit(){
    m_autonomo_disabled = this->m_auto_man->Init();
}
void Robot::TeleopInit(){

}
void Robot::TestInit(){
    /*
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllTalons()["TESTSERVO"]->Set(0.5);
        */
}
void Robot::DisabledInit(){

}

void Robot::AutonomousPeriodic(){
    // If anything is disabled, don't use it
    if(!this->m_joystick_disabled)
        this->m_joy_man->Update();
    if(!this->m_autonomo_disabled)
        this->m_auto_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hw_man->Update();
}
void Robot::TeleopPeriodic(){
    if(!this->m_joystick_disabled)
        this->m_joy_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hw_man->Update();
}
void Robot::TestPeriodic(){
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllServos()["TESTSERVO"]->SetAngle(360);
}
void Robot::DisabledPeriodic(){

}

START_ROBOT_CLASS(Robot);

