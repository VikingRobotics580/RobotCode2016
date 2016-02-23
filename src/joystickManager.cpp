
#include "joystickManager.h"

joystickManager::joystickManager(HardwareManager* hw,int num=0):
    BaseManager(),
    m_joysticks()
{
    this->m_hardware_manager = hw;
    for(int i=0; i<num; i++)
        //Just do 16 buttons and 16 axes
        this->registerJoystick(i,16,16);
}

joystickManager::~joystickManager(){
    for(auto& joy : this->m_joysticks)
        delete joy;
}

int joystickManager::Init(){
    int ret = 0;
    for(auto& joy : this->m_joysticks)
        ret |= joy->Init();
    return ret;
}

// There isn't anything to do in these
int joystickManager::Update(){ return 0; };
int joystickManager::End(){ return 0; };
bool joystickManager::IsFinished(){ return false; };

void joystickManager::registerJoystick(int id, int nbuttons, int naxes){
    this->m_joysticks.push_back(new joystick(id,nbuttons,naxes,this->m_hardware_manager));
}
void joystickManager::registerJoystick(int nbuttons, int naxes){
    this->m_joysticks.push_back(new joystick(this->m_joysticks.size(),nbuttons,naxes,this->m_hardware_manager));
}
void joystickManager::registerJoystick(joystick* joy){
    this->m_joysticks.push_back(joy);
}
void joystickManager::registerJoystick(Joystick* joy, int nbuttons, int naxes){
    this->m_joysticks.push_back(new joystick(joy,nbuttons,naxes,this->m_hardware_manager));
}

