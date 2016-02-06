
#include "HardwareManager.h"

HardwareManager::HardwareManager():
    BaseManager(),
    m_finished(false),
    m_talons()
{ }

HardwareManager::~HardwareManager(){
}

int HardwareManager::Init(){
    return 0;
}

int HardwareManager::Update(){
    return 0;
}

bool HardwareManager::IsFinished(){
    return this->m_finished;
}

int HardwareManager::End(){
    return 0;
}

