#ifndef _DIRECTIVE_TAG_MIPS_SIMULATOR_
#define _DIRECTIVE_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/DataTag.h"

#include <string>
#include <memory>

using std::string;

Class DirectiveTag: public DataTag {
    public:
        DirectiveTag(const string& value): value { value } {

        }
        const string value;
        virtual TagType type() const override {
            return TagType::DIRECTIVE;
        }
};

using DirectiveTagPointer = std::shared_ptr<DirectiveTag>;

#endif