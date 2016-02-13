
#ifndef _AIM_ASSIST_H_
#define _AIM_ASSIST_H_

class HardwareManager;
class JoystickManager;

class AimAssist {
    public:
        const static float APPROPRIATE_DIST;
        const static float TOLERANCE;
        AimAssist(HardwareManager*,JoystickManager*);
        ~AimAssist();
        int assist();
        inline void setEnabled(bool enabled=true){ this->m_enabled = enabled; };
        float distToTime(float pwr,float dist);
    private:
        HardwareManager* m_hwman;
        JoystickManager* m_jyman;
        bool m_enabled;
};

#endif

