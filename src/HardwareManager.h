
#ifndef _HARDWARE_MANAGER_H_
#define _HARDWARE_MANAGER_H_

#include <map>
#include <string>

#include "WPILib.h"
#include "BaseManager.h"

class HardwareManager: public BaseManager {
    public:
        HardwareManager();
        ~HardwareManager();

        int Init() override;
        int Update() override;
        bool IsFinished() override;
        int End() override;

        /*
         * getAllTalons
         * Accepts void
         * Returns a std::map<std::string,CANTalon*>
         * Returns the map of existing talons
         */
        inline std::map<std::string,CANTalon*>& getAllTalons(){ return this->m_talons; };

        /*
         * getTalon
         * Accepts a std::string&
         * Returns a CANTalon*
         * Returns the CANTalon specified by iden
         */
        inline CANTalon* getTalon(std::string& iden){
            if(this->m_talons.find(iden) != this->m_talons.end()) 
                return this->m_talons.at(iden);
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
    private:
        bool m_finished;
        std::map<std::string,CANTalon*> m_talons;
};

#endif

