
/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

std::string test_regex_using_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex using_regex(reflect::utils::using_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, using_regex);

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

const std::string using_std_foo = R"(
        using std::foo;
    )";

const std::string using_multiple_std_foo_bar = R"(
        using std::foo, std::bar;
    )";

const std::string using_long_foo_bar_baz_qux_long = R"(
        using std::foo::bar::baz::qux::long;
    )";

const std::string using_multiple_long_foo_bar_baz_qux_long_long_long  = R"(
        using std::foo::bar::baz::qux::long, std::foo::bar::baz::qux::long_long;
    )";

TEST(test_using, using_std_foo)
{
    ASSERT_EQ(test_regex_using_search(using_std_foo), R"(using std::foo;)");
}

TEST(test_using, using_multiple_std_foo_bar)
{
    ASSERT_EQ(test_regex_using_search(using_multiple_std_foo_bar), R"(using std::foo, std::bar;)");
}

TEST(test_using, using_long_foo_bar_baz_qux_long)
{
    ASSERT_EQ(test_regex_using_search(using_long_foo_bar_baz_qux_long), R"(using std::foo::bar::baz::qux::long;)");
}

TEST(test_using, using_multiple_long_foo_bar_baz_qux_long_long_long)
{
    ASSERT_EQ(test_regex_using_search(using_multiple_long_foo_bar_baz_qux_long_long_long), R"(using std::foo::bar::baz::qux::long, std::foo::bar::baz::qux::long_long;)");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


