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
#include <fstream>
#include "WPILib.h"

#include "BaseManager.h"
#include "JoystickManager.h"
#include "structs.h"

enum AutoModes{MODE1,MODE2,MODE3,MODE4,MODE5,MODE6};

class AutonomousManager: public BaseManager{
    public:
        const static int AUTO_MAGIC_NUMBER = 0x4155544f;
        const static int AUTO_TYPE_MASK = 0xFF00; // 255 different types supported
        const static int AUTO_ID_MASK = 0x00FF; // 255 different ID's supported
        const static int AUTO_MOVE_ID = 0x3000;
        const static int AUTO_AXIS_ID = 0x2000;
        const static int AUTO_BUTT_ID = 0x1000;
        // Only $29.99! 
        // Buy Now! Beat the Rush!

        /*
         * AutonomousManager - Constructor
         * Accepts no parameters
         * Constructs AutonomousManager
         */
        AutonomousManager(JoystickManager*);

        /*
         * AutonomousManager - Constructor
         * Accepts no parameters
         * Constructs AutonomousManager
         */
        AutonomousManager(std::string&,JoystickManager*);

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

        /*
         * executeInstruction
         * Accepts a command_struct (aka command) pointer
         * Returns 0 upon success and 1 upon failure
         * Executes the command
         */
        int executeInstruction(instruction*);

    private:
        /*
         * parseAutoSyntax
         * Accepts nothing
         * Returns 0 upon success and 1 upon failure
         * Parses the contents of m_auto_raw_data into an array of instruction structs.
         */
        int parseAutoSyntax();

        /*
         * readFile
         * Accepts nothing
         * Returns 0 upon success and 1 upon error
         * Reads the contents of m_filename into m_auto_raw_data
         */
        int readFile();

        instruction** m_instructions;
        std::string m_filename;

        int m_current_instruction;
        int m_instruction_amt;
        std::ifstream::pos_type m_raw_data_size;
        char* m_auto_raw_data;
        JoystickManager* m_jman;
};



#endif
