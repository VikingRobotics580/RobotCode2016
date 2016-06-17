
#ifndef _HARDWARE_MANAGER_H_
#define _HARDWARE_MANAGER_H_

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "WPILib.h"

#include "BaseManager.h"
#include "macros.h"
#include "types.h"

class joystick;

class HardwareManager: public BaseManager {
    public:
        // I don't think these button definitions actually do anything anymore, since we've replaced it all with the definitions in buttons.h
        // These 4 are actually just for the arcade-controller thing
        const static int HW_RAISE_BUTTON_IDX = 1;
        const static int HW_LOWER_BUTTON_IDX = 2;
        const static int HW_EXTND_BUTTON_IDX = 3;
        const static int HW_RETRCT_BUTTON_IDX = 4;

        const static int HW_SUCK_BUTTON_IDX = 5;
        const static int HW_LAUNCH_BUTTON_IDX = 6;
        const static int HW_WINCH_BUTTON_IDX = 7;
        const static int HW_RELEASE_BUTTON_IDX = 8;
        const static int HW_MISSILE_BUTTON_IDX = 9;
        const static int HW_LAUNCH_INIT_BUTTON_IDX = 10;

        // TODO: Actually define these
        const static float WHEEL_RPM_FULL_SPEED;
        const static float WHEEL_RADIUS;
        const static float DIST_SENSOR_CONST;

        HardwareManager();
        virtual ~HardwareManager();

        /*
         * Init
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Initializes all hardware-related things.
         */
        int Init() override;

        /*
         * Update
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Constantly updates various hardware objects if necessary
         */
        int Update() override;

        /*
         * IsFinished
         * Accepts nothing
         * Returns a bool if the manager is finished doing its thing
         * Simply returns if it is finished doing things.
         */
        bool IsFinished() override;

        /*
         * End
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Cleans up and uninitializes hardware objects
         */
        int End() override;

        /*
         * move
         * Accepts two floats
         * Returns an int (0 upon success, 1 upon failure)
         * Moves the robot based on the two floats passed
         */
        int move(float,float);

        /*
         * launch
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Launches the held ball
         */
        int launch();

        /*
         * suck
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * sucks a ball into the shooting mechanism
         */
        int suck();

        /*
         * release
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * gently ejects the ball from the shooting mechanism
         */
        int release();

        /*
         * init_climb
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Connects the winch mechanism to the drive system.
         * If you want to know why we do this, ask the Hardware team, as it is too long to explain here.
         */
        int init_climb();

        /*
         * stop_suck
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Turns off the intake system
         */
        int stop_suck();

        /*
         * init_launch
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Initializes the launch system before shooting
         */
        int init_launch();

        /*
         * reset_launch
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Resets the launch system by setting everything back to its starting point
         */
        int reset_launch();

        /*
         * raise
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Raises the arm
         */
        int raise();

        /*
         * stop_raise
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Stops the arm from raising or lowering
         */
        int stop_raise();

        /*
         * lower
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Lowers the arm
         */
        int lower();

        /*
         * stop_lower
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Stops the arm from raising or lowering
         */
        int stop_lower();

        /*
         * extend
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Extends the arm
         */
        int extend();
        /*
         * retract
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Retracts the arm
         */
        int retract();

        /*
         * stopExtRet
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Stops both the extension and retraction of the arm
         */
        int stopExtRet();

        /*
         * getDistanceSensorValue
         * Accepts nothing
         * Returns a float 
         * Returns the current value of the distance sensor in meters
         */
        float getDistanceSensorValue();

        /*
         * getAllTalons
         * Accepts void
         * Returns a talon_map
         * Returns the map of existing talons
         */
        inline talon_map& getAllTalons(){ return this->m_talons; };

        /*
         * getAllServos
         * Accepts void
         * Returns a servo_map
         * Returns the map of existing servos
         */
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
         * getDrive
         * Accepts nothing
         * Returns a RobotDrive*
         * Returns the instance of RobotDrive held by this object
         */
        inline RobotDrive* getDrive(){ return this->m_drive; };

        /*
         * addTalon
         * Accepts an int and std::string&
         * Returns void
         * Adds a CANTalon to the registered talons, with a unique identifier
         * IMPORTANT NOTE: These methods are broken. Do not use them
         */
        inline void addTalon(int id){
            std::string i = std::to_string(id);
            this->addTalon(id,i);
        }
        inline void addTalon(int id,std::string& identifier){
            log_info("Adding Talon '%s' : %d",identifier.c_str(),id);
            this->m_talons[identifier] = new CANTalon(id);
        }
        inline void addTalon(int id,const char* identifier=""){
            this->addTalon(id,(std::string&)identifier);
        }

        /*
         * hasWinchBeenActivated
         * Accepts nothing
         * Returns a bool
         * Returns whether or not the arm-winch has been activated
         */
        inline bool hasWinchBeenActivated(){ return this->m_servos["WinchActivate"]->GetAngle() == 360; };

        // Has a certain amount of time passed since start
        inline bool hasPassed(float start, float duration){
            return (start+duration) < m_internal_timer->Get();
        }

        /*
         * getCurrentTime
         * Accepts nothing
         * Returns a float
         * Returns the current time since initialization
         */
        inline float getCurrentTime(){
            return m_internal_timer->Get();
        };

    private:
        bool m_finished;
        talon_map m_talons;
        servo_map m_servos; // :(
        analogio_map m_anaios; // Oh well, guess we are using a map for each port now.
        digitalio_map m_digios;
        RobotDrive* m_drive;
        Timer* m_internal_timer;
};

#endif

