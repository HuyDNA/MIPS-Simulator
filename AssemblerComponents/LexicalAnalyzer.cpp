#include "visual_class_macros.h"

#include "AssemblerComponents/LexicalAnalyzer.h"

#include "WrapperClasses/ListWrapper.h"

#include "UtilityClasses/StringNormalizer.h"

#include <iostream>
#include <string>
#include <memory>

using std::string;

LexicalAnalyzer::LexicalAnalyzer(const string& program): 
    programText{program},
    programTextIterator{0} {

}

ListWrapper<string> LexicalAnalyzer::generateSentenceList() {
    ListWrapper<string> result;

    string sentence;
    while ((sentence = extractNextSentence()) != "") {
        result.pushBack(sentence);
    }
    
    return result;
}

string LexicalAnalyzer::extractNextSentence() {
    if (programText[programTextIterator] == '\0')
        return "";

    const std::size_t oldProgramTextIterator = programTextIterator;

    bool colonLast = false;
    bool blankLine = true;

    const auto performOnCurrentChar = [&colonLast, &blankLine, this](char c) -> bool {
        if (c == '\0')
            return false;

        ++programTextIterator;

        if (c == '\n' || c == '\r')
            return (colonLast || blankLine);
    
        if (c == ':')
            return (colonLast = true);

        if (c == ' ' || c == '\t')
            return true;

        colonLast = false;
        blankLine = false;
        return true;
    };

    while (true) {
        char currentChar = programText[programTextIterator];

        const bool shouldContinue = performOnCurrentChar(currentChar);
        if (!shouldContinue)
            break;
    }
    
    const string rawProgramSentence = programText.substr(oldProgramTextIterator, programTextIterator - oldProgramTextIterator);
    
    return StringNormalizer::spaceCollapse(StringNormalizer::trim(rawProgramSentence));
}