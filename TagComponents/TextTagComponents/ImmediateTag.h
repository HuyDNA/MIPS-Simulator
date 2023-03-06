#ifndef _IMMEDIATE_TAG_MIPS_SIMULATOR_
#define _IMMEDIATE_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/TextTag.h"

Class ImmediateTag: public TextTag {
    public:
        const int value;
        virtual TagType type() const override {
            return TagType::IMMEDIATE;
        }
};

#endif