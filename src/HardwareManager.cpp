
#include "HardwareManager.h"

HardwareManager::HardwareManager(JoystickManager* jman):
    BaseManager(),
    m_finished(false),
    m_talons(),
    m_servos()
{
    m_drive = NULL;
    m_jman = jman;
}

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    //std::cout << "Calling addTalon(0,\"frontLeft\")" << std::endl;
    //this->addTalon(0,"frontLeft");
    this->m_talons["frontLeft"] = new CANTalon(0);
    this->m_talons["backLeft"] = new CANTalon(1);
    this->m_talons["frontRight"] = new CANTalon(2);
    this->m_talons["backRight"] = new CANTalon(3);
    this->m_servos["TESTSERVO"] = new Servo(0);

    m_drive = new RobotDrive(
            this->m_talons["frontLeft"],this->m_talons["backLeft"],
            this->m_talons["frontRight"],this->m_talons["backRight"]);

    return 0;
}

int HardwareManager::Update(){
    int ret = 0;
    ret |= this->move();
    ret |= this->launch();
    ret |= this->suck();
    ret |= this->climb();
    return ret;
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

int HardwareManager::climb(){
    if(m_jman->Get(HardwareManager::HW_CLIMB_BUTTON_IDX)){
        // TODO: Somehow move the correct motors
        //       I'd do it myself but I haven't implemented that yet.
    }
    return 0;
}

