
#ifndef _VISION_MANAGER_H_
#define _VISION_MANAGER_H_

#include <string>
#include "Vision/AxisCamera.h"
#include "Vision/VisionAPI.h"
#include "BaseManager.h"

class VisionManager: public BaseManager {
    public:
        // TODO: Finish off these constants
        const std::string CAM_IP = "";
        const int CAM_WIDTH = 320;
        const int CAM_HEIGHT = 240;
        const int SAMPLE_WIDTH = 320;
        const int SAMPLE_HEIGHT = 240;
        const int MASK_COLOR = 0xFF0000;
        const int TOLERANCE_PERCENT = 30; // How much of a percentage is allowed to be different before we decide that it is not right

        VisionManager(int);
        ~VisionManager();

        int Update() override;
        int Init() override;
        bool IsFinished() override;
        int End() override;

        bool hasImageChanged();
        inline int* getLastPosition(){ return this->m_lastPos; };
        inline int* getCurrPosition(){ return this->m_currPos; };

        int* compareImgFrom(Image*,int,int);
        int findMostSignificantArtifact(Image*,int[2]);

        int takeAndSaveTestImage();
    private:
        int* m_lastPos;
        int* m_currPos;
        int m_updateTimer;
        int m_maxUpdateTicks;
        bool m_finished;
        AxisCamera* m_camera;

        Image* m_sample_img;
};

#endif

