#ifndef _RAM_MIPS_SIMULATOR_
#define _RAM_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "HardwareComponents/ContiguousMemoryHardware.h"
#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include "WrapperClasses/BoundedListWrapper.h"

#include <array>
#include <cstdint>
#include <string>

using std::array;
using std::string;
using address_t = std::uint_fast32_t;

/*This class assumes that the heap is not used and merged to stack*/
Class RAM: public ContiguousMemoryHardware {
    public:
        static constexpr long long RAM_SIZE_IN_BYTES = 0x1'0000'0000; // 2^32
        static constexpr long long TEXT_SEGMENT_SIZE_IN_BYTES = 0x0fc0'0000;
        static constexpr long long DATA_SEGMENT_SIZE_IN_BYTES = 0x0000'8000;
        static constexpr long long STACK_SEGMENT_SIZE_IN_BYTES = 0x6FFF'7FFC;
        
        static constexpr long long TEXT_SEGMENT_START_ADDRESS = 0x0040'0000;
        static constexpr long long DATA_SEGMENT_START_ADDRESS = 0x1000'0000;
        static constexpr long long STACK_SEGMENT_START_ADDRESS = 0x1000'8000;
        
        static constexpr long long TEXT_SEGMENT_END_ADDRESS = 0x0fff'ffff;
        static constexpr long long DATA_SEGMENT_END_ADDRESS = 0x1000'7fff;
        static constexpr long long STACK_SEGMENT_END_ADDRESS = 0x7fff'fffb;
    private:
        BoundedListWrapper<Byte> textSegmentByteList{TEXT_SEGMENT_SIZE_IN_BYTES};
        BoundedListWrapper<Byte> dataSegmentByteList{DATA_SEGMENT_SIZE_IN_BYTES};
        BoundedListWrapper<Byte> stackSegmentByteReversedList{STACK_SEGMENT_SIZE_IN_BYTES}; 
            // the highest byte on the stack is stored at the lowest index 
            // this is due to the consideration that stack usually grows backwards
    public:
        RAM();
        RAM(const RAM&);
        RAM(RAM&&);
        virtual ~RAM() = default;
        RAM& operator=(const RAM&) = delete;
        RAM& operator=(RAM&&) = delete;

        virtual Byte get(const address_t) const override;
        virtual void set(const address_t, const Byte) override;

        /*format: 0x--------*/
        string getHexaRepresentationOfWordAtByteAddress(const address_t) const;
    private:
        Word getRAMWordAtByteAddress(const address_t) const;

        Byte getByteInTextSegment(const address_t) const;
        void setByteInTextSegment(const address_t, const Byte);
        
        Byte getByteInDataSegment(const address_t) const;
        void setByteInDataSegment(const address_t, const Byte);

        Byte getByteInStackSegment(const address_t) const;
        void setByteInStackSegment(const address_t, const Byte);
};

#endif