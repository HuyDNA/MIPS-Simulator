#ifndef _ASSERT_MIPS_SIMULATOR_
#define _ASSERT_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include <string>
#include <type_traits>
#include <concepts>
#include <cmath>

using std::string;

template <class T>
concept not_floating_point = !std::is_floating_point<T>::value;

Class Assert {
    public:
        template <class T>
            requires not_floating_point<T>
        static void equals(const T& a, const T& b, const string& fail_message = "Failed", double error = 1e-7) {
            assert(std::abs(a - b) < error, fail_message);
        }

        template <class T>
            requires not_floating_point<T>
        static void unequals(const T& a, const T& b, const string& fail_message = "Failed", double error = 1e-7) {
            assert(std::abs(a - b) >= error, fail_message);
        }


        template <class T>
            requires std::floating_point<T>
        static void equals(const T& a, const T& b, const string& fail_message = "Failed") {
            assert(a == b, fail_message);
        }

        template <class T>
            requires std::floating_point<T>
        static void unequals(const T& a, const T& b, const string& fail_message = "Failed") {
            assert(a != b, fail_message);
        }
    private:
        static void assert(const bool failed, const string& fail_message) {
            if (failed)
                throw fail_message;
        }    
};



#endif