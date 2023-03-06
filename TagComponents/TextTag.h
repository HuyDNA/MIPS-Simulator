#ifndef _TEXT_TAG_MIPS_SIMULATOR_
#define _TEXT_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/Tag.h"
#include "TagComponents/TagType.h"

Interface TextTag: public Tag {
    public:
        virtual TagType type() const override = 0;
};

#endif