#include "../visual_class_macros.h"
#include "Register.h"
#include "RegisterFile.h"
#include "RAM.h"

Computer::Computer() = default;

Computer::Computer(const Computer& otherComputer): 
    registerFile {otherComputer.registerFile},
    PC {otherComputer.PC},
    RAM {otherComputer.RAM} {

}

Computer::~Computer() = default;

Register& Computer::getPC() {
    return PC;
}

Register& Computer::getRegisterOfNumber(int number) {
    return registerFile.getRegister(number);
}

RAM& Computer::getRAM() {
    return RAM;
}