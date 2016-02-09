/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"

Robot::Robot():
    IterativeRobot()
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
    this->m_hw_man->Init();
    this->m_auto_man->Init();
}
void Robot::AutonomousInit(){
    this->m_auto_man->Init();
}
void Robot::TeleopInit(){

}
void Robot::TestInit(){

}
void Robot::DisabledInit(){

}

void Robot::AutonomousPeriodic(){
    this->m_joy_man->Periodic();
    this->m_auto_man->Update();
    this->m_hw_man->Update();
}
void Robot::TeleopPeriodic(){
    this->m_joy_man->Periodic();
    this->m_hw_man->Update();
}
void Robot::TestPeriodic(){

}
void Robot::DisabledPeriodic(){

}

START_ROBOT_CLASS(Robot);
