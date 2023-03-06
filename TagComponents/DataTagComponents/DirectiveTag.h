#ifndef _DIRECTIVE_TAG_MIPS_SIMULATOR_
#define _DIRECTIVE_TAG_MIPS_SIMULATOR_

#include "../../visual_class_macros.h"
#include "TagType.h"
#include "../DataTag.h"

#include <string>

using std::string;

Class DirectiveTag: public DataTag {
    public:
        const string value;
        virtual TagType type() const override {
            return TagType::DIRECTIVE;
        }
};

#endif