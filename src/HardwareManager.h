
#ifndef _HARDWARE_MANAGER_H_
#define _HARDWARE_MANAGER_H_

#include <map>
#include <string>

#include "WPILib.h"
#include "BaseManager.h"

typedef std::map<std::string,SpeedController*> talon_map;

class HardwareManager: public BaseManager {
    public:
        HardwareManager();
        ~HardwareManager();

        int Init() override;
        int Update() override;
        bool IsFinished() override;
        int End() override;
        int move();

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
};

#endif

