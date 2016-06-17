/*
 * Tyler Robbins
 * 2/3/16
 * Base Manager
 * Pure virtual class to be extended by all Manager classes
 */

#ifndef _BASE_MANAGER_H_
#define _BASE_MANAGER_H_

class BaseManager {
    public:
        // This method is to be overrided to initialize the manager one time before it is updated
        virtual int Init(void) = 0;
        // This method is to be overrided with the code that is run constantly until IsFinished is true
        virtual int Update(void) = 0;
        // This method is to be overrided to return true when Update should end
        virtual bool IsFinished(void) = 0;
        // This method runs once when IsFinished has returned true
        virtual int End(void) = 0;
};

#endif

