#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "WrapperClasses/BoundedListWrapper.h"

#include <iostream>
#include <initializer_list>

using std::cout;

template <class T1, class T2, class... RestTs>
constexpr bool is_all_same = std::is_same_v<T1, T2> && is_all_same<T2, RestTs...>;;

template <class T1, class T2>
constexpr bool is_all_same<T1, T2> = std::is_same_v<T1, T2>; 

constexpr int DEFAULT_CAPACITY = 100;

/*Caveat: Can not test with a single parameter!*/
Class BoundedListWrapperTest {
        template <class E, class T>
            using MonadCallBackType = E (BoundedListWrapper<T>::*) (const T&);
    public:
        template <int capacity = DEFAULT_CAPACITY, class T>
        static void testEmpty() {
            BoundedListWrapper<T> list = createEmptyList<capacity, T>();
            
            Assert::equals(list.empty(), true, "testEmpty(): List should be empty!");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testNonEmpty(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElements<capacity>({first, rest...});

            Assert::unequals(list.empty(), true, "testNonEmpty(): List should be non-empty");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testGetSize(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElements<capacity>({first, rest...});

            Assert::equals(list.getSize(), sizeof...(rest) + 1, "testGetSize(): List's size should equal 5");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testPushBack(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElements<capacity>({first, rest...});

            assertListEqualsUsingBracketIndexing(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsUsingForEach(list, {first, rest...}, "testPushBack(): List does not equal the passed-in elements using for each");
        }
        
        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testPushFront(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElementsReversed<capacity>({first, rest...});

            assertListEqualsReverseUsingBracketIndexing(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using bracket indexing");
            assertListEqualsReverseUsingForEach(list, {first, rest...}, "testPushFront(): List does not equal the passed-in elements using for each");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testOnePopBack(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElementsReversed<capacity>({first, rest...});
            list.popBack();

            assertListEqualsReverseUsingBracketIndexing(list, {rest...}, "testOnePopBack(): List does not equal the passed-in elements using bracket indexing");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testOnePopFront(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElements<capacity>({first, rest...});
            list.popFront();

            assertListEqualsUsingBracketIndexing(list, {rest...}, "testOnePopFront(): List does not equal the passed-in elements using bracket indexing");
        }

        template <int capacity = DEFAULT_CAPACITY, class... Ts, class T>
        static void testPushOutOfCapacity(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            if constexpr (capacity >= sizeof... (Ts))
                throw std::runtime_error{"testPushOutOfCapacity(): Capacity should be less than the number of passed-in elements"};
            
            bool errorOccured = false;

            try {
                createListWithElements({first, ...rest});
                createListWithElementsReversed({first, ...rest});
            }
            catch (const std::exception& e) {
                errorOccured = true;
                std::cout << "testPushOutOfCapacity(): \"" << e.what() << "\"" << std::endl;
            }

            Assert::equals(errorOccured, true, "testPushOutOfCapacity(): An error should occur here");
        }

        template <class...Ts, class T>
        static void testCopyConstructor(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            BoundedListWrapper<T> list = createListWithElements({first, rest...});

            BoundedListWrapper<T> list2(list);
            BoundedListWrapper<T> list3{list};
            BoundedListWrapper<T> list4 = list;

            const string fail_message = "testCopyConstructor(): The copied list isn't the same as the original";
            assertListEqualsUsingForEach(list2, {first, rest...}, fail_message);
            assertListEqualsUsingBracketIndexing(list3, {first, rest...}, fail_message);
            assertListEqualsUsingForEach(list4, {first, rest...}, fail_message);
        }
        
        template <class...Ts, class T>
        static void testMoveConstructor(const T& first, const Ts&... rest) {
            checkParameterTypesAllSame<T, Ts...>();

            const string fail_list_not_same_message = "testMoveConstructor(): The moved list isn't the same as the original";
            const string fail_not_empty_message = "testMoveConstructor(): The moved-out list should be empty";
            
            BoundedListWrapper<T> list = createListWithElements({first, rest...});

            BoundedListWrapper<T> list2(std::move(list));
            assertListEqualsUsingForEach(list2, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list.empty(), true, fail_not_empty_message);

            BoundedListWrapper<T> list3{std::move(list2)};
            assertListEqualsUsingForEach(list3, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list2.empty(), true, fail_not_empty_message);

            BoundedListWrapper<T> list4 = std::move(list3);
            assertListEqualsUsingBracketIndexing(list4, {first, rest...}, fail_list_not_same_message);
            Assert::equals(list3.empty(), true, fail_not_empty_message);
        }

    private:
        template <class... Ts>
        static consteval void checkParameterTypesAllSame() {
            static_assert(is_all_same<Ts...>, "All parameters are not of the same type. Check your tests.");
        }

        template <int capacity, class T>
        static BoundedListWrapper<T> createEmptyList() {
            return BoundedListWrapper<T>(capacity);
        }

        template <int capacity, class T>
        static BoundedListWrapper<T> createListWithElementsReversed(std::initializer_list<T> elemList) {
            BoundedListWrapper<T> list = createEmptyList<capacity, T>();
            forEach(list, &BoundedListWrapper<T>::pushFront, elemList);
            return list;
        }

        template <int capacity, class T>
        static BoundedListWrapper<T> createListWithElements(std::initializer_list<T> elemList) {
            BoundedListWrapper<T> list = createEmptyList<capacity, T>();
            forEach(list, &BoundedListWrapper<T>::pushBack, elemList);
            return list;
        }

        template <class T, class E>
        static void forEach(BoundedListWrapper<T>& list, MonadCallBackType<E, T> callback, std::initializer_list<T> elemList) {
            for (const T& elem: elemList)
                (list.*callback)(elem);
        }

        template <class T>
        static void assertListEqualsUsingBracketIndexing(const BoundedListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i)
                Assert::equals(data(elemList)[i], list[i], fail_message);
        }
        
        template <class T>
        static void assertListEqualsUsingForEach(const BoundedListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            int i = 0;
            for (const T& elem: list)
                Assert::equals(elem, data(elemList)[i++], fail_message);
        }

        template <class T>
        static void assertListEqualsReverseUsingBracketIndexing(const BoundedListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
            for (int i = 0; i < list.getSize(); ++i) {
                int iReversed = list.getSize() - i - 1;
                Assert::equals(data(elemList)[i], list[iReversed], fail_message);
            }
        }

        template <class T>
        static void assertListEqualsReverseUsingForEach(const BoundedListWrapper<T>& list, std::initializer_list<T> elemList, const string& fail_message) {
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

    BoundedListWrapperTest::testEmpty<4, int>();
    BoundedListWrapperTest::testEmpty<4, char>();
    BoundedListWrapperTest::testEmpty<4, string>();
    BoundedListWrapperTest::testEmpty<4, float>();

    BoundedListWrapperTest::testNonEmpty(1, 2);
    BoundedListWrapperTest::testNonEmpty(4.0f, 2.3f);

    BoundedListWrapperTest::testGetSize(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testGetSize(1, 2);
    BoundedListWrapperTest::testGetSize<4>(one, two, three, four);

    BoundedListWrapperTest::testPushBack(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testPushBack<4>(one, two, three, four);
    BoundedListWrapperTest::testPushBack(4.0f, 2.0f, 8.6f);

    BoundedListWrapperTest::testPushFront(4.0f, 2.0f, 3.4f);
    BoundedListWrapperTest::testPushFront(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testPushFront(one, two, three, four);

    BoundedListWrapperTest::testOnePopBack(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testOnePopBack(4.0f, 2.0f, 3.9f);
    BoundedListWrapperTest::testOnePopBack(one, two, three);

    BoundedListWrapperTest::testOnePopFront(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testOnePopFront(4.0f, 2.0f, 3.9f);
    BoundedListWrapperTest::testOnePopFront(one, two, three);

    BoundedListWrapperTest::testPushOutOfCapacity<4>(1, 2, 3, 4);
    BoundedListWrapperTest::testPushOutOfCapacity<4>(one, two, three, four, one);
    BoundedListWrapperTest::testPushOutOfCapacity<3>(2.4f, 2.0f, 3.0f, 4.0f);

    BoundedListWrapperTest::testCopyConstructor(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testCopyConstructor(one, one, one);

    BoundedListWrapperTest::testMoveConstructor(1, 2, 3, 4, 5);
    BoundedListWrapperTest::testMoveConstructor(one, one, one);
}