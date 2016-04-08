/*
 * RobotVikings
 * Robot.h
 * 12/6/15
 * Declares a class Robot as the main class.
 */

#ifndef ROBOT_H_
#define ROBOT_H_

#include <vector>
#include "HardwareManager.h"
#include "joystickManager.h"
#include "AutonomousManager.h"
#include "joystick.h"

// A simple enumeration of each one of the possible modes the Robot could be in
enum class RModes { TELEOP=0, AUTO=1, TEST=2, DISABLED=3 };

class IterativeRobot;

class Robot: public IterativeRobot{
    public:
        /*
         * A public static variable which indicates what mode the Robot is currently in.
         * This helps other classes (like joystickManager) with their own functionality
         */
        static RModes s_mode;

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

        // 3 methods that simply return the specified manager
        inline AutonomousManager* getAutoMan(){ return m_auto_man; };
        inline HardwareManager* getHardMan(){ return m_hw_man; };
        inline joystickManager* getJoyMan(){ return m_jman; };

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

        /*
         * End
         * Accepts nothing
         * Returns nothing
         * Runs when the robot is done
         */
        void End();// override;

        /*
         * IsFinished
         * Accepts nothing
         * Returns true if the Robot class is finished, false otherwise
         * Does exactly what I just said
         */
        bool IsFinished();
    private:
        HardwareManager* m_hw_man;
        joystickManager* m_jman;
        AutonomousManager* m_auto_man;

        // Disable various managers if they fail to initialize
        bool m_hardware_disabled;
        bool m_joystick_disabled;
        bool m_autonomo_disabled;
};

#endif
