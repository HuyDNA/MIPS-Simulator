#ifndef _REGISTER_TAG_MIPS_SIMULATOR_
#define _REGISTER_TAG_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "TagComponents/TagType.h"
#include "TagComponents/TextTag.h"

#include <memory>

Class RegisterTag: public TextTag {
    public:
        RegisterTag(int value): value { value } {

        }
        const int value;
        virtual TagType type() const override {
            return TagType::REGISTER;
        }
};

using RegisterTagPointer = std::shared_ptr<RegisterTag>;

#endif