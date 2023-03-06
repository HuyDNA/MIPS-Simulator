#include "../visual_class_macros.h"
#include "Register.h"
#include "RegisterFile.h"
#include "RAM.h"
#include "Computer.h"

Computer::Computer() = default;

Computer::Computer(const Computer& otherComputer): 
    registerFile {otherComputer.registerFile},
    pc {otherComputer.pc},
    ram {otherComputer.ram} {

}

Computer::~Computer() = default;

Register& Computer::getPC() {
    return pc;
}

Register& Computer::getRegisterOfNumber(int number) {
    return registerFile.getRegister(number);
}

RAM& Computer::getRAM() {
    return ram;
}