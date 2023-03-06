#ifndef _LABEL_TAG_MIPS_SIMULATOR_
#define _LABEL_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/Tag.h"
#include "TagComponents/TagType.h"

Class LabelTag: public Tag {
    public:
        virtual TagType type() const override {
            return TagType::LABEL;
        }
};

#endif