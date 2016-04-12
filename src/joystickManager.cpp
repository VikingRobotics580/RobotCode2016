
#include "joystickManager.h"
#include "Robot.h"
#include "buttons.h"

joystickManager::joystickManager(HardwareManager* hw,Robot* robot):
    BaseManager(),
    m_joysticks()
{
    this->m_hardware_manager = hw;
    this->m_robot = robot;
    // Register all 3 joysticks we will be using (the ID's are kind of arbitrary, but necessary at the same time)
    m_joysticks["leftHand"] = new joystick(0,1,5,hw);
    m_joysticks["rightHand"] = new joystick(1,1,5,hw);
    m_joysticks["buttonBox"] = new joystick(2,13,1,hw);
}

joystickManager::~joystickManager(){
    delete m_joysticks["leftHand"];
    delete m_joysticks["rightHand"];
    delete m_joysticks["buttonBox"];
}

int joystickManager::Init(){
    int ret = 0;
    // Initialize each joystick we have registered
    for(auto& set : this->m_joysticks){
        // 1 will be returned if any of the Init() calls return 1 themselves
        ret |= set.second->Init();
    }
    return ret;
}

int joystickManager::Update(){
    // Get the current Robot mode, so that we can call the appropriate check*Buttons method
    RModes mode = Robot::s_mode;
    int ret = 0;
    try{
        switch(mode){
            case RModes::TELEOP:
                // Unlike the other modes, here we check for joystick input and move the wheels
                ret |= m_hardware_manager->move(m_joysticks["leftHand"]->GetAxis(1),
                        -m_joysticks["rightHand"]->GetAxis(1));
                // TODO: Remove this print statement when we have access to the robot. It may no longer be needed
                printf(" "); 
                return ret | this->checkTeleopButtons();
            case RModes::AUTO:
                return this->checkAutoButtons();
            // Check for the other modes regardless of whether or not we do anything in them
            case RModes::TEST:
                return this->checkTestButtons();
            case RModes::DISABLED:
                return this->checkDisabledButtons();
            default:
                // This should never happen. But just in case.
                log_err("Unknown mode %d. Please contact a programmer.",mode);
                return 1;
        }
    }catch(...){
        // Catch all.
        return 1;
    }
}

int joystickManager::End(){
    // Nothing to clean up
    return 0;
}

bool joystickManager::IsFinished(){
    // We are never finished. We will work tirelessly until the day we die
    return false;
}

int joystickManager::checkTeleopButtons(){
    int ret = 0;

    // ALL THE STUFF GOES HERE ! :D

    // Initialize launcher
    if(m_joysticks["buttonBox"]->GetButton(LAUNCH_INIT_BUTTON)){
        ret |= m_hardware_manager->init_launch();
    }

    // Launch, release or reset
    // Order is important here, because launch takes precedence
    if(m_joysticks["buttonBox"]->GetButton(LAUNCH_BUTTON)){
        ret |= m_hardware_manager->launch();
    }else if(m_joysticks["buttonBox"]->GetButton(RELEASE_BUTTON)){
        ret |= m_hardware_manager->release();
    }else if(!m_joysticks["buttonBox"]->GetButton(LAUNCH_INIT_BUTTON) // We check SUCK here as well, because SUCK utilizes the launch wheels. and we don't want them shutting off before SUCK is done
            && !m_joysticks["buttonBox"]->GetButton(SUCK_BUTTON)){ // Of course, this creates the side effect that launch-init must be off before those wheels will shut off themselves
        ret |= m_hardware_manager->reset_launch();
    }

    // Do raise stuff
    if(m_joysticks["buttonBox"]->GetButton(RAISE_BUTTON)){
        ret |= m_hardware_manager->raise();
    }else if(m_joysticks["buttonBox"]->GetButton(LOWER_BUTTON)){
        ret |= m_hardware_manager->lower();
    }else{
        ret |= m_hardware_manager->stop_raise();
    }

    // Do Extend stuff
    if(m_joysticks["buttonBox"]->GetButton(EXTEND_BUTTON)){
        ret |= m_hardware_manager->extend();
    }else if(m_joysticks["buttonBox"]->GetButton(RETRACT_BUTTON)){
        ret |= m_hardware_manager->retract();
    }else{
        ret |= m_hardware_manager->stopExtRet();
    }

    // Do winch stuff
    if(m_joysticks["buttonBox"]->GetButton(WINCH_BUTTON)){
        ret |= m_hardware_manager->init_climb();
    }
    // Don't need to check for if it isn't being pressed, because it is a one-hit wonder. It can never reset


    // Do suck stuff
    if(m_joysticks["buttonBox"]->GetButton(SUCK_BUTTON)){
        ret |= m_hardware_manager->suck();
    }else if(!m_joysticks["buttonBox"]->GetButton(RELEASE_BUTTON)){
        ret |= m_hardware_manager->stop_suck();
    }

    // Finally, if for some bizarre reason any of these return 1, return 1
    return ret;
}

int joystickManager::checkTestButtons(){
    // Nothing to check for in Test mode
    return 0;
}

int joystickManager::checkAutoButtons(){
    int auto_mode = 0;

    // Autonomous mode is decided by a 3-bit binary number, represented by 3 switches on the button-box
    // The following code converts [B1,B2,B3] into 0's and 1's
    // Also, we check for AUTO_SWITCH_3 first because it is supposed to be the last digit
    // 011
    // ^- This is AUTO_SWITCH_3
    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_3);
    auto_mode <<= 1;
    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_2);
    auto_mode <<= 1;
    auto_mode |= m_joysticks["buttonBox"]->GetButton(AUTO_SWITCH_1);

    // Set the current autonomous manager's autonomous mode to auto mode (only if it isn't already auto_mode, of course)
    if(this->m_robot->getAutoMan()->getMode() != auto_mode)
        this->m_robot->getAutoMan()->setMode(auto_mode);

    return 0;
}

int joystickManager::checkDisabledButtons(){
    return 0;
}

// Oh please, I lost my sanity when writing this code during build season long before this method was ever conceived
int joystickManager::checkSanity(){
    for(auto& set : m_joysticks){
        // Check each joystick to ensure it isn't NULL, and have them check their own sanity as well.
        if(set.second == NULL) return 1;
        if(!set.second->checkSanity()) return 1;
    }
    return 0;
}

