#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "AssemblerComponents/LexicalAnalyzer.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <string>

using std::string;
using std::pair;

void testGenerateSentenceList(const string&, const ListWrapper<string>&);

ListWrapper<string> createListWrapperFromStringList(const std::initializer_list<string>);

/*TODO: Refactor these into separate test functions*/
int main() {
    /*Basic misc tests*/
    const string programText1 = ".text\nadd $s1, $s2, $s3\nsub $s2, $s3, $s4\n";
    const ListWrapper<string> groundTruth1 = createListWrapperFromStringList({".text", "add $s1, $s2, $s3", "sub $s2, $s3, $s4"});
    testGenerateSentenceList(programText1, groundTruth1);

    const string programText2 = ".text\n add $s2, $s3, $t2\n  label1: sub $s2, $t2, $t3";
    const ListWrapper<string> groundTruth2 = createListWrapperFromStringList({".text", "add $s2, $s3, $t2", "label1: sub $s2, $t2, $t3"});
    testGenerateSentenceList(programText2, groundTruth2);

    /*Many leading, trailing and contiguous whitespaces*/
    const string programText3 = "  \n  .data\n   \n add $s2,   $s3,    $s5  \n     label2  : lw $s2, 8($3)    \n   ";
    const ListWrapper<string> groundTruth3 = createListWrapperFromStringList({".data", "add $s2, $s3, $s5", "label2 : lw $s2, 8($3)"});
    testGenerateSentenceList(programText3, groundTruth3);
    
    /*Many newlines*/
    const string programText4 = ".data\n\n\n\n   \n .text \n label3:\n jal label3  \nlabel2: lw $s2, 8($3)     ";
    const ListWrapper<string> groundTruth4 = createListWrapperFromStringList({".data", ".text", "label3: jal label3", "label2: lw $s2, 8($3)"});
    testGenerateSentenceList(programText4, groundTruth4);

    /*One newline no space*/
    const string programText5 = "label1:\njr $s2";
    const ListWrapper<string> groundTruth5 = createListWrapperFromStringList({"label1: jr $s2"});
    testGenerateSentenceList(programText5, groundTruth5);

    /*No space after colon*/
    const string programText6 = "label2:jr $s3";
    const ListWrapper<string> groundTruth6 = createListWrapperFromStringList({"label2:jr $s3"});
    testGenerateSentenceList(programText6, groundTruth6);

    /*Many adjacent labels*/
    const string programText7 = "label1: label2:\nlabel3: jal label1";
    const ListWrapper<string> groundTruth7 = createListWrapperFromStringList({"label1: label2: label3: jal label1"});
    testGenerateSentenceList(programText7, groundTruth7);
}

void testGenerateSentenceList(const string& programText, const ListWrapper<string>& groundTruth) {
    LexicalAnalyzer lexer(programText);
    const ListWrapper<string> output = lexer.generateSentenceList();
    
    Assert::equals(output.getSize(), groundTruth.getSize(), "testGenerateSentenceList(): generated output's size is not the same as ground truth's");
    
    for (long long i = 0; i < output.getSize(); ++i) {
       const string failure_message = string("textGenerateSentenceList(): generated output is not the same as ground truth.")
                                    + "\nExpected: " + groundTruth[i] + "\nGot     : " + output[i];
       Assert::equals(output[i], groundTruth[i], failure_message);
    }
}

ListWrapper<string> createListWrapperFromStringList(const std::initializer_list<string> stringList) {
    ListWrapper<string> stringListWrapper{};

    for (const auto& s: stringList)
        stringListWrapper.pushBack(s);
    
    return stringListWrapper;
}