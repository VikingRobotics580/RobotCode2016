/*
 * The reason this class exists is because I don't feel like trying to rework JoystickManager to support multiple joysticks.
 * As such, I decided to just use a manager of managers, which in turn will be managed by Robot.
 */

#ifndef _JOYSTICK_MANAGER_MANAGER_H_
#define _JOYSTICK_MANAGER_MANAGER_H_

#include <vector>
#include "BaseManager.h"
#include "JoystickManager.h"

class JoystickManagerManager: public BaseManager{
    public:
        JoystickManagerManager();
        virtual ~JoystickManagerManager();
        int Init() override;
        int Update() override;
        int End() override;
        bool IsFinished() override;

        int registerJM(JoystickManager*);

        inline JoystickManager* getJoystickManager(int idx){ return m_jmans.at(idx); };
    private:
        std::vector<JoystickManager*> m_jmans;
};

#endif

