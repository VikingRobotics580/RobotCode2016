
#ifndef _HARDWARE_MANAGER_H_
#define _HARDWARE_MANAGER_H_

#include <iostream>
#include <map>
#include <string>

#include "WPILib.h"

#include "JoystickManagerManager.h"
#include "BaseManager.h"
#include "structs.h"
#include "macros.h"

typedef std::map<std::string,SpeedController*> talon_map;
typedef std::map<std::string,Servo*> servo_map;
typedef std::map<std::string,AnalogInput*> analogio_map;
typedef std::map<std::string,DigitalInput*> digitalio_map;
//typedef std::map<std::string,SpeedController*> talon_map;

class HardwareManager: public BaseManager {
    public:
        // TODO: Replace these with the actual buttons
        const static int HW_LAUNCH_BUTTON_IDX = 1;
        const static int HW_SUCK_BUTTON_IDX = 2;
        const static int HW_CLIMB_BUTTON_IDX = 3;
        const static int HW_RELEASE_BUTTON_IDX = 4;
        const static int HW_RAISE_BUTTON_IDX = 5;
        const static int HW_EXTEND_BUTTON_IDX = 7;

        // TODO: Actually define these
        const static float WHEEL_RPM_FULL_SPEED;
        const static float WHEEL_RADIUS;

        HardwareManager(JoystickManagerManager*);
        virtual ~HardwareManager();

        int Init() override;
        int Update() override;
        bool IsFinished() override;
        int End() override;
        int move();
        int launch();
        int suck();
        int climb();
        int release();
        int init_climb();
        int init_suck();
        int uninit_suck();
        int move_arm();
        int stop_suck();

        int getDistanceSensorValue();

        /*
         * getAllTalons
         * Accepts void
         * Returns a talon_map
         * Returns the map of existing talons
         */
        inline talon_map& getAllTalons(){ return this->m_talons; };

        inline servo_map& getAllServos(){ return this->m_servos; };

        /*
         * getTalon
         * Accepts a std::string&
         * Returns a SpeedController*
         * Returns the SpeedController specified by iden
         */
        inline SpeedController* getTalon(std::string& iden){
            if(this->m_talons.find(iden) != this->m_talons.end())
                return this->m_talons.at(iden);
            else
                return NULL;
        }
        inline SpeedController* getTalon(const char* iden){
            return this->getTalon((std::string&)iden);
        }

        /*
         * addTalon
         * Accepts an int and std::string&
         * Returns void
         * Adds a CANTalon to the registered talons, with a unique identifier
         */
        inline void addTalon(int id){
            std::string i = std::to_string(id);
            this->addTalon(id,i);
        }
        inline void addTalon(int id,std::string& identifier){
            log_info("Adding Talon '%s' : %d",identifier.c_str(),id);
            this->m_talons[identifier] = new CANTalon(id);
        }
        inline void addTalon(int id,const char* identifier){
            this->addTalon(id,(std::string&)identifier);
        }

        inline bool hasWinchBeenActivated(){ return this->m_servos["WinchActivate"]->GetAngle() == 360; };

    private:
        bool m_finished;
        talon_map m_talons;
        servo_map m_servos; // :(
        analogio_map m_anaios; // Oh well, guess we are using a map for each port now.
        digitalio_map m_digios;
        //sensor_map m_sensors;
        RobotDrive* m_drive;
        JoystickManagerManager* m_jman;
};

#endif

