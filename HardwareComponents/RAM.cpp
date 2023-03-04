#include "../visual_class_macros.h"
#include "RAM.h"

#include <cstdint>
#include <string>

using std::string;
using address_t = std::uint_fast32_t;

RAM::RAM() {
    for (Byte& RAMCell : byteArray)
        RAMCell = 0;
}

RAM::RAM(const RAM& otherRAM) {
    for (address_t address = 0; address < RAM_SIZE_IN_BYTES; ++address)
        byteArray[address] = otherRAM.byteArray[address];
}

virtual RAM::~RAM() override = default;

virtual Byte RAM::get(const address_t address) const override {
    return byteArray[address];
}

virtual void RAM::set(const address_t address, const Byte value) override {
    byteArray[address] = value;
}