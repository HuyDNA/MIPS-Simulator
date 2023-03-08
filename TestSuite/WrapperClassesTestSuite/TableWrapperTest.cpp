#include "visual_class_macros.h"

#include "TestSuite/Assert.h"

#include "WrapperClasses/TableWrapper.h"

#include <iostream>
#include <initializer_list>

using std::cout;

template <class T1, class T2, class... RestTs>
constexpr bool is_all_same = std::is_same_v<T1, T2> && is_all_same<T2, RestTs...>;;

template <class T1, class T2>
constexpr bool is_all_same<T1, T2> = std::is_same_v<T1, T2>; 

Class TableWrapperTest {
    public:
        
    private:
};

int main() {

}