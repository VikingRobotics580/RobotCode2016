
#ifndef _NEW_JOYSTICK_MANAGER_H_
#define _NEW_JOYSTICK_MANAGER_H_

#include <string>
#include <map>

#include "WPILib.h"
#include "joystick.h"
#include "BaseManager.h"
#include "HardwareManager.h"
#include "types.h"

class Robot; // Forward declaration of Robot (this fixes a compiler-error when we just included it, no idea why though)

class joystickManager: public BaseManager {
    public:
        /*
         * joystickManager - Constructor
         * Accepts a HardwareManager* and a Robot*
         * Returns nothing (obviously)
         * Constructs joystickManager
         */
        joystickManager(HardwareManager*,Robot*);
        /*
         * joystickManager - Destructor
         * Accepts nothing (obviously)
         * Returns nothing (obviously)
         * Deconstructs joystickManager
         */
        virtual ~joystickManager();

        /*
         * Init
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Initializes the joystickManager object and all joystick objects.
         */
        int Init(void) override;

        /*
         * Update
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failure)
         * Updates things related to joysticks
         */
        int Update(void) override;

        /*
         * End
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failue)
         * Cleans up before the destructor is called
         */
        int End(void) override;

        /*
         * IsFinished
         * Accepts nothing
         * Returns a bool
         * Returns whether or not the manager is finished
         */
        bool IsFinished(void) override;

        /*
         * checkTeleopButtons
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failue)
         * Checks every button that is supposed to be checked in Teleop mode
         */
        int checkTeleopButtons();

        /*
         * checkTestButtons
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failue)
         * Checks every button that is supposed to be checked in Test mode
         */
        int checkTestButtons();

        /*
         * checkAutoButtons
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failue)
         * Checks every button that is supposed to be checked in Autonomous mode
         */
        int checkAutoButtons();

        /*
         * checkDisabledButtons
         * Accepts nothing
         * Returns an int (0 upon success, 1 upon failue)
         * Checks every button that is supposed to be checked in Disabled mode
         */
        int checkDisabledButtons();

        /*
         * checkSanity
         * Accepts nothing
         * Returns an int
         * Checks to make sure that everything is working as intended. 0 if it is, 1 otherwise
         */
        int checkSanity();

        /*
         * getJoystick
         * Accepts a string (identifier)
         * Returns a joystick object
         * Gets the joystick object specified by str
         */
        inline joystick* getJoystick(std::string& str){ return m_joysticks[str]; };

    private:
        jmap m_joysticks;
        HardwareManager* m_hardware_manager;
        Robot* m_robot;
};

#endif

