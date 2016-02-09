/*
 * JoystickManager.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Maxwell
 */

#ifndef JOYSTICKMANAGER_H_
#define JOYSTICKMANAGER_H_

class JoystickManager {
    private:
        const static int NUM_BUTTS = 6; //lol butts
        const static int NUM_AXES = 6; // Axe me a question
    public:
        JoystickManager(Joystick* j, JoystickButton* butts[NUM_BUTTS]);
        JoystickManager(Joystick* j, JoystickButton* butts[NUM_BUTTS], Timer*);
        ~JoystickManager();
        JoystickButton* GetButtonByIndex(int);
        JoystickButton* GetButtonByID(int);
        bool Get(int);
        float GetAxis(int);
        float GetJoystickX();
        float GetJoystickY();
        float GetJoystickTwist();
        float GetJoystickThrottle();
        void FakeJoystickX(float);
        void FakeJoystickY(float);
        void FakeJoystickTwist(float);
        void Periodic(void);
        void FakeAxisInput(int,float,float);
        void FakePressButton(int, float);
        void ClearFakeJoystickInput();
        void ClearFakeButtonInput();
        void StopAssisted();
        bool IsJoystickSentient();
    private:
        Joystick* m_joystick;
        JoystickButton** m_buttons;
        bool m_pressed[NUM_BUTTS];
        float m_axes[NUM_AXES];

        float m_holdUntil[NUM_BUTTS];
        float m_axisHoldUntil[NUM_AXES];
        float m_fakeJoystickX;
        float m_fakeJoystickY;
        float m_fakeJoystickTwist;
        float m_fakeAxis[NUM_AXES];
        float m_lastDeltaT; //time since last update of X, Y, and Twist values according to dY/dX/dTwist

        /*
         * dY, dX, and dTwist variables are how much it changes the corresponding fakeJoystick
         * values each second.
         *
         * */

        float m_dY = 0.0F; //assuming constant dY/dt
        float m_dX = 0.0F; //assuming constant dX/dt
        float m_dTwist = 0.0F; //assuming constant dTwist/dt
        float* m_dAxisT[NUM_AXES];
        //I could totally make a d^2Y/dt^2 variable but nah
        Timer* m_timer;
};

class XBoxManager : public JoystickManager{

};

#endif
