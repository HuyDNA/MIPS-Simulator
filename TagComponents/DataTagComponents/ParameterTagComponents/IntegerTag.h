#ifndef _INTEGER_TAG_MIPS_SIMULATOR_
#define _INTEGER_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTagComponents/ParameterTag.h"
#include "WrapperClasses/ListWrapper.h"

#include <memory>

Class IntegerTag: public ParameterTag {
    public:
        IntegerTag(const ListWrapper<long long>& value): value { value } {

        }
        IntegerTag(ListWrapper<long long>&& value): value { std::move(value) } {

        }
        const ListWrapper<long long> value;
        virtual TagType type() const override {
            return TagType::INTEGER;
        }
};

#endif