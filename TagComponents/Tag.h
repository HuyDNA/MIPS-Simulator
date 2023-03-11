#ifndef _TAG_MIPS_SIMULATOR_
#define _TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "TagComponents/TagType.h"

#include <memory>

Interface Tag {
    public:
        virtual TagType type() const = 0;
};

using TagPointer = std::shared_ptr<Tag>;

#endif