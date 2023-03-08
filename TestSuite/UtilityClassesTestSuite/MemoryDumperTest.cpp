#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "MemoryUnitStructs/Byte.h"
#include "MemoryUnitStructs/Word.h"

#include "UtilityClasses/MemoryDumper.h"

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <string>

using std::string;

void testDump(const Word&, const string&);

int main() {
    testDump({Byte(0), Byte(0), Byte(0), Byte(0)}, "0x00000000");
    testDump({Byte(1), Byte(2), Byte(3), Byte(4)}, "0x01020304");
    testDump({Byte{10}, Byte{17}, Byte{20}, Byte{13}}, "0x0a11140d");
    testDump({Byte{255}, Byte{254}, Byte{20}, Byte{23}}, "0xfffe1417");
    testDump({Byte{63}, Byte{64}, Byte{127}, Byte{128}}, "0x3f407f80");
    testDump({Byte{70}, Byte{67}, Byte{68}, Byte{69}}, "0x46434445");
}

void testDump(const Word& word, const string& hexaRepresentation) {
    const string dumpResult = MemoryDumper::dumpWordInHexa(word);
    const string fail_message = "testDump(): should be " + hexaRepresentation + " instead of" + dumpResult;
    Assert::equals(dumpResult, hexaRepresentation, fail_message);
}