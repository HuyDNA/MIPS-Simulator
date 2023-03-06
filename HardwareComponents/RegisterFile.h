#ifndef _REGISTER_FILE_MIPS_SIMULATOR_
#define _REGISTER_FILE_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "HardwareComponents.Register.h"

#include <cstddef>
#include <cstdint>
#include <string>

using std::byte;
using std::string;

Class RegisterFile {
    public:
        static constexpr int NUMBER_OF_REGISTERS = 32;
    private:
        array<Register, NUMBER_OF_REGISTERS> registerArray;
    public:
        RegisterFile();
        RegisterFile(const RegisterFile&);
        ~RegisterFile();
        
        Register& getRegister(int);
};

#endif