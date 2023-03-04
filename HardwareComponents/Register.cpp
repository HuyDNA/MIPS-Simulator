#include "../visual_class_macros.h"
#include "ContiguousMemoryHardware.h"
#include "../Visitors/MemoryDumpVisitor.h"

#include <cstddef>
#include <cstdint>
#include <string>

using std::byte;
using std::string;
using address_t = std::uint_fast32_t;

Register::Register() {
    for (byte& registerCell : byteArray)
        registerCell = 0;
}

Register::Register(const Register& otherRegister) {
    for (address_t address = 0; address < REGISTER_SIZE_IN_BYTES; ++address)
        byteArray[address] = otherRegister.byteArray[address];
}

virtual Register::~Register() override = default;

virtual byte Register::get(const address_t address) const override {
    return byteArray[address];
}

virtual void Register::set(const address_t address, const byte value) override {
    byteArray[address] = value;
}