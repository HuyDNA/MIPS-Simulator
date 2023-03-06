#ifndef _PARAMETER_TAG_MIPS_SIMULATOR_
#define _PARAMETER_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "TagComponents/TagType.h"
#include "TagComponents/DataTag.h"

Interface ParameterTag: public DataTag {
    public:
        virtual TagType type() const override = 0;
};

#endif