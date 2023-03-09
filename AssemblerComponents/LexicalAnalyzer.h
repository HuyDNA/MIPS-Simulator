#ifndef _LEXICAL_ANALYZER_MIPS_SIMULATOR_
#define _LEXICAL_ANALYZER_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include "WrapperClasses/ListWrapper.h"

#include <string>

using std::string;

Class LexicalAnalyzer {
    private:
        const string programText;
        std::size_t programTextIterator;
    public:
        LexicalAnalyzer(const string&);

        LexicalAnalyzer(const LexicalAnalyzer&) = delete;
        LexicalAnalyzer& operator=(const LexicalAnalyzer&) = delete;
        ~LexicalAnalyzer() = default;

        ListWrapper<string> generateSentenceList();
    private:
        string extractNextSentence();
};

#endif