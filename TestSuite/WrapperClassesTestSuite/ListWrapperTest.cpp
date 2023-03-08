#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "WrapperClasses/ListWrapper.h"

#include <iostream>
#include <initializer_list>

using std::cout;

/*Caveat: Can not test with a single parameter!*/
Class ListWrapperTest {
        template <class E, class T>
            using MonadCallBackType = E (ListWrapper<T>::*) (const T&);
    public:
        template <class T>
        static void testEmpty() {
            ListWrapper<T> list = createEmptyList<T>();
            
            Assert::equals(list.empty(), true, "testEmpty(): List should be empty!");
        }

        template <class... Ts, class T>
        static void testNonEmpty(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            Assert::unequals(list.empty(), true, "testNonEmpty(): List should be non-empty");
        }

        template <class... Ts, class T>
        static void testGetSize(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            Assert::equals(list.getSize(), sizeof...(rest) + 1, "testGetSize(): List's size should equal 5");
        }

        template <class... Ts, class T>
        static void testPushBack(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            assertListEqualsUsingBracketIndexing(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsUsingForEach(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using for each");
        }
        
        template <class... Ts, class T>
        static void testPushFront(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElementsReversed({first, rest...});

            assertListEqualsReverseUsingBracketIndexing(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsReverseUsingForEach(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using for each");
        }

        template <class... Ts, class T>
        static void testOnePopBack(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElementsReversed({first, rest...});
            list.popBack();

            assertListEqualsReverseUsingBracketIndexing(list, {rest...}, "testOnePopBack(): List does not equal the passed-in elements using bracket indexing");
        }

        template <class... Ts, class T>
        static void testOnePopFront(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});
            list.popFront();

            assertListEqualsUsingBracketIndexing(list, {rest...}, "testOnePopFront(): List does not equal the passed-in elements using bracket indexing");
        }

        template <class...Ts, class T>
        static void testCopyConstructor(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            ListWrapper<T> list2(list);
            ListWrapper<T> list3{list};
            ListWrapper<T> list4 = list;

            const string fail_message = "testCopyConstructor(): The copied list isn't the same as the original";
            assertListEqualsUsingForEach(list2, {first, rest...}, fail_message);
            assertListEqualsUsingBracketIndexing(list3, {first, rest...}, fail_message);
            assertListEqualsUsingForEach(list4, {first, rest...}, fail_message);
        }
        
        template <class...Ts, class T>
        static void testMoveConstructor(const T& first, const Ts&... rest) {
            Assert::parameterTypesAllSame<T, Ts...>();

            const string fail_list_not_same_message = "testMoveConstructor(): The moved list isn't the same as the original";
            const string fail_not_empty_message = "testMoveConstructor(): The moved-out list should be empty";
            
            ListWrapper<T> list = createListWithElements({first, rest...});

            ListWrapper<T> list2(std::move(list));
            assertListEqualsUsingForEach(list2, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list.empty(), true, fail_not_empty_message);

            ListWrapper<T> list3{std::move(list2)};
            assertListEqualsUsingForEach(list3, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list2.empty(), true, fail_not_empty_message);

            ListWrapper<T> list4 = std::move(list3);
            assertListEqualsUsingBracketIndexing(list4, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list3.empty(), true, fail_not_empty_message);
        }
    private:
        template <class T>
        static ListWrapper<T> createEmptyList() {
            return ListWrapper<T>();
        }

        template <class T>
        static ListWrapper<T> createListWithElementsReversed(std::initializer_list<T> elemList) {
            ListWrapper<T> list = createEmptyList<T>();
            forEach(list, &ListWrapper<T>::pushFront, elemList);
            return list;
        }

        template <class T>
        static ListWrapper<T> createListWithElements(std::initializer_list<T> elemList) {
            ListWrapper<T> list = createEmptyList<T>();
            forEach(list, &ListWrapper<T>::pushBack, elemList);
            return list;
        }

        template <class T, class E>
        static void forEach(ListWrapper<T>& list, MonadCallBackType<E, T> callback, std::initializer_list<T> elemList) {
            for (const T& elem: elemList)
                (list.*callback)(elem);
        }

        template <class T>
        static void assertListEqualsUsingBracketIndexing(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i)
                Assert::equals(data(elemList)[i], list[i], fail_message);
        }
        
        template <class T>
        static void assertListEqualsUsingForEach(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            int i = 0;
            for (const T& elem: list)
                Assert::equals(elem, data(elemList)[i++], fail_message);
        }

        template <class T>
        static void assertListEqualsReverseUsingBracketIndexing(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i) {
                int iReversed = list.getSize() - i - 1;
                Assert::equals(data(elemList)[i], list[iReversed], fail_message);
            }
        }

        template <class T>
        static void assertListEqualsReverseUsingForEach(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            int i = list.getSize() - 1;
            for (const T& elem: list)
                Assert::equals(elem, data(elemList)[i--], fail_message);
        }
};

int main() {
    string one = "one";
    string two = "two";
    string three = "three";
    string four = "four";

    ListWrapperTest::testEmpty<int>();
    ListWrapperTest::testEmpty<char>();
    ListWrapperTest::testEmpty<string>();
    ListWrapperTest::testEmpty<float>();

    ListWrapperTest::testNonEmpty<int>(1, 2);
    ListWrapperTest::testNonEmpty<float>(4.0f, 2.3f);

    ListWrapperTest::testGetSize<int>(1, 2, 3, 4, 5);
    ListWrapperTest::testGetSize<int>(1, 2);
    ListWrapperTest::testGetSize<string>(one, two, three, four);

    ListWrapperTest::testPushBack(1, 2, 3, 4, 5);
    ListWrapperTest::testPushBack(one, two, three, four);
    ListWrapperTest::testPushBack(4.0f, 2.0f, 8.6f);

    ListWrapperTest::testPushFront(4.0f, 2.0f, 3.4f);
    ListWrapperTest::testPushFront(1, 2, 3, 4, 5);
    ListWrapperTest::testPushFront(one, two, three, four);

    ListWrapperTest::testOnePopBack(1, 2, 3, 4, 5);
    ListWrapperTest::testOnePopBack(4.0f, 2.0f, 3.9f);
    ListWrapperTest::testOnePopBack(one, two, three);

    ListWrapperTest::testOnePopFront(1, 2, 3, 4, 5);
    ListWrapperTest::testOnePopFront(4.0f, 2.0f, 3.9f);
    ListWrapperTest::testOnePopFront(one, two, three);

    ListWrapperTest::testCopyConstructor(1, 2, 3, 4, 5);
    ListWrapperTest::testCopyConstructor(one, one, one);

    ListWrapperTest::testMoveConstructor(1, 2, 3, 4, 5);
    ListWrapperTest::testMoveConstructor(one, one, one);
}