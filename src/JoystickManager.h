/*
 * JoystickManager.h
 *
 *  Created on: Jan 16, 2016
 *      Author: Maxwell
 */

#ifndef JOYSTICKMANAGER_H_
#define JOYSTICKMANAGER_H_

class JoystickManager {
	public:
		JoystickManager(Joystick* j, JoystickButton* butts[6]);
		JoystickManager(Joystick* j, JoystickButton* butts[6], Timer*);
		~JoystickManager();
		JoystickButton* GetButtonByIndex(int);
		JoystickButton* GetButtonByID(int);
		bool Get(int);
		float GetJoystickX();
		float GetJoystickY();
		float GetJoystickTwist();
		float GetJoystickThrottle();
		void FakeJoystickX(float);
		void FakeJoystickY(float);
		void FakeJoystickTwist(float);
		void Periodic(void);
		void FakePressButton(int, float);
		void ClearFakeJoystickInput();
		void ClearFakeButtonInput();
		void StopAssisted();
		bool IsJoystickSentient();
	private:
		const static int NUM_BUTTS = 6; //lol butts
		Joystick* m_joystick;
		JoystickButton* m_buttons[NUM_BUTTS];
		bool* m_pressed[NUM_BUTTS];
		float* m_holdUntil[NUM_BUTTS];
		float m_fakeJoystickX;
		float m_fakeJoystickY;
		float m_fakeJoystickTwist;
		float m_lastDeltaT; //time since last update of X, Y, and Twist values according to dY/dX/dTwist

		/*
		 * dY, dX, and dTwist variables are how much it changes the corresponding fakeJoystick
		 * values each second.
		 *
		 * */

		float m_dY = 0.0F; //assuming constant dY/dt
		float m_dX = 0.0F; //assuming constant dX/dt
		float m_dTwist = 0.0F; //assuming constant dTwist/dt
		//I could totally make a d^2Y/dt^2 variable but nah
		Timer* m_timer;
};

class XBoxManager : public JoystickManager{

};

#endif
