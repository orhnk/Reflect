#include <iostream>
#include <iterator>
#include <regex>
#include <string>

using std::cout;
using std::string;
using std::regex;

auto dummy() -> int {
    string str = "I am looking for GeeksForGeek \n";

    // matches words beginning by "Geek"
    regex regex_matcher {"Geek[a-zA-z]+"};

    // regex_replace() for replacing the match with 'geek'
    cout << std::regex_replace(str, regex_matcher, "geek");

    string result;

    // regex_replace( ) for replacing the match with 'geek'
    regex_replace(
        std::back_inserter(result),
        str.begin(),
        str.end(),
        regex_matcher,
        "geek");

    cout << result;

    return 0;
}
