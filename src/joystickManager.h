
#ifndef _NEW_JOYSTICK_MANAGER_H_
#define _NEW_JOYSTICK_MANAGER_H_

#include <string>
#include <map>

#include "WPILib.h"
#include "joystick.h"
#include "BaseManager.h"
#include "HardwareManager.h"

class Robot;

typedef std::map<std::string,joystick*> jmap;

class joystickManager: public BaseManager {
    public:
        joystickManager(HardwareManager*,Robot*);
        virtual ~joystickManager();

        int Init(void) override;
        int Update(void) override;
        int End(void) override;
        bool IsFinished(void) override;

        int checkTeleopButtons();
        int checkTestButtons();
        int checkAutoButtons();
        int checkDisabledButtons();
        int checkSanity();

        inline joystick* getJoystick(std::string& str){ return m_joysticks[str]; };

    private:
        //std::vector<joystick*> m_joysticks;
        jmap m_joysticks;
        HardwareManager* m_hardware_manager;
        Robot* m_robot;
};

#endif

