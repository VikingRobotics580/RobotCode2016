/*
 * RobotVikings
 * Robot.h
 * 12/6/15
 * Declares a class Robot as the main class.
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include "HardwareManager.h"
#include "JoystickManager.h"
#include "AutonomousManager.h"

class IterativeRobot;

class Robot: public IterativeRobot{
    public:
        /*
         * Robot - Constructor
         * Accepts nothing
         * Returns nothing
         * Constructs Robot
         */
        Robot();

        /*
         * Robot - Destructor
         * Accepts nothing
         * Returns nothing
         * Deconstructs Robot
         */
        ~Robot();

        // What do you expect me to write here. These methods do exactly what you think they do: Go back in time to kill John Connor
        inline bool isHardwareDisabled(){ return m_hardware_disabled; };
        inline bool isJoystickDisabled(){ return m_joystick_disabled; };
        inline bool isAutonomoDisabled(){ return m_autonomo_disabled; };

    protected:
        /*
         * RobotInit
         * Accepts nothing
         * Returns nothing
         * Initializes the Robot upon startup
         */
        void RobotInit() override;

        /*
         * AutonomousInit
         * Accepts nothing
         * Returns nothing
         * Prepares the robot for Autonomous mode
         */
        void AutonomousInit() override;

        /*
         * TeleopInit
         * Accepts nothing
         * Returns nothing
         * Prepares the robot for Teleop mode
         */
        void TeleopInit() override;

        /*
         * TestInit
         * Accepts nothing
         * Returns nothing
         * Prepares the robot for Test mode
         */
        void TestInit() override;

        /*
         * DisabledInit
         * Accepts nothing
         * Returns nothing
         * Prepares the robot for Disabled mode
         */
        void DisabledInit() override;

        /*
         * AutonomousPeriodic
         * Accepts nothing
         * Returns nothing
         * Is run periodically during Autonomous mode
         */
        void AutonomousPeriodic() override;

        /*
         * TeleopPeriodic
         * Accepts nothing
         * Returns nothing
         * Is run periodically during Teleop mode
         */
        void TeleopPeriodic() override;

        /*
         * TestPeriodic
         * Accepts nothing
         * Returns nothing
         * Is run periodically during Test mode
         */
        void TestPeriodic() override;

        /*
         * DisabledPeriodic
         * Accepts nothing
         * Returns nothing
         * Is run periodically during Disabled mode
         */
        void DisabledPeriodic() override;
    private:
        HardwareManager* m_hw_man;
        JoystickManager* m_joy_man;
        AutonomousManager* m_auto_man;

        // Disable various managers if they fail to initialize
        bool m_hardware_disabled;
        bool m_joystick_disabled;
        bool m_autonomo_disabled;
};



#endif
