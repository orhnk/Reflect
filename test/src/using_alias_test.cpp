/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

std::string test_regex_using_alias_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex using_alias_regex(reflect::utils::using_alias_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, using_alias_regex);

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

const std::string using_alias_bar = R"(
        using foo = std::bar;
    )";

const std::string using_alias_template_bar = R"(
        using foo = std::bar<true>;
    )";

const std::string using_alias_long_bar = R"(
        using foo = std::very::long::destination::bar;
    )";

const std::string using_alias_long_template_bar = R"(
        using foo = std::very::long::destination::bar<size_t>;
    )";

TEST(test_using_alias, using_alias_bar)
{
    ASSERT_EQ(test_regex_using_alias_search(using_alias_bar), R"(using foo = std::bar;)");
}

TEST(test_using_alias, using_alias_template_bar)
{
    ASSERT_EQ(test_regex_using_alias_search(using_alias_template_bar), R"(using foo = std::bar<true>;)");
}

TEST(test_using_alias, using_alias_long_bar)
{
    ASSERT_EQ(test_regex_using_alias_search(using_alias_long_bar), R"(using foo = std::very::long::destination::bar;)");
}

TEST(test_using_alias, using_alias_long_template_bar)
{
    ASSERT_EQ(test_regex_using_alias_search(using_alias_long_template_bar), R"(using foo = std::very::long::destination::bar<size_t>;)");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
