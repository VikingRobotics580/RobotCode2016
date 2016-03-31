
#ifndef _AIM_ASSIST_H_
#define _AIM_ASSIST_H_

class HardwareManager;
class VisionManager;

class AimAssist {
    public:
        const static float APPROPRIATE_DIST;
        const static float TOLERANCE;
        AimAssist(HardwareManager*,VisionManager*);
        ~AimAssist();
        int assist();
        inline void setEnabled(bool enabled=true){ this->m_enabled = enabled; };
        float distToTime(float pwr,float dist);
        int determineLeftOrRight();
    private:
        HardwareManager* m_hwman;
        VisionManager* m_viman;
        bool m_enabled;
};

#endif

