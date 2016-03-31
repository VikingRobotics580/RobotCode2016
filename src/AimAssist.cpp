#include "AimAssist.h"
#include "HardwareManager.h"
#include "VisionManager.h"
#include "macros.h"

const float AimAssist::APPROPRIATE_DIST = 0.0;
const float AimAssist::TOLERANCE = 0.0;

AimAssist::AimAssist(HardwareManager* hwman,VisionManager* viman):
    m_enabled(true)
{
    this->m_hwman = hwman;
    this->m_viman = viman;
}

// Don't do anything because we want Robot::~Robot() to deal with it
AimAssist::~AimAssist(){ }

// Return 0 when it is okay to shoot
// Return 1 otherwise
int AimAssist::assist(){
    float l=0;
    float r=0;

    l = this->determineLeftOrRight()==2 ? 0.5:0;
    r = this->determineLeftOrRight()==1 ? 0.5:0;

    // Do this because the | operator doesn't work on floats
    int neither = ((int)(l+0.5))|((int)(r+0.5));

    // If l|r comes out to 0, then we are in position to shoot (both are 0, so the method determined that we don't need to adjust any more)
    if(neither != 0){
        m_hwman->move(l,r);
        return 1;
    }
    log_info("In position, adjustment done.");
    return 0;
}

// Ya know, this entire method could easily fit onto one line
// We might even save a few bytes of memory on variables
float AimAssist::distToTime(float pwr,float dist){
    // The only time a nested ternary is fine.
    float npwr = (pwr > 1 ? 1 : (pwr < -1 ? -1 : pwr));
    float actual = HardwareManager::WHEEL_RPM_FULL_SPEED*npwr;
    float angular_vel = actual/(2*PI);
    float linear_vel = angular_vel*HardwareManager::WHEEL_RADIUS;
    return (linear_vel/dist)*60; // seconds
}

// Returns:
//  0 - neither
//  1 - right
//  2 - left
int AimAssist::determineLeftOrRight(){
    int* cpos = this->m_viman->getCurrPosition();

    // We have a 5 pixel tolerance (I'm pretty sure we won't be _that_ off if the image isn't 100% centered).
    if(cpos[0] < this->m_viman->CAM_WIDTH-5){
        return 1;
    }else if(cpos[0] > this->m_viman->CAM_WIDTH+5){
        return 2;
    }else{
        return 0;
    }
}

