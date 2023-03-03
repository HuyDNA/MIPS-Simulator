#include "../visual_class_macros.h"
#include "Register.h"

#include <cstddef>
#include <cstdint>
#include <string>

using std::byte;
using std::string;

RegisterFile::RegisterFile() = default;

RegisterFile::RegisterFile(const RegisterFile& otherRegisterFile): 
    registerArray {otherRegisterFile.registerArray} {

}

RegisterFile::~RegisterFile() = default;
        
Register& RegisterFile::getRegister(int number) {
    return registerArray[number];
}