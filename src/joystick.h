// A simple joystick class to phase out the old JoystickManager and JoystickManagerManager

#ifndef _JOYSTICK_MANAGER_2_H_
#define _JOYSTICK_MANAGER_2_H_

#include <array>
#include <vector>

#include "WPILib.h"
#include "HardwareManager.h"

class joystick {
    private:
        int m_id;
        int m_button_amt;
        int m_axis_amt;

        Joystick* m_joystick;
        HardwareManager* m_hardware_manager;
        std::vector<JoystickButton*> m_joybuttons;
        // A vector of {start time, duration, value}
        std::vector<std::array<float,3>> m_button_fakes;
        std::vector<std::array<float,3>> m_axis_fakes;

    public:
        joystick(int,int,int,HardwareManager*);
        ~joystick();
        int Init(void);
        float GetButton(int);
        float GetAxis(int);
        void FakeButton(int,float,float);
        void FakeAxis(int,float,float);

        inline Joystick* GetJoystick(){ return m_joystick; };
        inline JoystickButton* GetJoystickButton(int id){ return m_joybuttons[id]; };
};

#endif

