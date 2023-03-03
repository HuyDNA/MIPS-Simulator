#ifndef _REGISTER_MIPS_SIMULATOR_
#define _REGISTER_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "ContiguousMemoryHardware.h"
#include "MemoryDumperVisitor.h"

#include <cstddef>
#include <cstdint>
#include <string>

using std::byte;
using std::string;
using address_t = std::uint_fast32_t;

Class Register {
    public:
        static constexpr int REGISTER_SIZE_IN_BYTES = 4;
    private:
        byte byteArray[REGISTER_SIZE_IN_BYTES];
    public:
        Register();
        Register(const Register&);
        virtual ~Register() override;

        virtual byte get(const address_t) const override;
        virtual void set(const address_t, const byte) override;
        virtual string acceptDumper(const MemoryDumperVisitor&) const override;
};

#endif