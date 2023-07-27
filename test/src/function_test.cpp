/*
 * Test the <type> <bane>(... params ...) regex to match function signatures
 * */

#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex.hpp"

std::string test_regex_function_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex functionSignatureRegex(reflect::utils::function);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, functionSignatureRegex);

    for (const string& fn : fn_buf)
    {
        cerr << fn << "\n";
    }

    return fn_buf[0];
}

const std::string int_add = R"(
        int add(int a, int b) {
            return a + b;
        }
    )";

const std::string double_divide = R"(
        double divide(double a, double b) {
            if (b == 0.0)
                throw std::runtime_error("Division by zero");
            return a / b;
        }
    )";

const std::string void_someFunction = R"(
        void someFunction() {
            // Function without parameters
        }
    )";

const std::string vector_int_add = R"(
        std::vector<int> add(std::vector<int> a, std::vector<int> b) {
            return a + b;
        }
    )";

const std::string class_fn_foo_foo = R"(
        void Foo::foo(int some, char* param) {
            // Function without parameters
        }
    )";

const std::string multiline_class_fn_foo_foo = R"(
        void Foo::foo(
            int a,
            int b
        ) {
            return a + b;
        }
    )";

// TODO
// These are not going to get moved to the .cpp file because of the template
// So Unmatch thsese! ^template
const std::string neg_template_int_add = R"(
        template <typename T>
        T add(T a, T b) {
            return a + b;
        }
    )";

TEST(test_fn, simple)
{
    ASSERT_EQ(test_regex_function_search(int_add), "int add(int a, int b)");
}

TEST(test_fn, simple_long)
{
    ASSERT_EQ(test_regex_function_search(double_divide), "double divide(double a, double b)");
}

TEST(test_fn, simple_no_params)
{
    ASSERT_EQ(test_regex_function_search(void_someFunction), "void someFunction()");
}

TEST(test_fn, complex_types)
{
    ASSERT_EQ(test_regex_function_search(vector_int_add), "std::vector<int> add(std::vector<int> a, std::vector<int> b)");
}

TEST(test_fn, complex_class_types)
{
    ASSERT_EQ(test_regex_function_search(class_fn_foo_foo), "void Foo::foo(int some, char* param)");
}

TEST(test_fn, class_complex_multiline)
{
    ASSERT_EQ(test_regex_function_search(multiline_class_fn_foo_foo),
    R"(void Foo::foo(
            int a,
            int b
        ))");
}

// TEST(test_fn_simple, CheckValues)
// {
// }

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
