#include "visual_class_macros.h"

#include "HardwareComponents/RAM.h"
#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include "UtilityClasses/MemoryDumper.h"

#include <cstdint>
#include <string>
#include <memory>
#include <stdexcept>

using std::string;
using address_t = std::uint_fast32_t;

RAM::RAM() = default;

RAM::RAM(const RAM& otherRAM): 
    textSegmentByteList{otherRAM.textSegmentByteList}, 
    dataSegmentByteList{otherRAM.dataSegmentByteList},
    stackSegmentByteReversedList{otherRAM.stackSegmentByteReversedList} {

}

RAM::RAM(RAM&& otherRAM):
    textSegmentByteList{std::move(otherRAM.textSegmentByteList)},
    dataSegmentByteList{std::move(otherRAM.dataSegmentByteList)},
    stackSegmentByteReversedList{std::move(otherRAM.stackSegmentByteReversedList)} {

}

Byte RAM::get(const address_t address) const {
    if (address < 0 or address >= RAM_SIZE_IN_BYTES)
        throw std::length_error{"RAM::get(): Address out of range"};
    else if (address < TEXT_SEGMENT_START_ADDRESS)
        throw std::runtime_error{"RAM::get(): Can not accessing reserved address"};
    else if (address <= TEXT_SEGMENT_END_ADDRESS)
        return getByteInTextSegment(address);
    else if (address <= DATA_SEGMENT_END_ADDRESS)
        return getByteInDataSegment(address);
    else if (address <= STACK_SEGMENT_END_ADDRESS)
        return getByteInStackSegment(address);
    else
        throw std::runtime_error{"RAM::get(): Unknown address"};
}

void RAM::set(const address_t address, const Byte value) {
    if (address < 0 or address >= RAM_SIZE_IN_BYTES)
        throw std::length_error{"RAM::set(): Address out of range"};
    else if (address < TEXT_SEGMENT_START_ADDRESS)
        throw std::runtime_error{"RAM::set(): Can not accessing reserved address"};
    else if (address <= TEXT_SEGMENT_END_ADDRESS)
        return setByteInTextSegment(address, value);
    else if (address <= DATA_SEGMENT_END_ADDRESS)
        return setByteInDataSegment(address, value);
    else if (address <= STACK_SEGMENT_END_ADDRESS)
        return setByteInStackSegment(address, value);
    else
        throw std::runtime_error{"RAM::set(): Unknown address"};

}

string RAM::getHexaRepresentationOfWordAtByteAddress(const address_t address) const {
    return MemoryDumper::dumpWordInHexa(getRAMWordAtByteAddress(address));
}

Word RAM::getRAMWordAtByteAddress(const address_t address) const {
    return {get(address), get(address + 1), get(address + 2), get(address + 3)};
}

Byte RAM::getByteInTextSegment(const address_t address) const {
    return textSegmentByteList[address - TEXT_SEGMENT_START_ADDRESS];
}
void RAM::setByteInTextSegment(const address_t address, const Byte value) {
    textSegmentByteList[address - TEXT_SEGMENT_START_ADDRESS] = value;
}
        
Byte RAM::getByteInDataSegment(const address_t address) const {
    return dataSegmentByteList[address - DATA_SEGMENT_START_ADDRESS];
}

void RAM::setByteInDataSegment(const address_t address, const Byte value) {
    dataSegmentByteList[address - DATA_SEGMENT_START_ADDRESS] = value;
}

Byte RAM::getByteInStackSegment(const address_t address) const {
    return stackSegmentByteReversedList[STACK_SEGMENT_END_ADDRESS - address];
}

void RAM::setByteInStackSegment(const address_t address, const Byte value) {
    stackSegmentByteReversedList[STACK_SEGMENT_END_ADDRESS - address] = value;
}
