#ifndef _REGISTER_TAG_MIPS_SIMULATOR_
#define _REGISTER_TAG_MIPS_SIMULATOR_

#include "../../visual_class_macros.h"
#include "TagType.h"
#include "../TextTag.h"

Class RegisterTag: public TextTag {
    public:
        const int value;
        virtual TagType type() const override {
            return TagType::REGISTER;
        }
};

#endif