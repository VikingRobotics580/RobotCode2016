/*
 * RobotVikings
 * AutonomousManager.h
 * 12/6/15
 * Declares a class AutonomousManager to control Autonomous mode
 */

#ifndef _AUTONOMOUSDRIVE_H_
#define _AUTONOMOUSDRIVE_H_

#include <string>
#include <vector>
#include "WPILib.h"

#include "BaseManager.h"
#include "structs.h"

enum AutoModes{MODE1,MODE2,MODE3,MODE4,MODE5,MODE6};

class AutonomousManager: public BaseManager{
    public:
        const static int AUTO_MAGIC_NUMBER = 0x4155544f;
        /*
         * AutonomousManager - Constructor
         * Accepts no parameters
         * Constructs AutonomousManager
         */
        AutonomousManager();

        /*
         * AutonomousManager - Constructor
         * Accepts no parameters
         * Constructs AutonomousManager
         */
        AutonomousManager(std::string&);

        /*
         * AutonomousManager - Destructor
         * Accepts no parameters
         * Deconstructs AutonomousManager
         */
        ~AutonomousManager();

        /*
         * Initialize
         * Accepts nothing
         * Returns nothing
         * Initializes AutonomousManager
         */
        int Init() override;

        /*
         * Execute
         * Accepts nothing
         * Returns nothing
         * Is constantly called during Autonomous mode.
         */
        int Update() override;

        /*
         * IsFinished
         * Accepts nothing
         * Returns a boolean
         * Will return true if Autonomous is done executing. False otherwise
         */
        bool IsFinished() override;

        /*
         * End
         * Accepts nothing
         * Returns nothing.
         * Will run cleanup on AutonomousManager when IsFinished returns True
         */
        int End() override;

        /*
         * Interrupted
         * Accepts nothing
         * Returns nothing
         * Similarly to End, Interrupted runs cleanup on AutonomousManager if an error occurs while it is running.
         */
        //void Interrupted() override;

    protected:
        /*
         * mode
         * Accepts nothing
         * Returns 0 upon success and 1 upon failure
         * Parses m_auto_syntax and executes the commands specified by it.
         */
        int mode();

    private:
        /*
         * readAutoSyntax
         * Accepts nothing
         * Returns 0 upon success and 1 upon failure
         * Reads the contents of m_filename into m_auto_syntax
         */
        int readAutoSyntax();

        instruction* m_instructions;
        std::string m_filename;

        int m_instruction_amt;
        char* m_auto_raw_data;
};



#endif
