/*
 * Maxwell Chow
 * ButtonManager.cpp
 * 16-Jan-16
 *
 * Caffeine consumed while writing this file: 68mg
 *
 *  The only thing we have to fear are off-by-one errors in the ButtonManager class itself.
 */

#include "WPILib.h"
#include "stdio.h"
#include "JoystickManager.h"

JoystickManager::JoystickManager(Joystick* j){
    m_joystick = j;
    m_buttons = new JoystickButton*[NUM_BUTTS];
    for(int i=0; i <  NUM_BUTTS; i++)
        m_buttons[i] = new JoystickButton(j,i);
    m_timer = new Timer();
    m_timer->Start();
    m_fakeJoystickX = 0;
    m_fakeJoystickY = 0;
    m_fakeJoystickTwist = 0;
    m_lastDeltaT = m_timer->Get();
}

/*
 * JoystickManager Constructor
 *
 * Accepts a Joystick pointer and an array of JoystickButton*s.
 *
 * When using this constructor, the timer is autoinitialized and started at zero.
 *
 * */

JoystickManager::JoystickManager(Joystick* j, JoystickButton* butts[NUM_BUTTS]) {
    m_joystick = j;
    m_buttons = butts;
    m_timer = new Timer();
    m_timer->Start();
    m_fakeJoystickX = 0;
    m_fakeJoystickY = 0;
    m_fakeJoystickTwist = 0;
    m_lastDeltaT = m_timer->Get();
}

/*
 * JoystickManager Constructor
 *
 * Accepts same parameters as the first constructor, plus a Timer* object (usually
 *  initialized in the class this is being constructed). The advantage of this
 *  constructor is that the Timer* can be started or stopped already.
 *
 * */

JoystickManager::JoystickManager(Joystick* j, JoystickButton* butts[NUM_BUTTS], Timer* time) {
    m_joystick = j;
    m_buttons = butts;
    m_timer = time;
    m_fakeJoystickX = 0;
    m_fakeJoystickY = 0;
    m_fakeJoystickTwist = 0;
    m_lastDeltaT = m_timer->Get();
}

JoystickManager::~JoystickManager(){ }

/*
 * GetButtonByIndex
 *
 * Returns a JoystickButton* pointer corresponding to the index parameter. Useful
 *  if you want to get the button back and check stuff w/o JoystickManager, or you're
 *  destructing the JoystickManager, or constructing a new one.
 *
 * */

JoystickButton* JoystickManager::GetButtonByIndex(int index) {
    return m_buttons[index];
}

/*
 * GetButtonByID
 *
 * Identical to GetButtonByIndex but gets the buttons by their ID. Duh.
 *
 * */

JoystickButton* JoystickManager::GetButtonByID(int id) {
    return m_buttons[id - 1];
}

/*
 * Get
 *
 * Checks if the button at the specified index is pressed (true if pressed,
 *  false otherwise)
 *
 * */

bool JoystickManager::Get(int index) {
    return m_pressed[index];
}

/*
 * FakePressButton
 *
 * Tells JoystickManager to simulate a button press at the specified index
 *  for the specified duration.
 * */

void JoystickManager::FakePressButton(int index, float duration) {
    float currTime = m_timer->Get();
    m_holdUntil[index] = currTime + duration;
}

/*
 * Periodic
 *
 * Call this in the Periodic method of the IterativeRobot.
 *
 * */

void JoystickManager::Periodic() {
    for (size_t i = 0; i < NUM_BUTTS; ++i) {
        if (m_holdUntil[i] >= m_timer->Get()) {
            m_pressed[i] = true;
        } else {
            m_pressed[i] = m_buttons[i]->Get();
        }
    }
    float dT = m_timer->Get() - m_lastDeltaT;
    m_fakeJoystickX += m_dX / dT;
    m_fakeJoystickY += m_dY / dT;
    m_fakeJoystickTwist += m_dTwist / dT;

    for (size_t i = 0; i < NUM_AXES; ++i){
        if(m_axisHoldUntil[i] >= m_timer->Get())
            m_axes[i] = m_fakeAxis[i];
        else
            m_axes[i] = m_joystick->GetRawAxis(i);
    }

    m_lastDeltaT = m_timer->Get();
}

bool JoystickManager::IsJoystickSentient() {
    return true;
}

/*
 * GetJoystickX
 *
 * Returns a float in the interval [-1,1] representing the Joystick's
 *  input on the X-Axis.
 *
 * */

float JoystickManager::GetJoystickX() {
    return m_joystick->GetX() + m_fakeJoystickX;
}

/*
 * GetJoystickY
 *
 * Literally the exact same thing as the X version. Dummy.
 *
 * */

float JoystickManager::GetJoystickY() {
    return m_joystick->GetY() + m_fakeJoystickY;
}

/*
 * GetJoystickTwist
 *
 * Same as GetJoystickX, but gets how far the Joystick is twisted.
 *
 * */

float JoystickManager::GetJoystickTwist() {
    return m_joystick->GetTwist() + m_fakeJoystickTwist;
}

void JoystickManager::FakeJoystickX(float x) {
    m_fakeJoystickX = x;
}

void JoystickManager::FakeJoystickY(float y) {
    m_fakeJoystickY = y;
}

void JoystickManager::FakeJoystickTwist(float twist) {
    m_fakeJoystickTwist = twist;
}

void JoystickManager::ClearFakeJoystickInput() {
    m_dX = 0;
    m_dY = 0;
    m_dTwist = 0;
    m_fakeJoystickX = 0;
    m_fakeJoystickY = 0;
    m_fakeJoystickTwist = 0;
}

void JoystickManager::ClearFakeButtonInput() {
    for(size_t i = 0; i < NUM_BUTTS; ++i) {
        m_holdUntil[i] = m_timer->Get();
    }
}

void JoystickManager::StopAssisted() {
    ClearFakeJoystickInput();
    ClearFakeButtonInput();
}

float JoystickManager::GetAxis(int id){
    return m_axes[id];
}

void JoystickManager::FakeAxisInput(int id, float value, float duration){
    float curr_time = m_timer->Get();
    m_axisHoldUntil[id] = curr_time + duration;
    m_fakeAxis[id] = value;
}

