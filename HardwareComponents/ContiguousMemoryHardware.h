#ifndef _CONTIGUOUS_MEMORY_HARDWARE_MIPS_SIMULATOR_
#define _CONTIGUOUS_MEMORY_HARDWARE_MIPS_SIMULATOR_

#include "../visual_class_macros.h"

#include <cstdint>
#include <string>

using std::string;
using address_t = std::uint_fast32_t;

Interface ContiguousMemoryHardware {
    public:
        virtual ~ContiguousMemoryHardware() = 0;

        virtual Byte get(const address_t) const = 0;
        virtual void set(const address_t, const Byte) = 0;
};

#endif