/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"
#include "joystickManager.h"
#include "macros.h"

RModes Robot::s_mode = RModes::DISABLED;

Robot::Robot():
    IterativeRobot(),
    m_hardware_disabled(false),
    m_joystick_disabled(false),
    m_autonomo_disabled(false)
{
    this->m_hw_man = new HardwareManager();
    this->m_auto_man = new AutonomousManager(m_hw_man);
    this->m_jman = new joystickManager(m_hw_man,this);
}

Robot::~Robot(){
    delete this->m_hw_man;
    delete this->m_auto_man;
    delete this->m_jman;
}

void Robot::RobotInit(){
    log_info("Registering joystick objects.");

#ifndef ENABLE_JOYSTICK_FAKING
    log_warn("Joystick faking has been disabled!\n \
            If you feel that this is incorrect, please talk to a programmer.");
#endif

    m_hardware_disabled = this->m_hw_man->Init();
    this->m_jman->Init();

    log_test("Current Manager Status:");
    log_test("(int)m_hardware_disabled=%d",(int)m_hardware_disabled);
    log_test("(int)m_joystick_disabled=%d",(int)m_joystick_disabled);
    log_test("(int)m_autonomo_disabled=%d",(int)m_autonomo_disabled);

    // Because fuck it
    m_hw_man->getDrive()->SetSafetyEnabled(false);

    return;
}

void Robot::AutonomousInit(){
    Robot::s_mode = RModes::AUTO;

    m_autonomo_disabled = this->m_auto_man->Init();
    if(m_autonomo_disabled)
        log_warn("Autonomous got disabled! D:");
    m_jman->checkAutoButtons();
    log_test("Current Auto mode = %d",m_auto_man->getMode());
    SmartDashboard::PutNumber("Autonomous Mode",m_auto_man->getMode());
}

void Robot::TeleopInit(){
    Robot::s_mode = RModes::TELEOP;

    if(m_hw_man == NULL){
        log_warn("OH GOD! HardwareManager is NULL! D:");
        m_hardware_disabled = true;
    }

    m_jman->checkSanity();
}

void Robot::TestInit(){
    Robot::s_mode = RModes::TEST;
}

void Robot::DisabledInit(){
    Robot::s_mode = RModes::DISABLED;
}

void Robot::AutonomousPeriodic(){
    if(!this->m_autonomo_disabled)
        this->m_autonomo_disabled = DISABLE_MANAGER_ON_FAILURE && (this->m_auto_man->Update()==1); // Update will always return 1 upon failure, 2 on not implemented, and 0 upon success
    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
}

void Robot::TeleopPeriodic(){
    SmartDashboard::PutNumber("Distance",m_hw_man->getDistanceSensorValue());
    SmartDashboard::PutBoolean("Hardware Disabled",this->m_hardware_disabled);
    SmartDashboard::PutBoolean("Joystick Disabled",this->m_joystick_disabled);
    SmartDashboard::PutBoolean("Autonomous Disabled",this->m_autonomo_disabled);

    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
    this->m_jman->Update();
    printf("");
}

void Robot::TestPeriodic(){
    std::string str = "buttonBox";
    log_test("Calling GetButton");
    log_test("BAmt()=%d",m_jman->getJoystick(str)->getBAmt());
    m_jman->getJoystick(str)->GetButton(1);
}

void Robot::DisabledPeriodic(){
    // TODO: Add something here to hold the robot in place until we can get it down.
    if(!this->m_hardware_disabled && this->m_hw_man->hasWinchBeenActivated())
        log_warn("WARNING! NOT IMPLEMENTED YET!\nNote to Tyler: Remember to ask Rick if we need to do something here.");

    this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_jman->Update();
}

void Robot::End(){
    if(this->m_hw_man->End()) log_err("A problem occurred during m_hw_man::End()!");
    if(this->m_auto_man->End()) log_err("A problem occurred during m_auto_man::End()!");
    if(this->m_jman->End()) log_err("A problem occurred during m_jman::End()!");
}

bool Robot::IsFinished(){
    return this->m_hw_man->IsFinished() && this->m_auto_man->IsFinished() && this->m_jman->IsFinished();
}

START_ROBOT_CLASS(Robot);

