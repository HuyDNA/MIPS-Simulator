#ifndef _LABEL_TAG_MIPS_SIMULATOR_
#define _LABEL_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/Tag.h"
#include "TagComponents/TagType.h"

#include <string>
#include <memory>

using std::string;

Class LabelTag: public Tag {
    public:
        LabelTag(const string& value): value { value } {
            
        }
        const string value;
        virtual TagType type() const override {
            return TagType::LABEL;
        }
};

using LabelTagPointer = std::shared_ptr<LabelTag>;

#endif