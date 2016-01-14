/*
 * RobotVikings
 * AutonomousDrive.h
 * 12/6/15
 * Declares a class AutonomousDrive to control Autonomous mode
 */

#ifndef _AUTONOMOUSDRIVE_H_
#define _AUTONOMOUSDRIVE_H_

#include <string>
#include "WPILib.h"

enum AutoModes{MODE1,MODE2,MODE3,MODE4,MODE5,MODE6};

class AutonomousDrive: public Command{
    public:
        /*
         * AutonomousDrive - Constructor
         * Accepts no parameters
         * Constructs AutonomousDrive
         */
        AutonomousDrive();

        /*
         * AutonomousDrive - Destructor
         * Accepts no parameters
         * Deconstructs AutonomousDrive
         */
        ~AutonomousDrive();

        /*
         * Initialize
         * Accepts nothing
         * Returns nothing
         * Initializes AutonomousDrive
         */
        void Initialize() override;

        /*
         * Execute
         * Accepts nothing
         * Returns nothing
         * Is constantly called during Autonomous mode.
         */
        void Execute() override;

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
         * Will run cleanup on AutonomousDrive when IsFinished returns True
         */
        void End() override;

        /*
         * Interrupted
         * Accepts nothing
         * Returns nothing
         * Similarly to End, Interrupted runs cleanup on AutonomousDrive if an error occurs while it is running.
         */
        void Interrupted() override;

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

        std::string m_auto_syntax;
        std::string m_filename;
};



#endif
