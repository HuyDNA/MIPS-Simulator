#ifndef _BYTE_TAG_MIPS_SIMULATOR_
#define _BYTE_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTagComponents/ParameterTag.h"

#include "WrapperClasses/ListWrapper.h"
#include "MemoryUnitStructs/Byte.h"

Class ByteTag: public ParameterTag {
    public:
        const ListWrapper<Byte> value;
        virtual TagType type() const override {
            return TagType::BYTE;
        }
};

#endif