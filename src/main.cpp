#include <iostream>
#include <iterator>
#include <regex>
#include <string>

#include "reflect/regex_utils.hpp"

using std::cout;
using std::regex;
using std::string;

auto main() -> int {
    string
        str =  // A dummy C++ code snippet just to get transpiled into a header file
        R"(
        #include <iostream>

        using namespace std;

        // run_1()
        // -> 1
        // 1
        int run_1()
        {
            cout << "run_1";
            return 0;
        }

        // run_2()
        // -> 2
        // 2
        auto run_2 = []() -> int {
            cout << "run_2";
            return 0;
        };

        // run_3()
        // -> 3
        // 3
        auto run_3() -> int {
            cout << "run_3";
            return 0;
        };
        )";

    // matches words beginning by "Geek"

    try {
        using regex_utils::operator""_r;
        regex regex_matcher = R"((\w+)\s+(\w+)\s*\((.*)\)\s*{)"_r;
        string regex_buffer;
        // regex_replace() for replacing the match with 'geek'
        regex_replace(
            back_inserter(regex_buffer),
            str.begin(),
            str.end(),
            regex_matcher,
            "<SOME FUNCTION FOUND>");
    } catch (std::regex_error& e) {
        // Syntax error in the regular expression
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
