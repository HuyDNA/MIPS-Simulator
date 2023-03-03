#include "../visual_class_macros.h"
#include "MemoryDumpVisitor.h"

#include <cstddef>
#include <cstdint>
#include <string>

using std::byte;
using std::string;
using address_t = std::uint_fast32_t;

RAM::RAM() {
    for (byte& RAMCell : byteArray)
        RAMCell = 0;
}

RAM::RAM(const RAM& otherRAM) {
    for (address_t address = 0; address < RAM_SIZE_IN_BYTES; ++address)
        byteArray[address] = otherRAM.byteArray[address];
}

virtual RAM::~RAM() override = default;

virtual byte RAM::get(const address_t address) const override {
    return byteArray[address];
}

virtual void RAM::set(const address_t address, const byte value) override {
    byteArray[address] = value;
}

virtual string RAM::acceptDumper(const MemoryDumperVisitor& visitor) const override {
    vistor.visit(*this);
}