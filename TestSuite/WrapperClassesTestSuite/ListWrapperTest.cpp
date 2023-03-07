#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "WrapperClasses/ListWrapper.h"

#include <iostream>
#include <initializer_list>

using std::cout;

template <class T1, class T2, class... RestTs>
constexpr bool is_all_same = std::is_same_v<T1, T2> && (sizeof...(RestTs) == 0 || is_all_same<T2, RestTs...>);

/*Caveat: Can not test with a single parameter!*/
Class ListWrapperTest {
        template <class E>
            using forEachCallBackType = E (ListWrapper<int>::*) (const int&);
    public:
        template <class T>
        static void testEmpty() {
            ListWrapper<T> list = createEmptyList<T>();
            
            Assert::equals(list.empty(), true, "testEmpty(): List should be empty!");
        }

        template <class... Ts, class T>
        static void testNonEmpty(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            Assert::unequals(list.empty(), true, "testNonEmpty(): List should be non-empty");
        }

        template <class... Ts, class T>
        static void testGetSize(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            Assert::equals(list.getSize(), sizeof... elements, "testGetSize(): List's size should equal 5");
        }

        template <class... Ts, class T>
        static void testPushBack(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});

            assertListEqualsUsingBracketIndexing(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsUsingForEach(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using for each");
        }
        
        template <class... Ts, class T>
        static void testPushFront(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElementsReversed({first, rest...});

            assertListEqualsReverseUsingBracketIndexing(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsReverseUsingForEach(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using for each");
        }

        template <class... Ts, class T>
        static void testOnePopBack(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElementsReversed(first, {first, rest...});
            list.popBack();

            assertListEqualsReverseUsingBracketIndexing(list, {first, rest...}, "testOnePopBack(): List does not equal the passed-in elements using bracket indexing");
        }

        template <class... Ts, class T>
        static void testOnePopFront(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            ListWrapper<T> list = createListWithElements({first, rest...});
            list.popFront();

            assertListEqualsUsingBracketIndexing(list, {first, rest...}, "testOnePopFront(): List does not equal the passed-in elements using bracket indexing");
        }

    private:
        template <class... Ts>
        static consteval void checkParameterTypesAllSame() {
            static_assert(is_all_same<Ts...>, "All parameters are not of the same type. Check your tests.");
        }

        template <class T>
        static ListWrapper<T> createEmptyList() {
            return ListWrapper<T>();
        }

        template <class T>
        static ListWrapper<T> createListWithElementsReversed(std::initializer_list<T> elemList) {
            ListWrapper<T> list = createEmptyList<T>();
            forEach(list, ListWrapper<T>::pushBack, elemList);
            return list;
        }

        template <class T>
        static ListWrapper<T> createListWithElements(std::initializer_list<T> elemList) {
            ListWrapper<T> list = createEmptyList<T>();
            forEach(list, ListWrapper<T>::pushBack, elemList);
            return list;
        }

        template <class T, class E>
        static void forEach(const ListWrapper<T>& list, forEachCallBackType<E> callback, std::initializer_list<T> elemList) {
            for (const T& elem: elemList)
                list.*callback(elem);
        }

        template <class T>
        static void assertListEqualsUsingBracketIndexing(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i)
                Assert::equals(elemList[i], list[i], fail_message);
        }
        
        template <class T>
        static void assertListEqualsUsingForEach(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            int i = 0;
            for (const T& elem: list)
                Assert::equals(elem, elemList[i++], fail_message);
        }

        template <class T>
        static void assertListEqualsReverseUsingBracketIndexing(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i) {
                int iReversed = list.getSize() - i - 1;
                Assert::equals(elemList[i], list[iReversed], fail_message);
            }
        }

        template <class T>
        static void assertListEqualsReverseUsingForEach(const ListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            int i = list.getSize() - 1;
            for (const T& elem: list)
                Assert::equals(elem, elemList[i--], fail_message);
        }
};

int main() {
    ListWrapperTest::testEmpty<int>();
    ListWrapperTest::testEmpty<char>();
    ListWrapperTest::testEmpty<string>();
    ListWrapperTest::testEmpty<float>();

    ListWrapperTest::testNonEmpty<int>(1, 2);
    ListWrapperTest::testNonEmpty<float>(4.0, 2.3);

    ListWrapperTest::testGetSize<int>(1, 2, 3, 4, 5);
    ListWrapperTest::testGetSize<int>(1, 2);
    ListWrapperTest::testGetSize<string>("one", "two", "three", "four");

    ListWrapperTest::testPushBack(1, 2, 3, 4, 5);
    ListWrapperTest::testPushBack("one", "two", "three");
    ListWrapperTest::testPushBack(4.0, 2.0, 8.6);

    ListWrapperTest::testPushFront(4.0, 2.0, 3.4);
    ListWrapperTest::testPushFront(1, 2, 3, 4, 5);
    ListWrapperTest::testPushFront("one", "two", "three");

    ListWrapperTest::testOnePopBack(1, 2, 3, 4, 5);
    ListWrapperTest::testOnePopBack(4.0, 2.0, 3.9);
    ListWrapperTest::testOnePopBack("one", "two", "three");

    ListWrapperTest::testOnePopFront(1, 2, 3, 4, 5);
    ListWrapperTest::testOnePopFront(4.0, 2.0, 3.9);
    ListWrapperTest::testOnePopFront"one", "two", "three");
}