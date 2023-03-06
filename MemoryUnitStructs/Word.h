#ifndef _WORD_MIPS_SIMULATOR_
#define _WORD_MIPS_SIMULATOR_

#include "MemoryUnitStructs/Byte.h"

struct Word {
    static const int WORD_SIZE_IN_BYTES = 4;
    Byte byte1;
    Byte byte2;
    Byte byte3;
    Byte byte4;
};

#endif