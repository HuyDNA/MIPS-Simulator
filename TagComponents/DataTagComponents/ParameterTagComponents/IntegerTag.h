#ifndef _INTEGER_TAG_MIPS_SIMULATOR_
#define _INTEGER_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTagComponents/ParameterTag.h"
#include "WrapperClasses/ListWrapper.h"

Class IntegerTag: public ParameterTag {
    public:
        const ListWrapper<int> value;
        virtual TagType type() const override {
            return TagType::INTEGER;
        }
};

#endif