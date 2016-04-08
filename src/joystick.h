// A simple joystick class to phase out the old JoystickManager and JoystickManagerManager

#ifndef _JOYSTICK_MANAGER_2_H_
#define _JOYSTICK_MANAGER_2_H_

#include <array>
#include <vector>

#include "WPILib.h"
#include "buttons.h"
#include "HardwareManager.h"

class joystick {
    private:
        int m_id;
        int m_button_amt;
        int m_axis_amt;

        // The joystick
        Joystick* m_joystick;
        HardwareManager* m_hardware_manager;
        // All buttons that we care about
        std::vector<JoystickButton*> m_joybuttons;
        // A vector of {start time, duration, value}
        std::vector<std::array<float,3>> m_button_fakes;
        std::vector<std::array<float,3>> m_axis_fakes;

    public:
        // The Constructor
        // Accepts 3 ints, and a hardware manager
        // ID, number of buttons, number of axes, HardwareManager object
        joystick(int,int,int,HardwareManager*);
        ~joystick();

        int Init(void);
        int GetButton(int);
        float GetAxis(int);

        // Two methods to fake joystick input
        void FakeButton(int,float,float);
        void FakeAxis(int,float,float);

        // Sanity check, make sure everything is not null
        // Return true on success, false otherwise
        bool checkSanity();

        inline Joystick* GetJoystick(){ return m_joystick; };
        inline JoystickButton* GetJoystickButton(int id){ return m_joybuttons[id]; };

        inline int getID(){ return m_id; };
        inline int getBAmt(){ return m_button_amt; };
        inline int getAAmt(){ return m_axis_amt; };
};

#endif

