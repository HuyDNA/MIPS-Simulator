#ifndef _REGISTER_MIPS_SIMULATOR_
#define _REGISTER_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "HardwareComponents/ContiguousMemoryHardware.h"
#include "HardwareComponents/Register.h"

#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include <array>
#include <cstdint>
#include <string>

using std::array;
using std::string;
using address_t = std::uint_fast32_t;

Class Register: public ContiguousMemoryHardware {
    public:
        static constexpr int REGISTER_SIZE_IN_BYTES = 4;
    private:
        array<Byte, REGISTER_SIZE_IN_BYTES> byteArray;
    public:
        Register();
        Register(const Register&);
        virtual ~Register() = default;
        Register& operator=(const Register&) = delete;
        Register& operator=(Register&&) = delete;

        virtual Byte get(const address_t) const override;
        virtual void set(const address_t, const Byte) override;
        string getHexaRepresentation() const;
    private:
        Word getRegisterAsWord() const;
};

#endif