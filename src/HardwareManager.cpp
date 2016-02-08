
#include "HardwareManager.h"

HardwareManager::HardwareManager(JoystickManager* jman):
    BaseManager(),
    m_finished(false),
    m_talons()
{
    m_drive = NULL;
    m_jman = jman;
}

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    this->addTalon(0,"frontLeft");
    this->addTalon(1,"backLeft");
    this->addTalon(2,"frontRight");
    this->addTalon(3,"backRight");
    m_drive = new RobotDrive(
            this->getTalon("frontLeft"),this->getTalon("backLeft"),
            this->getTalon("frontRight"),this->getTalon("backRight"));

    return 0;
}

int HardwareManager::Update(){
    return this->move();
}

bool HardwareManager::IsFinished(){
    return this->m_finished;
}

int HardwareManager::End(){
    return 0;
}

int HardwareManager::move(){
    this->m_drive->TankDrive(m_jman->GetAxis(1),m_jman->GetAxis(2));
    return 0;
}

int HardwareManager::launch(){
    if(m_jman->Get(HardwareManager::HW_LAUNCH_BUTTON_IDX)){
        //TODO: Somehow move the correct motors
        //      I'd do it myself, but I haven't implemented that yet.
    }
    return 0;
}

int HardwareManager::suck(){
    if(m_jman->Get(HardwareManager::HW_SUCK_BUTTON_IDX)){
        // TODO: Somehow move the correct motors
        //       I'd do it myself, but I haven't implemented that yet.
    }
    return 0;
}

