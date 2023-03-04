#include "../visual_class_macros.h"
#include "ContiguousMemoryHardware.h"
#include "Register.h"
#include "../MemoryUnitStructs/Byte.h"
#include "../MemoryUnitStructs/Word.h"

#include <cstdint>
#include <string>

using std::string;
using address_t = std::uint_fast32_t;

Register::Register() {
    for (Byte& registerCell : byteArray)
        registerCell = Byte(0);
}

Register::Register(const Register& otherRegister) {
    for (address_t address = 0; address < REGISTER_SIZE_IN_BYTES; ++address)
        byteArray[address] = otherRegister.byteArray[address];
}

Register::~Register() = default;

Byte Register::get(const address_t address) const {
    return byteArray[address];
}

void Register::set(const address_t address, const Byte value) {
    byteArray[address] = value;
}