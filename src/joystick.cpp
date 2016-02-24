#include "joystick.h"
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

joystick::joystick(Joystick* joy,int num_buttons,int num_axes,HardwareManager* hwm):
    m_id(0),
    m_button_amt(num_buttons),
    m_axis_amt(num_axes),
    m_joybuttons(),
    m_button_fakes(),
    m_axis_fakes()
{
    log_warn("DO NOT USE THIS CONSTRUCTOR!");
    m_joystick = joy;
    m_hardware_manager = hwm;
}

joystick::~joystick(){
    // Delete the JoystickButton*'s first because they use m_joystick
    for(auto& jb : m_joybuttons) delete jb;
    delete m_joystick;
}

int joystick::Init(){
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

int joystick::GetButton(int id){
    if(m_hardware_manager->hasPassed(m_button_fakes.at(id).at(0),m_button_fakes[id][1])){
        return m_joybuttons[id]->Get();
    }else
        return (int)(m_button_fakes[id][2]);
}

float joystick::GetAxis(int id){
    if(m_hardware_manager->hasPassed(m_axis_fakes.at(id).at(0),m_axis_fakes[id][1]))
        return m_joystick->GetRawAxis(id);
    else
        return m_axis_fakes[id][2];
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

