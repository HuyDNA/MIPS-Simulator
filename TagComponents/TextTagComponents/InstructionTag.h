#ifndef _INSTRUCTION_TAG_MIPS_SIMULATOR_
#define _INSTRUCTION_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "TagComponents/TagType.h"
#include "TagComponents/TextTag.h"

#include <string>

using std::string;

Class InstructionTag: public TextTag {
    public:
        const string value;
        InstructionTag(string value) : value(value) {
            
        }
        virtual TagType type() const override {
            return TagType::INSTRUCTION;
        }
};

#endif