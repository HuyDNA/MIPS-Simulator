#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "HardwareComponents/RAM.h"

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
Class RAMTest {
    using AddressValuePairList = std::initializer_list<pair<long long, Byte>>;
    using AddressWordPairList = std::initializer_list<pair<long long, Word>>;
    public:
        static void testSetGet(const AddressValuePairList& pairsOfAddressValue) {
            RAM ram = createRAMFromAddressValuePair(pairsOfAddressValue);
            
            assertRAMEquals(ram, pairsOfAddressValue, "testSetGet(): Created RAM isn't the same as the passed-in RAM");
        }

        static void testCopyConstructor(const AddressValuePairList& pairsOfAddressValue) {
            RAM ram = createRAMFromAddressValuePair(pairsOfAddressValue);

            RAM ram2 = ram;
            RAM ram3(ram);
            RAM ram4{ram};

            const string fail_message = "testCopyConstructor(): Copied RAM isn't the same as the original";

            assertRAMEquals(ram2, pairsOfAddressValue, fail_message);
            assertRAMEquals(ram3, pairsOfAddressValue, fail_message);
            assertRAMEquals(ram4, pairsOfAddressValue, fail_message);
        }

        static void testMoveConstructor(const AddressValuePairList& pairsOfAddressValue) {
            RAM ram = createRAMFromAddressValuePair(pairsOfAddressValue);

            const string fail_not_same_message = "testCopyConstructor(): Moved RAM isn't the same as the passed-in RAM";
            
            RAM ram2 = std::move(ram); 
            assertRAMEquals(ram2, pairsOfAddressValue, fail_not_same_message);
            
            RAM ram3(std::move(ram2));
            assertRAMEquals(ram3, pairsOfAddressValue, fail_not_same_message);

            RAM ram4{std::move(ram3)};
            assertRAMEquals(ram4, pairsOfAddressValue, fail_not_same_message);
        }

        static void testDump(const AddressWordPairList& pairsOfAddressWord) {
            RAM ram = createRAMFromAddressWordPair(pairsOfAddressWord);
            
            for (const auto& [address, word]: pairsOfAddressWord)
                Assert::equals(ram.getHexaRepresentationOfWordAtByteAddress(address), MemoryDumper::dumpWordInHexa(word),
                               "testDump(): Wrong representation");
        }
    private:
        static RAM createFreshRAM() {
            return RAM();
        }

        static RAM createRAMFromAddressValuePair(const AddressValuePairList& pairsOfAddressValue) {
            RAM ram = createFreshRAM();

            for (const auto& [address, value]: pairsOfAddressValue)
                ram.set(address, value);

            return ram;
        }

        static RAM createRAMFromAddressWordPair(const AddressWordPairList& pairsOfAddressWord) {
            RAM ram = createFreshRAM();

            for (const auto& [address, word]: pairsOfAddressWord) 
                if (address % 4 != 0)
                    throw std::runtime_error("createRAMFromAddressWordPair(): Word address should be divisible by 4");
                else {
                ram.set(address, word.byte1);
                ram.set(address + 1, word.byte2);
                ram.set(address + 2, word.byte3);
                ram.set(address + 3, word.byte4);
            }

            return ram;
        }

        static void assertRAMEquals(const RAM& ram, const AddressValuePairList& pairsOfAddressValue, const string& fail_message) {
            for (const auto& [address, value]: pairsOfAddressValue)
                Assert::equals(ram.get(address), value, fail_message);
        }
};

int main() {
    std::initializer_list<pair<long long, Byte>> pairsOfAddressValue = {
                                                                        {0x1000'0000, Byte(15)}, 
                                                                        {0x1000'0001, Byte(12)}, 
                                                                        {0x1000'0002, Byte(13)}, 
                                                                        {0x0040'0003, Byte(1)}, 
                                                                        {0x7fff'fffb, Byte(7)},
                                                                        {0x0040'0007, Byte(5)},
                                                                       };
    RAMTest::testSetGet(pairsOfAddressValue);
    RAMTest::testCopyConstructor(pairsOfAddressValue);
    RAMTest::testMoveConstructor(pairsOfAddressValue);

    std::initializer_list<pair<long long, Word>> pairsOfAddressWord = {
                                                                       {0x1000'0000, {Byte(13), Byte(12), Byte(11), Byte(10)}}, // in data segment
                                                                       //{0x1000'8000, {Byte{12}, Byte{10}, Byte{1}, Byte{2}}}, // in stack segment but the other end
                                                                       {0x0040'0040, {Byte(5), Byte{2}, Byte{3}, {Byte{5}}}},   // in text segment
                                                                       {0x7fff'fff0, {Byte{10}, Byte{12}, Byte{3}, Byte{4}}},   // in stack segment
                                                                      };
    RAMTest::testDump(pairsOfAddressWord);
}
