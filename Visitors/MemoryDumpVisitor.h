#ifndef _MEMORY_DUMP_VISITOR_MIPS_SIMULATOR_
#define _MEMORY_DUMP_VISITOR_MIPS_SIMULATOR_

#include "visual_class_macros.h"
#include "Register.h"
#include "RAM.h"

#include <string>

using std::string;

Class MemoryDumpVisitor {
    public:
        string visit(const Register&) const;
        string visit(const RAM&) const;
};

#endif