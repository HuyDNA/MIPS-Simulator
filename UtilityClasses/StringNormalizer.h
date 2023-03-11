#ifndef _STRING_TRIMMER_MIPS_SIMULATOR_
#define _STRING_TRIMMER_MIPS_SIMULATOR_

#include "visual_class_macros.h"
 
#include <string>

using std::string;

Class StringNormalizer {
    public:
        /*default to whitespaces*/
        static string ltrim(const string &s, const string trimmedCharacters = " \n\r\t\f\v");
        
        /*default to whitespaces*/
        static string rtrim(const string &s, const string trimmedCharacters = " \n\r\t\f\v");
        
        /*default to whitespaces*/
        static string trim(const string &s, const string trimmedCharacters = " \n\r\t\f\v");

        static string spaceCollapse(const string& s);
};

#endif