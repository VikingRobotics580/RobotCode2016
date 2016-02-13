/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"
#include "macros.h"

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
    // TODO: Change this hardcoded filename
    //   Create some way to let the driver choose the auto mode they want (Maybe using the button box)
    this->m_auto_man->setFilename("auto_1.joy");
    m_autonomo_disabled = this->m_auto_man->Init();

    log_test("Current Manager Status:");
    log_test("(int)m_hardware_disabled=%d",(int)m_hardware_disabled);
    log_test("(int)m_joystick_disabled=%d",(int)m_joystick_disabled);
    log_test("(int)m_autonomo_disabled=%d",(int)m_autonomo_disabled);

    return;
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
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_joy_man->Update();
    if(!this->m_autonomo_disabled)
        this->m_autonomo_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_auto_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
}
void Robot::TeleopPeriodic(){
    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_joy_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
}
void Robot::TestPeriodic(){
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllServos()["TESTSERVO"]->SetAngle(360);
}
void Robot::DisabledPeriodic(){

}

void Robot::End(){
    if(this->m_hw_man->End()) log_err("A problem occurred during m_hw_man::End()!");
    if(this->m_auto_man->End()) log_err("A problem occurred during m_auto_man::End()!");
    if(this->m_joy_man->End()) log_err("A problem occurred during m_joy_man::End()!");
}

START_ROBOT_CLASS(Robot);

