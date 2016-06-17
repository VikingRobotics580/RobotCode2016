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

#include "HardwareManager.h"
#include "BaseManager.h"

enum AutoModes{MODE1,MODE2,MODE3,MODE4,MODE5,MODE6};

class AutonomousManager: public BaseManager{
    public:
        // These constants are related to the idea Max and I had of using a special file type to store Autonomous mode code
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
        AutonomousManager(HardwareManager*);

        /*
         * AutonomousManager - Destructor
         * Accepts no parameters
         * Deconstructs AutonomousManager
         */
        virtual ~AutonomousManager();

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
         * setMode
         * Accepts an int
         * Returns nothing
         * Sets the current mode to m_mode
         */
        inline void setMode(int mode){ this->m_mode = mode; };
        /*
         * getMode
         * Accepts nothing
         * Returns an int
         * returns the current mode
         */
        inline int getMode(){ return this->m_mode; };

    protected:
        /*
         * mode
         * Accepts nothing
         * Returns 0 upon success and 1 upon failure
         * Executes a hardcoded autonomous mode. Should only run if Init fails or if USE_EXPERIMENTAL_AUTO_METHOD is not defined
         */
        int mode();


        /*
         * modeN (where N is any number from 1 to the maximum possible Autonomous value)
         * Accepts nothing
         * A series of methods that each return 0 upon success and 1 upon failure
         * A series of methods that perform hardcoded autonomous modes.
         */
        int mode0();
        int mode1();
        int mode2();
        int mode3();
        int mode4();
        int mode5();
        int mode6();
        int mode7();

    private:
        HardwareManager* m_hw_man;

        bool m_useHardcodedAuto;
        bool m_finished;

        // A number which determins which autonomous mode to run
        int m_mode;
        // A number which specifies the time at which the mode starts
        float m_mode_start;
};

#endif

