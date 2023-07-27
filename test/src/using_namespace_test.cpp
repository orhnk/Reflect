/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex.hpp"

std::string test_regex_using_namespace_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex using_namespace_regex(reflect::utils::using_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, using_namespace_regex);

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

const std::string using_namespace_foo = R"(
        using namespace foo;
    )";

const std::string using_namespace_foo_bar = R"(
        using namespace foo::bar;
    )";

const std::string using_namespace_cluttered_foo_bar = R"(
        using     namespace   foo::bar;
    )";

const std::string using_namespace_foo_bar_baz_qux = R"(
        using namespace foo::bar::baz::qux;
    )";

const std::string using_namespace_cluttered_foo_bar_baz_qux = R"(
        using     namespace   foo::bar::baz::qux;
    )";

TEST(test_using_namespace, using_namespace_search_foo)
{
    EXPECT_EQ(test_regex_using_namespace_search(using_namespace_foo), "using namespace foo;");
}

TEST(test_using_namespace, using_namespace_search_foo_bar)
{
    EXPECT_EQ(test_regex_using_namespace_search(using_namespace_foo_bar), "using namespace foo::bar;");
}

TEST(test_using_namespace, using_namespace_search_cluttered_foo_bar)
{
    EXPECT_EQ(test_regex_using_namespace_search(using_namespace_cluttered_foo_bar), "using     namespace   foo::bar;");
}

TEST(test_using_namespace, using_namespace_search_foo_bar_baz_qux)
{
    EXPECT_EQ(test_regex_using_namespace_search(using_namespace_foo_bar_baz_qux), "using namespace foo::bar::baz::qux;");
}

TEST(test_using_namespace, using_namespace_search_cluttered_foo_bar_baz_qux)
{
    EXPECT_EQ(test_regex_using_namespace_search(using_namespace_cluttered_foo_bar_baz_qux), "using     namespace   foo::bar::baz::qux;");
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

