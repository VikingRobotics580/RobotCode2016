#include "AimAssist.h"
#include "HardwareManager.h"
#include "macros.h"

const float AimAssist::APPROPRIATE_DIST = 0.0;
const float AimAssist::TOLERANCE = 0.0;

AimAssist::AimAssist(HardwareManager* hwman):
    m_enabled(true)
{
    this->m_hwman = hwman;
}

// Don't do anything because we want Robot::~Robot() to deal with it
AimAssist::~AimAssist(){ }

// Return 0 when it is okay to shoot
// Return 1 otherwise
int AimAssist::assist(){
    float dist = 0; //m_hwman->getSensor("distSensor")->Get();
    float adist = dist-AimAssist::APPROPRIATE_DIST;
    // TODO: Change the ID's for the axes
    if(adist > AimAssist::TOLERANCE){
        //m_jyman->FakeAxisInput(0,0.5,this->distToTime(0.5,adist));
    }else if(adist < -AimAssist::TOLERANCE){
        //m_jyman->FakeAxisInput(0,-0.5,this->distToTime(0.5,adist));
    }else{
        return 0;
    }
    return 1;
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

