
#include "joystickManager.h"
#include "Robot.h"
#include "buttons.h"

joystickManager::joystickManager(HardwareManager* hw):
    BaseManager(),
    m_joysticks()
{
    this->m_hardware_manager = hw;
    m_joysticks["leftHand"] = new joystick(0,1,5,hw);
    m_joysticks["rightHand"] = new joystick(1,1,5,hw);
    m_joysticks["buttonBox"] = new joystick(2,13,1,hw);
}

joystickManager::~joystickManager(){
    /*
    for(auto& joy : this->m_joysticks)
        delete joy;
        */
    delete m_joysticks["leftHand"];
    delete m_joysticks["rightHand"];
    delete m_joysticks["buttonBox"];
}

int joystickManager::Init(){
    int ret = 0;
    for(auto& set : this->m_joysticks)
        ret |= set.second->Init();
    return ret;
}

int joystickManager::Update(){
    RModes mode = Robot::s_mode;
    switch(mode){
        case RModes::TELEOP:
            return m_hardware_manager->move() | this->checkTeleopButtons();
        case RModes::AUTO:
            return this->checkAutoButtons();
        case RModes::TEST:
            return this->checkTestButtons();
        case RModes::DISABLED:
            return this->checkDisabledButtons();
        default:
            log_err("Unknown mode %d. Please contact a programmer.",mode);
            return 1;
    }
}

int joystickManager::End(){
    return 0;
}

bool joystickManager::IsFinished(){
    return false;
}

int joystickManager::checkTeleopButtons(){
    int ret = 0;

    // ALL THE STUFF GOES HERE ! :D

    // Initialize launcher
    if(m_joysticks["buttonBox"]->GetButton(LAUNCH_INIT_BUTTON))
        ret |= m_hardware_manager->init_launch();

    // Launch, release or reset
    // Order is important here, because launch takes precedence
    if(m_joysticks["buttonBox"]->GetButton(LAUNCH_BUTTON))
        ret |= m_hardware_manager->launch();
    else if(m_joysticks["buttonBox"]->GetButton(RELEASE_BUTTON))
        ret |= m_hardware_manager->release();
    else
        ret |= m_hardware_manager->reset_launch();

    // Do raise stuff
    if(m_joysticks["buttonBox"]->GetButton(RAISE_BUTTON))
        ret |= m_hardware_manager->raise();
    else if(m_joysticks["buttonBox"]->GetButton(LOWER_BUTTON))
        ret |= m_hardware_manager->lower();

    // Do Extend stuff
    if(m_joysticks["buttonBox"]->GetButton(EXTEND_BUTTON))
        ret |= m_hardware_manager->extend();
    else if(m_joysticks["buttonBox"]->GetButton(RETRACT_BUTTON))
        ret |= m_hardware_manager->retract();

    // Do winch stuff
    if(m_joysticks["buttonBox"]->GetButton(WINCH_BUTTON))
        ret |= m_hardware_manager->init_climb();

    // Do suck stuff
    if(m_joysticks["buttonBox"]->GetButton(SUCK_BUTTON))
        ret |= m_hardware_manager->suck();
    else
        ret |= m_hardware_manager->stop_suck();


    return ret;
}

int joystickManager::checkTestButtons(){
    return 0;
}

int joystickManager::checkAutoButtons(){
    int auto_mode = 0;

    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_1);
    auto_mode <<= 1;
    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_2);
    auto_mode <<= 1;
    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_3);

    // TODO: Find a way to send this to AutonomousManager

    return 0;
}

int joystickManager::checkDisabledButtons(){
    return 0;
}

