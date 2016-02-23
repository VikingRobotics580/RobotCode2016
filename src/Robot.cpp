/*
 * Robot Vikings
 * Robot.cpp
 * 12/6/15
 */

#include "WPILib.h"
#include "Robot.h"
#include "JoystickManager.h"
#include "macros.h"

Robot::Robot():
    IterativeRobot(),
    m_joysticks(),
    m_hardware_disabled(false),
    m_joystick_disabled(false),
    m_autonomo_disabled(false)
{
    //Joystick* j = new Joystick(0);
    //this->m_joy_man = new JoystickManager(j);
    this->m_joy_man = new JoystickManagerManager();
    this->m_hw_man = new HardwareManager(m_joysticks);
    this->m_auto_man = new AutonomousManager(m_joy_man);
}

Robot::~Robot(){
    delete this->m_hw_man;
    delete this->m_joy_man;
    delete this->m_auto_man;
}

void Robot::RobotInit(){
    log_info("Registering JoystickManagers.");
    // HOLY SHIT
    m_joystick_disabled = this->m_joy_man->registerJM(new JoystickManager(new Joystick(0)));
    m_joystick_disabled = this->m_joy_man->registerJM(new JoystickManager(new Joystick(1)));
    m_joystick_disabled = this->m_joy_man->registerJM(new JoystickManager(new Joystick(2)));

    m_joystick_disabled = this->m_joy_man->Init();


    m_hardware_disabled = this->m_hw_man->Init();


    log_info("Registering joystick objects.");
    // The driver sticks
    m_joysticks.push_back(new joystick(0,1,8,this->m_hw_man));
    m_joysticks.push_back(new joystick(1,1,8,this->m_hw_man));
    // The button box
    m_joysticks.push_back(new joystick(2,13,1,this->m_hw_man));

    // Just in case ;)
    try{
        for(auto& j : m_joysticks){
            if(j->Init()){
                m_joystick_disabled = true;
                break;
            }
        }
    }catch(...){
        m_joystick_disabled = true;
    }

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
    if(!this->m_hardware_disabled)
        this->m_hw_man->init_suck();
    m_autonomo_disabled = this->m_auto_man->Init();
}

void Robot::TeleopInit(){
    /*
    if(!this->m_hardware_disabled)
        this->m_hw_man->init_suck();
        */
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
    if(!this->m_hardware_disabled)
        this->m_hw_man->uninit_suck();
    // If anything is disabled, don't use it
    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_joy_man->Update();
    if(!this->m_autonomo_disabled)
        this->m_autonomo_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_auto_man->Update();
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

    /*
    if(!this->m_hardware_disabled)
        this->m_hw_man->uninit_suck();
        */
    if(!this->m_joystick_disabled)
        this->m_joystick_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_joy_man->Update();
    if(!this->m_hardware_disabled)
        this->m_hardware_disabled = DISABLE_MANAGER_ON_FAILURE && this->m_hw_man->Update();
}

void Robot::TestPeriodic(){
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllServos()["TESTSERVO"]->SetAngle(0);
    /*
    if(!this->m_hardware_disabled)
        this->m_hw_man->getAllTalons()["TESTTALON"]->Set(1);
        */
}

void Robot::DisabledPeriodic(){
    // TODO: Add something here to hold the robot in place until we can get it down.
    if(!this->m_hardware_disabled && this->m_hw_man->hasWinchBeenActivated())
        log_warn("WARNING! NOT IMPLEMENTED YET!");
}

void Robot::End(){
    if(this->m_hw_man->End()) log_err("A problem occurred during m_hw_man::End()!");
    if(this->m_auto_man->End()) log_err("A problem occurred during m_auto_man::End()!");
    if(this->m_joy_man->End()) log_err("A problem occurred during m_joy_man::End()!");
}

bool Robot::IsFinished(){
    return this->m_hw_man->IsFinished() && this->m_auto_man->IsFinished() && this->m_joy_man->IsFinished();
}

START_ROBOT_CLASS(Robot);

