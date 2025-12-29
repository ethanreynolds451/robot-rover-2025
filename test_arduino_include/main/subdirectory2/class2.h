#ifndef CLASS2_h
#define CLASS2_h

#include "subdirectory1/class.h"

class myClass2 {
    public:
        myClass2();
        myClass myObject = myClass();
        void doSomething();
    private:
        int myVariable;
};

#endif