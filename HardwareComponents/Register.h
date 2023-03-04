#ifndef _REGISTER_MIPS_SIMULATOR_
#define _REGISTER_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "ContiguousMemoryHardware.h"
#include "Register.h"
#include "../MemoryUnitStructs/Byte.h"
#include "../MemoryUnitStructs/Word.h"


#include <cstdint>
#include <string>

using std::string;
using address_t = std::uint_fast32_t;

Class Register {
    public:
        static constexpr int REGISTER_SIZE_IN_BYTES = 4;
    private:
        Byte byteArray[REGISTER_SIZE_IN_BYTES];
    public:
        Register();
        Register(const Register&);
        virtual ~Register();

        virtual Byte get(const address_t) const override;
        virtual void set(const address_t, const Byte) override;
        string getHexaRepresentation() const;
};

#endif