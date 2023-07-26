#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

using std::cout;
using std::regex;
using std::string;
using std::vector;

int main()
{
    // Input code containing function signatures
    string code = R"(
        int add(int a, int b) {
            return a + b;
        }

        double divide(double a, double b) {
            if (b == 0.0)
                throw std::runtime_error("Division by zero");
            return a / b;
        }

        void someFunction() {
            // Function without parameters
        }
    )";

    // Regular expression to match function signatures
    const regex functionSignatureRegex(R"(\b(\w+)\s+(\w+)\s*\([^)]*\))");

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, functionSignatureRegex);

    cout << fn_buf[0] << ": first function\n";
    for (const auto& fn : fn_buf)
    {
        cout << fn << "\n";
    }

    return 0;
}
