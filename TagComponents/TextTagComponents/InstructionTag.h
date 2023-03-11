#ifndef _INSTRUCTION_TAG_MIPS_SIMULATOR_
#define _INSTRUCTION_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "TagComponents/TagType.h"
#include "TagComponents/TextTag.h"

#include <string>
#include <memory>

using std::string;

Class InstructionTag: public TextTag {
    public:
        InstructionTag(const string& value): value { value } {

        }
        const string value;
        virtual TagType type() const override {
            return TagType::INSTRUCTION;
        }
};

using InstructionTagPointer = std::shared_ptr<InstructionTag>;

#endif