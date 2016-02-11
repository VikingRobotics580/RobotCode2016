
#ifndef _HARDWARE_MANAGER_H_
#define _HARDWARE_MANAGER_H_

#include <map>
#include <string>

#include "WPILib.h"

#include "JoystickManager.h"
#include "BaseManager.h"
#include "structs.h"

typedef std::map<std::string,SpeedController*> talon_map;

class HardwareManager: public BaseManager {
    public:
        // TODO: Replace these with the actual buttons
        const static int HW_LAUNCH_BUTTON_IDX = 1;
        const static int HW_SUCK_BUTTON_IDX = 2;
        const static int HW_CLIMB_BUTTON_IDX = 3;

        HardwareManager(JoystickManager*);
        virtual ~HardwareManager();

        int Init() override;
        int Update() override;
        bool IsFinished() override;
        int End() override;
        int move();
        int launch();
        int suck();
        int climb();

        /*
         * getAllTalons
         * Accepts void
         * Returns a talon_map
         * Returns the map of existing talons
         */
        inline talon_map& getAllTalons(){ return this->m_talons; };

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
        inline void addTalon(int id,std::string& identifier=(std::string&)("")){
            if(identifier.compare("") == 0) identifier = std::to_string(id);
            this->m_talons.at(identifier) = new CANTalon(id);
        }
        inline void addTalon(int id,const char* identifier=""){
            this->addTalon(id,(std::string&)identifier);
        }

    private:
        bool m_finished;
        talon_map m_talons;
        RobotDrive* m_drive;
        JoystickManager* m_jman;
};

#endif

