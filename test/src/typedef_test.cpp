/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex.hpp"

std::string test_regex_typedef_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex typedef_regex(reflect::utils::typedef_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, typedef_regex);

    for (const string& fn : fn_buf)
    {
        cerr << fn << "\n";
    }

    if (fn_buf.empty())
    {
        throw std::runtime_error("No matches found");
    }

    return fn_buf[0];
}

const std::string typedef_int = R"(
        typedef int myInt;
    )";

const std::string typedef_void_foo_pmf_int = R"(
        typedef void (Foo::*pmf)(int);
    )";

const std::string typedef_struct_complex = R"(
      typedef struct
      {
          float real;
          float imaginary;
      } complex;
    )";

TEST(test_typedef, typedef_search_foo)
{
    EXPECT_EQ(test_regex_typedef_search(typedef_int), "typedef int myInt;");
}

TEST(test_typedef, typedef_search_foo_pmf)
{
    EXPECT_EQ(test_regex_typedef_search(typedef_void_foo_pmf_int), "typedef void (Foo::*pmf)(int);");
}

TEST(test_typedef, typedef_search_struct_complex)
{
    EXPECT_EQ(test_regex_typedef_search(typedef_struct_complex), "typedef struct\n      {\n          float real;\n          float imaginary;\n      } complex;");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
