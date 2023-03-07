#ifndef _CONTIGUOUS_MEMORY_HARDWARE_MIPS_SIMULATOR_
#define _CONTIGUOUS_MEMORY_HARDWARE_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include <cstdint>
#include <string>

using std::string;
using address_t = std::uint_fast32_t;

Interface ContiguousMemoryHardware {
    public:
        virtual ~ContiguousMemoryHardware() = default;
        ContiguousMemoryHardware& operator=(const ContiguousMemoryHardware&) = delete;
        ContiguousMemoryHardware& operator=(ContiguousMemoryHardware&&) = delete;

        virtual Byte get(const address_t) const = 0;
        virtual void set(const address_t, const Byte) = 0;
};

#endif