#include "joystick.h"
#include <iostream>
#include "macros.h"

joystick::joystick(int id, int num_buttons, int num_axes, HardwareManager* hwm):
    m_id(id),
    m_button_amt(num_buttons),
    m_axis_amt(num_axes),
    m_joybuttons(),
    m_button_fakes(),
    m_axis_fakes()
{
    log_test("joystick %d constructed.",id);
    m_joystick = new Joystick(id);
    m_hardware_manager = hwm;
}

joystick::~joystick(){
    // Delete the JoystickButton*'s first because they use m_joystick (prevent a SEGFAULT)
    for(auto& jb : m_joybuttons) delete jb;
    delete m_joystick;
}

int joystick::Init(){
    // Populate m_joybuttons with pointers to JoystickButton objects
    for(int i=0;i<m_button_amt;i++){
        m_joybuttons.push_back(new JoystickButton(m_joystick,i+1));
        m_button_fakes.push_back({0.0,0.0,0.0});
    }
    for(int i=0; i<m_axis_amt;i++){
        m_axis_fakes.push_back({0.0,0.0,0.0});
    }
    log_info("joystick %d initialized with %d buttons and %d axes.",m_id,m_button_amt,m_axis_amt);
    return 0;
}

// :)
int joystick::GetButton(int id){
    // A NULL-check
    if(m_joybuttons.at(id) == NULL){
        log_err("NULL BUTTON FOUND!");
        return -1;
    }else{
        return m_joybuttons[id]->Get();
    }
}

float joystick::GetAxis(int id){
    return m_joystick->GetRawAxis(id);
}

void joystick::FakeButton(int id, float value, float duration){
    m_button_fakes[id][0] = m_hardware_manager->getCurrentTime();
    m_button_fakes[id][1] = duration;
    m_button_fakes[id][2] = value;
}

void joystick::FakeAxis(int id, float value, float duration){
    m_axis_fakes[id][0] = m_hardware_manager->getCurrentTime();
    m_axis_fakes[id][1] = duration;
    m_axis_fakes[id][2] = value;
}

bool joystick::checkSanity(){
    if(m_joybuttons.size() != m_button_amt) return false;

    for(auto& b : m_joybuttons){
        if(b == NULL) return false;
    }
    return m_joystick != NULL;
}

