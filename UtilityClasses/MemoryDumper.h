#ifndef _MEMORY_DUMPER_MIPS_SIMULATOR_
#define _MEMORY_DUMPER_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "../MemoryUnitStructs/Byte.h"
#include "../MemoryUnitStructs/Word.h"

#include <string>

using std::string;

Class MemoryDumper {
    public:
        static string dumpWordInHexa(const Word&);
    private:
        static string getByteRepresentationInHexa(const Byte&);
        static string getHalfByteRepresentationInHexa(const Byte&);
};

#endif