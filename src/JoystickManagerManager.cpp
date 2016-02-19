
#include "JoystickManagerManager.h"

JoystickManagerManager::JoystickManagerManager():
    BaseManager(),
    m_jmans()
{
}

JoystickManagerManager::~JoystickManagerManager(){
    for(auto& jm:m_jmans)
        delete jm;
}

int JoystickManagerManager::Update(){
    int ret = 0;
    for(auto& jm:m_jmans)
        ret |= jm->Update();
    return ret;
}

int JoystickManagerManager::Init(){
    int ret = 0;
    for(auto& jm:m_jmans)
        ret |= jm->Init();
    return ret;
}

int JoystickManagerManager::End(){
    int ret = 0;
    for(auto& jm:m_jmans)
        ret |= jm->End();
    return ret;
}

bool JoystickManagerManager::IsFinished(){
    bool ret = 0;
    for(auto& jm:m_jmans)
        ret = ret && jm->End();
    return (bool)ret;
}

int JoystickManagerManager::registerJM(JoystickManager* jm){
    this->m_jmans.push_back(jm);
    return 0;
}

