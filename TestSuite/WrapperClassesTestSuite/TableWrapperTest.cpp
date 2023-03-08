#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "WrapperClasses/TableWrapper.h"

#include <iostream>
#include <initializer_list>
#include <utility>
#include <memory>

using std::cout;
using std::pair;

/*
  Caveats: Make sure all keys are distinct.
  TODO: Allow duplicate keys
*/
Class TableWrapperTest {
    public:
        template <class K, class T>
        static void testEmpty() {
            TableWrapper<K, T> table = createEmptyTable<K, T>();

            Assert::equals(table.empty(), true, "testEmpty(): Table should be empty here");
        }  

        template <class K, class T>
        static void testSetGet(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            assertTableEquals(table, pairsOfKeyValue, "testSetGet(): Table constructed does not equal the passed-in element list");            
        }

        template <class K, class T>
        static void testBracketIndexing(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            for (const auto& [key, value]: pairsOfKeyValue)
                Assert::equals(table[key], value, "testBracketIndexing(): Unequal value indexed vs passed-in");
        }

        template <class K, class T>
        static void testGetSize(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            Assert::equals(table.getSize(), pairsOfKeyValue.size(), "testGetSize(): Table's size is not the same as the number of passed-in elements");
        }

        template <class K, class T>
        static void testErase(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            for (const auto& [key, _]: pairsOfKeyValue)
                table.erase(key);
            
            Assert::equals(table.empty(), true, "testErase(): Table should be empty after erasing all of its elements");
        }

        template <class K, class T>
        static void testCopyConstructor(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            TableWrapper<K, T> table2(table);
            TableWrapper<K, T> table3{table};
            TableWrapper<K, T> table4 = table;

            const string fail_message = "testCopyConstructor(): The copied table should be the same as the original";
            assertTableEquals(table2, pairsOfKeyValue, fail_message);
            assertTableEquals(table3, pairsOfKeyValue, fail_message);
            assertTableEquals(table4, pairsOfKeyValue, fail_message);
        }

        template <class K, class T>
        static void testMoveConstructor(const std::initializer_list<pair<K, T>> pairsOfKeyValue) {
            TableWrapper<K, T> table = createTableFromKeyValuePairs<K, T>(pairsOfKeyValue);

            const string fail_not_same_message = "testMoveConstructor(): The moved table should be the same as the passed-in parameters";
            const string fail_not_empty_message = "testMoveConstructor(): The moved-out table should be empty";

            TableWrapper<K, T> table2(std::move(table));
            assertTableEquals(table2, pairsOfKeyValue, fail_not_same_message);
            Assert::equals(table.empty(), true, fail_not_empty_message);

            TableWrapper<K, T> table3{std::move(table2)};
            assertTableEquals(table3, pairsOfKeyValue, fail_not_same_message);
            Assert::equals(table2.empty(), true, fail_not_empty_message);

            TableWrapper<K, T> table4 = std::move(table3);
            assertTableEquals(table4, pairsOfKeyValue, fail_not_same_message);
            Assert::equals(table3.empty(), true, fail_not_empty_message);
        }
    private:
        template <class K, class T>
        static TableWrapper<K, T> createEmptyTable() {
            return {};
        }

        template <class K, class T>
        static TableWrapper<K, T> createTableFromKeyValuePairs(const std::initializer_list<pair<K, T>>& pairsOfKeyValue) {
            TableWrapper<K, T> table = createEmptyTable<K, T>();
            for (const auto& [key, value]:  pairsOfKeyValue)
                table.set(key, value);
            return table;
        }

        template <class K, class T>
        static void assertTableEquals(const TableWrapper<K, T>& table, const std::initializer_list<pair<K, T>>& pairsOfKeyValue, const string& fail_message) {
            for (const auto& [key, value]: pairsOfKeyValue)
                Assert::equals(table.get(key), value, fail_message);
        }
};

int main() {
    const std::initializer_list<pair<string, int>> pointSummary = {{"anhuy", 10}, {"vu", 0}, {"amyra", 10}, {"nguyenvu", 10}};
    const std::initializer_list<pair<int, int>> birthDates = {{8, 6}, {6, 6}, {1, 1}, {25, 12}};
    const std::initializer_list<pair<int, string>> ageOrder = {{1, "nguyenvu"}, {2, "amyra"}, {3, "anhuy"}, {4, "vu"}};

    TableWrapperTest::testEmpty<string, int>();
    TableWrapperTest::testEmpty<int, int>();
    TableWrapperTest::testEmpty<int, string>();

    TableWrapperTest::testGetSize(pointSummary);
    TableWrapperTest::testGetSize(birthDates);
    TableWrapperTest::testGetSize(ageOrder);

    TableWrapperTest::testSetGet(pointSummary);
    TableWrapperTest::testSetGet(birthDates);
    TableWrapperTest::testSetGet(ageOrder);
    
    TableWrapperTest::testErase(pointSummary);
    TableWrapperTest::testErase(birthDates);
    TableWrapperTest::testErase(ageOrder);
 
    TableWrapperTest::testCopyConstructor(pointSummary);
    TableWrapperTest::testCopyConstructor(birthDates);
    TableWrapperTest::testCopyConstructor(ageOrder);

    TableWrapperTest::testMoveConstructor(pointSummary);
    TableWrapperTest::testMoveConstructor(birthDates);
    TableWrapperTest::testMoveConstructor(ageOrder);
    
    TableWrapperTest::testBracketIndexing(pointSummary);
    TableWrapperTest::testBracketIndexing(birthDates);
    TableWrapperTest::testBracketIndexing(ageOrder);
}