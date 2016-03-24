/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"
#include "JoystickManager.h"
#include "joystickManager.h"
#include "macros.h"

RModes Robot::s_mode = RModes::DISABLED;

Robot::Robot():
    IterativeRobot(),
    m_joysticks(),
    m_hardware_disabled(false),
    m_joystick_disabled(false),
    m_autonomo_disabled(false)
{
    this->m_hw_man = new HardwareManager(m_joysticks);
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
    // The driver sticks
    m_joysticks.push_back(new joystick(0,1,8,this->m_hw_man));
    m_joysticks.push_back(new joystick(1,1,8,this->m_hw_man));
    // The button box
    m_joysticks.push_back(new joystick(2,13,1,this->m_hw_man));

#ifndef ENABLE_JOYSTICK_FAKING
    log_warn("Joystick faking has been disabled!\n \
            If you feel that this is incorrect, please talk to a programmer.");
#endif

    // Just in case ;)
    try{
        for(auto& j : m_joysticks){
            if(j->Init()){
                m_joystick_disabled = true;
                break;
            }
        }
    }catch(...){
        log_err("Initialization of one of the joysticks failed. Disabling joysticks.");
        m_joystick_disabled = true;
    }

    this->m_hw_man->setJoystickVector(m_joysticks);

    m_hardware_disabled = this->m_hw_man->Init();

    // TODO: Change this hardcoded filename
    //   Create some way to let the driver choose the auto mode they want (Maybe using the button box)
    //this->m_auto_man->setFilename("auto_1.joy");
    m_autonomo_disabled = this->m_auto_man->Init();

    log_test("Current Manager Status:");
    log_test("(int)m_hardware_disabled=%d",(int)m_hardware_disabled);
    log_test("(int)m_joystick_disabled=%d",(int)m_joystick_disabled);
    log_test("(int)m_autonomo_disabled=%d",(int)m_autonomo_disabled);

    return;
}

void Robot::AutonomousInit(){
    Robot::s_mode = RModes::AUTO;

    if(!this->m_hardware_disabled)
        this->m_hw_man->init_suck();
    m_autonomo_disabled = this->m_auto_man->Init();
}

void Robot::TeleopInit(){
    Robot::s_mode = RModes::TELEOP;

    /*
    if(!this->m_hardware_disabled)
        this->m_hw_man->init_suck();
        */
}

void Robot::TestInit(){
    Robot::s_mode = RModes::TEST;

    for(int j=0; j<3; j++){
        for(int a=0; a<m_joysticks[j]->getAAmt(); a++){
            printf("Joystick(%d) - Axis(%d)",j,a);
            printf("-%f\n",m_joysticks[j]->GetAxis(a));
        }
        for(int b=0; b<m_joysticks[j]->getBAmt(); b++)
            log_test("Joystick(%d) - Button(%d)-%d",j,b,m_joysticks[j]->GetButton(b));
    }
}

void Robot::DisabledInit(){
    Robot::s_mode = RModes::DISABLED;
}

void Robot::AutonomousPeriodic(){
    if(!this->m_hardware_disabled)
        this->m_hw_man->uninit_suck();

    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_jman->Update();

    if(!this->m_autonomo_disabled)
        this->m_autonomo_disabled = DISABLE_MANAGER_ON_FAILURE && (this->m_auto_man->Update()==1); // Update will always return 1 upon failure, 2 on not implemented, and 0 upon success
    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();

    if(!this->m_autonomo_disabled && this->m_auto_man->IsFinished())
        this->m_auto_man->End();
}

void Robot::TeleopPeriodic(){
    SmartDashboard::PutNumber("Distance",m_hw_man->getDistanceSensorValue());
    SmartDashboard::PutBoolean("Hardware Disabled",this->m_hardware_disabled);
    SmartDashboard::PutBoolean("Joystick Disabled",this->m_joystick_disabled);
    SmartDashboard::PutBoolean("Autonomous Disabled",this->m_autonomo_disabled);

    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_jman->Update();
}

void Robot::TestPeriodic(){
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllServos()["TESTSERVO"]->SetAngle(0);

    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_jman->Update();
}

void Robot::DisabledPeriodic(){
    // TODO: Add something here to hold the robot in place until we can get it down.
    if(!this->m_hardware_disabled && this->m_hw_man->hasWinchBeenActivated())
        log_warn("WARNING! NOT IMPLEMENTED YET!\nNote to Tyler: Remember to ask Rick if we need to do something here.");

    if(!this->m_joystick_disabled)
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

