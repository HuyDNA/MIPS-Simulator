#ifndef _BYTE_TAG_MIPS_SIMULATOR_
#define _BYTE_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTagComponents/ParameterTag.h"

#include "WrapperClasses/ListWrapper.h"
#include "MemoryUnitStructs/Byte.h"

#include <memory>

Class ByteTag: public ParameterTag {
    public:
        ByteTag(const ListWrapper<Byte>& value): value { value } {

        }
        ByteTag(ListWrapper<Byte>&& value): value { std::move(value) } {

        }
        const ListWrapper<Byte> value;
        virtual TagType type() const override {
            return TagType::BYTE;
        }
};

using ByteTagPointer = std::shared_ptr<ByteTag>;

#endif