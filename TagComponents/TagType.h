#ifndef _TAG_TYPE_MIPS_SIMULATOR_
#define _TAG_TYPE_MIPS_SIMULATOR_

enum class TagType {
    INSTRUCTION,
    REGISTER,
    IMMEDIATE,
    DIRECTIVE,
    INTEGER,
    BYTE,
    LABEL,
};

#endif