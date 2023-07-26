/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

std::string test_regex_function_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex functionSignatureRegex(reflect::utils::include);
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
        #include <iostream>
    )";

const std::string two_tabs = R"(
        #include    <catch2/catch.cpp>
    )";

const std::string cluttered = R"(
        #include       <gtest/gtest.h>
    )";

const std::string one_tab = R"(
        #include  <vector>
    )";

TEST(test_include, function_search_one_space)
{
    ASSERT_EQ(test_regex_function_search(one_space), "#include <iostream>");
}

TEST(test_include, function_search_two_tabs)
{
    ASSERT_EQ(test_regex_function_search(two_tabs), "#include    <catch2/catch.cpp>");
}

TEST(test_include, function_search_cluttered)
{
    ASSERT_EQ(test_regex_function_search(cluttered), "#include       <gtest/gtest.h>");
}

TEST(test_include, function_search_one_tab)
{
    ASSERT_EQ(test_regex_function_search(one_tab), "#include  <vector>");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
