#ifndef _LABEL_TAG_MIPS_SIMULATOR_
#define _LABEL_TAG_MIPS_SIMULATOR_

#include "../visual_class_macros.h"
#include "Tag.h"
#include "TagType.h"

Interface LabelTag: public Tag {
    public:
        virtual TagType type() const override = 0;
};

#endif