#ifndef _ASSERT_MIPS_SIMULATOR_
#define _ASSERT_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include <string>
#include <type_traits>
#include <concepts>
#include <cmath>
#include <stdexcept>
#include <iostream>

using std::string;

template <class T1, class T2, class... RestTs>
constexpr bool is_all_same = std::is_same_v<T1, T2> && is_all_same<T2, RestTs...>;;

template <class T1, class T2>
constexpr bool is_all_same<T1, T2> = std::is_same_v<T1, T2>; 

Class Assert {
    public:
        template <class T1, class T2>
            requires (std::floating_point<T1> && std::floating_point<T2>)
        static void equals(const T1& a, const T2& b, const string& fail_message = "Failed", double error = 1e-7) {
            assert(std::abs(a - b) < error, fail_message);
        }

        template <class T1, class T2>
            requires (std::floating_point<T1> && std::floating_point<T2>)
        static void unequals(const T1& a, const T2& b, const string& fail_message = "Failed", double error = 1e-7) {
            assert(std::abs(a - b) >= error, fail_message);
        }


        template <class T1, class T2>
            requires (!std::floating_point<T1> && !std::floating_point<T2>)
        static void equals(const T1& a, const T2& b, const string& fail_message = "Failed") {
            assert(a == b, fail_message);
        }

        template <class T1, class T2>
            requires (!std::floating_point<T1> && !std::floating_point<T2>)
        static void unequals(const T1& a, const T2& b, const string& fail_message = "Failed") {
            assert(a != b, fail_message);
        }
        
        template <class... Ts>
        static consteval void parameterTypesAllSame() {
            static_assert(is_all_same<Ts...>, "All parameters are not of the same type. Check your tests.");
        }
    private:
        static void assert(const bool success, const string& fail_message) {
            if (!success)
                throw std::runtime_error(fail_message);
        }    
};



#endif