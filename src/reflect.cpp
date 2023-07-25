// #include "reflect/reflect.hpp"

#include <iostream>
#include <string>

using std::cout;
using std::string;

namespace reflect {
    // Main function to be called by the user
    // transpiles .cpp -> .hpp
    // Modifies the input string!
    // Copy it manually
    auto reflect(std::string& raw) -> int {
        cout << raw << "\n";
        return 0;
    }
}  // namespace reflect
