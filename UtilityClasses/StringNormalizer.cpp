#include "visual_class_macros.h"

#include "UtilityClasses/StringNormalizer.h"

#include <algorithm>

#include <string>
#include <regex>

using std::string;

/*default to whitespaces*/
string StringNormalizer::ltrim(const string &s, const string trimmedCharacters) {
    size_t start = s.find_first_not_of(trimmedCharacters);
    return (start == string::npos) ? "" : s.substr(start);
}

/*default to whitespaces*/
string StringNormalizer::rtrim(const string &s, const string trimmedCharacters) {
    size_t end = s.find_last_not_of(trimmedCharacters);
    return (end == string::npos) ? "" : s.substr(0, end + 1);
}

/*default to whitespaces*/
string StringNormalizer::trim(const string &s, const string trimmedCharacters) {
    return rtrim(ltrim(s, trimmedCharacters), trimmedCharacters);
}

string StringNormalizer::spaceCollapse(const string& s) {
    using namespace std;

    const regex contiguousSpacePattern(R"(\s+)");
    const char* substitutedText = R"( )";
    
    return regex_replace(s, contiguousSpacePattern, substitutedText);
}