/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex.hpp"

std::string test_regex_enum_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex functionSignatureRegex(reflect::utils::preprocessor_directives);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, functionSignatureRegex);

    for (const string& fn : fn_buf)
    {
        cerr << fn << "\n";
    }

    return fn_buf[0];
}

const std::string one_space = R"(
        // Distraction!!! #include
        #include <iostream>
        // Distraction!!! #include
    )";

const std::string two_tabs = R"(
        // Distraction!!! #include
        // Distraction!!! #include
        #include    <catch2/catch.cpp>
        // Distraction!!! #include
    )";

const std::string cluttered = R"(
        // Distraction!!! #include
        #include       <gtest/gtest.h>
        // Distraction!!! #include
        // Distraction!!! #include
    )";

const std::string one_tab = R"(
        // Distraction!!! #include
        #include  <vector>
        // Distraction!!! #include
    )";

TEST(test_include, function_search_one_space)
{
    ASSERT_EQ(test_regex_enum_search(one_space), "#include <iostream>");
}

TEST(test_include, function_search_two_tabs)
{
    ASSERT_EQ(test_regex_enum_search(two_tabs), "#include    <catch2/catch.cpp>");
}

TEST(test_include, function_search_cluttered)
{
    ASSERT_EQ(test_regex_enum_search(cluttered), "#include       <gtest/gtest.h>");
}

TEST(test_include, function_search_one_tab)
{
    ASSERT_EQ(test_regex_enum_search(one_tab), "#include  <vector>");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
