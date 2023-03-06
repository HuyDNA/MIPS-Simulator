#ifndef _COMPUTER_MIPS_SIMULATOR_
#define _COMPUTER_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "Register.h"
#include "RegisterFile.h"
#include "RAM.h"

Class Computer {
    private:
        RegisterFile registerFile;
        Register pc;
        RAM ram;
    public:
        Computer();
        Computer(const Computer&);
        ~Computer();

        Register& getPC();
        Register& getRegisterOfNumber(int);
        RAM& getRAM();
};

#endif