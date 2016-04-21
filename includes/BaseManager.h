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
        virtual int Init(void) = 0;
        virtual int Update(void) = 0;
        virtual bool IsFinished(void) = 0;
        virtual int End(void) = 0;
};

#endif

