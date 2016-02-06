
#include "HardwareManager.h"

HardwareManager::HardwareManager():
    BaseManager(),
    m_finished(false),
    m_talons()
{
    m_drive = NULL;
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
    // TODO: Somehow get stuff from JoystickManager
    this->m_drive->TankDrive(0.0,0.0);
    return 0;
}

