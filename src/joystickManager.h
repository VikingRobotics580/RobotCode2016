
#ifndef _NEW_JOYSTICK_MANAGER_H_
#define _NEW_JOYSTICK_MANAGER_H_

#include "WPILib.h"
#include "joystick.h"
#include "BaseManager.h"
#include "HardwareManager.h"

class joystickManager: public BaseManager {
    public:
        joystickManager(HardwareManager*,int);
        virtual ~joystickManager();

        int Init(void) override;
        int Update(void) override;
        int End(void) override;
        bool IsFinished(void) override;

        void registerJoystick(int,int,int);
        void registerJoystick(int,int);
        void registerJoystick(joystick*);
        void registerJoystick(Joystick*,int,int);

        inline joystick* getJoystick(int id){ return m_joysticks[id-1]; };

    private:
        std::vector<joystick*> m_joysticks;
        HardwareManager* m_hardware_manager;
};

#endif

