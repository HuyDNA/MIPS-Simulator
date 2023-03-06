#include "UtilityClasses/MemoryDumper.h"

#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include <string>
#include <cstddef>
#include <stdexcept>

using std::string;

string MemoryDumper::dumpWordInHexa(const Word& word) {
    string result = "0x";
    
    result += getByteRepresentationInHexa(word.byte1);
    result += getByteRepresentationInHexa(word.byte2);
    result += getByteRepresentationInHexa(word.byte3);
    result += getByteRepresentationInHexa(word.byte4);

    return result;
}

string MemoryDumper::getByteRepresentationInHexa(const Byte& byte) {
    string result = "";
    
    Byte upperHexa = byte >> 4;
    result += getHalfByteRepresentationInHexa(upperHexa);
    
    Byte lowerHexa = (byte << 4) >> 4;
    result += getHalfByteRepresentationInHexa(lowerHexa);

    return result;
}

string MemoryDumper::getHalfByteRepresentationInHexa(const Byte& byte) {
    switch (std::to_integer(byte)) {
        case 0: return "0";
        case 1: return "1";
        case 2: return "2";
        case 3: return "3";
        case 4: return "4";
        case 5: return "5";
        case 6: return "6";
        case 7: return "7";
        case 8: return "8";
        case 9: return "9";
        case 10: return "a";
        case 11: return "b";
        case 12: return "c";
        case 13: return "d";
        case 14: return "e";
        case 15: return "f";
        
        default: 
            throw std::runtime_error("byte value out-of-range in MemoryDumper::getHalfByteRepresentationInHexa(const Byte& byte)");
    }
}