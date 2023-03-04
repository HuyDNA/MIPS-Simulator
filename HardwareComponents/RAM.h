#ifndef _RAM_MIPS_SIMULATOR_
#define _RAM_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "ContiguousMemoryHardware.h"
#include "../MemoryUnitStructs/Byte.h"
#include "../MemoryUnitStructs/Word.h"

#include <array>
#include <cstdint>
#include <string>

using std::array;
using std::string;
using address_t = std::uint_fast32_t;

Class RAM {
    public:
        static constexpr int RAM_SIZE_IN_BYTES = 4'294'967'296; // 2^32
    private:
        array<Byte, RAM_SIZE_IN_BYTES> byteArray;
    public:
        RAM();
        RAM(const RAM&);
        virtual ~RAM();

        virtual Byte get(const address_t) const override;
        virtual void set(const address_t, const Byte) override;

        string getHexaRepresentationOfWord(const address_t) const;
};

#endif