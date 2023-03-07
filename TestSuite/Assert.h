#ifndef _ASSERT_MIPS_SIMULATOR_
#define _ASSERT_MIPS_SIMULATOR_

#include "visual_class_macros.h"

#include <string>
#include <type_traits>
#include <concepts>
#include <cmath>

using std::string;

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
    private:
        static void assert(const bool failed, const string& fail_message) {
            if (failed)
                throw fail_message;
        }    
};



#endif