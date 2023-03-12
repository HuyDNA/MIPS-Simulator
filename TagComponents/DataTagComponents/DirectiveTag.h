#ifndef _DIRECTIVE_TAG_MIPS_SIMULATOR_
#define _DIRECTIVE_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTag.h"

#include <string>

using std::string;

Class DirectiveTag: public DataTag {
    public:
        const string value;
        DirectiveTag (string value) : value(value) {
            
        }
        virtual TagType type() const override {
            return TagType::DIRECTIVE;
        }
};

#endif