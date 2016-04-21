// A simple joystick class to phase out the old JoystickManager and JoystickManagerManager

#ifndef _JOYSTICK_MANAGER_2_H_
#define _JOYSTICK_MANAGER_2_H_

#include <array>
#include <vector>

#include "WPILib.h"
#include "buttons.h"
#include "HardwareManager.h"

class joystick {
    public:
        /*
         * joystick - Constructor
         * Accepts 3 ints and a HardwareManager*
         * Returns nothing (obviously)
         * Constructs the joystick object
         */
        joystick(int,int,int,HardwareManager*);

        /*
         * joystick - Destructor
         * Accepts nothing
         * Returns nothing (obviously)
         * Deconstructs the joystick object
         */
        ~joystick();

        /*
         * Init
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Initializes everything about the joystick object, including all of the joystick buttons and fake arrays
         */
        int Init(void);

        /*
         * GetButton
         * Accepts an int (identifier)
         * Returns an int (either 0 or 1)
         * Gets whether or not the specified button is being pressed (1 or 0 respectively)
         */
        int GetButton(int);

        /*
         * GetAxis
         * Accepts an int (identifier)
         * Returns a float (a value between -1 and 1)
         * Gets the current value of the axis at the specified identifier
         */
        float GetAxis(int);

        // Two methods to fake joystick input
        void FakeButton(int,float,float);
        void FakeAxis(int,float,float);

        // Sanity check, make sure everything is not null
        // Return true on success, false otherwise
        bool checkSanity();

        /*
         * GetJoystick
         * Accepts nothing
         * Returns a Joystick object
         * Gets the Joystick object held by this joystick object
         */
        inline Joystick* GetJoystick(){ return m_joystick; };

        /*
         * GetJoystickButton
         * Accepts an int (identifier)
         * Returns a JoystickButton object
         * Gets the JoystickButton object specified
         */
        inline JoystickButton* GetJoystickButton(int id){ return m_joybuttons[id]; };

        /*
         * getID
         * Accepts nothing
         * Returns an int
         * Gets the identifier number of the current joystick
         */
        inline int getID(){ return m_id; };

        /*
         * getBAmt
         * Accepts nothing
         * Returns an int
         * Gets the number of buttons
         */
        inline int getBAmt(){ return m_button_amt; };
        /*
         * getAAmt
         * Accepts nothing
         * Returns an int
         * Gets the number of axes
         */
        inline int getAAmt(){ return m_axis_amt; };

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

};

#endif

