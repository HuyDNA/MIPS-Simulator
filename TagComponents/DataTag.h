#ifndef _DATA_TAG_MIPS_SIMULATOR_
#define _DATA_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/Tag.h"
#include "TagComponents/TagType.h"

#include <memory>

Interface DataTag: public Tag {
    public:
        virtual TagType type() const override = 0;
};

using DataTagPointer = std::shared_ptr<DataTag>;

#endif