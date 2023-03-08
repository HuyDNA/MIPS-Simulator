#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "HardwareComponents/Register.h"

#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include "UtilityClasses/MemoryDumper.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <string>

using std::string;
using std::pair;

/*
    Caveats: Passed in addresses must be distinct
    TODO: Allow repeating addresses
*/
Class RegisterTest {
    public:
        static void testSetGet(const Word& word) {
            Register reg = createRegisterFromWord(word);
            
            assertRegisterEquals(reg, word, "testSetGet(): Created Register isn't the same as the passed-in Register");
        }

        static void testCopyConstructor(const Word& word) {
            Register reg = createRegisterFromWord(word);

            Register reg2 = reg;
            Register reg3(reg);
            Register reg4{reg};

            const string fail_message = "testCopyConstructor(): Copied Register isn't the same as the original";

            assertRegisterEquals(reg2, word, fail_message);
            assertRegisterEquals(reg3, word, fail_message);
            assertRegisterEquals(reg4, word, fail_message);
        }

        static void testMoveConstructor(const Word& word) {
            Register reg = createRegisterFromWord(word);

            const string fail_not_same_message = "testCopyConstructor(): Moved Register isn't the same as the passed-in Register";
            
            Register reg2 = std::move(reg); 
            assertRegisterEquals(reg2, word, fail_not_same_message);
            
            Register reg3(std::move(reg2));
            assertRegisterEquals(reg3, word, fail_not_same_message);

            Register reg4{std::move(reg3)};
            assertRegisterEquals(reg4, word, fail_not_same_message);
        }

        static void testDump(const Word& word) {
            Register reg = createRegisterFromWord(word);
            
            Assert::equals(reg.getHexaRepresentation(), MemoryDumper::dumpWordInHexa(word),
                            "testDump(): Wrong representation");
        }
    private:
        static Register createFreshRegister() {
            return Register();
        }

        static Register createRegisterFromWord(const Word& word) {
            Register reg = createFreshRegister();

            reg.set(0, word.byte1);
            reg.set(1, word.byte2);
            reg.set(2, word.byte3);
            reg.set(3, word.byte4);

            return reg;
        }

        static void assertRegisterEquals(const Register& reg, const Word& word, const string& fail_message) {
            Assert::equals(reg.get(0), word.byte1, fail_message);
            Assert::equals(reg.get(1), word.byte2, fail_message);
            Assert::equals(reg.get(2), word.byte3, fail_message);
            Assert::equals(reg.get(3), word.byte4, fail_message);
        }
};

int main() {
    Word word1 = {Byte{0}, Byte{1}, Byte{2}, Byte{3}};
    Word word2 = {Byte{4}, Byte{5}, Byte{6}, Byte{7}};
    Word word3 = {Byte{8}, Byte{9}, Byte{10}, Byte{11}};
    Word word4 = {Byte{12}, Byte{13}, Byte{14}, Byte{15}};

    RegisterTest::testSetGet(word1);
    RegisterTest::testSetGet(word2);
    RegisterTest::testSetGet(word3);
    RegisterTest::testSetGet(word4);

    RegisterTest::testCopyConstructor(word1);
    RegisterTest::testCopyConstructor(word2);
    RegisterTest::testCopyConstructor(word3);
    RegisterTest::testCopyConstructor(word4);

    RegisterTest::testMoveConstructor(word1);
    RegisterTest::testMoveConstructor(word2);
    RegisterTest::testMoveConstructor(word3);
    RegisterTest::testMoveConstructor(word4);

    RegisterTest::testDump(word1);
    RegisterTest::testDump(word2);
    RegisterTest::testDump(word3);
    RegisterTest::testDump(word4);
}