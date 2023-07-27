/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

std::string test_regex_enum_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex enum_regex(reflect::utils::enum_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, enum_regex);

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

const std::string enum_foo = R"(

        // some comment
        auto some() -> distraction
        enum foo {
          one,
          two,
          three,
        }

        // some comment
        auto some() -> distraction
    )";

const std::string failing_enum_foo = R"(

        // some comment
        auto some() -> distraction

        enum foo::some {
          one,
          two,
          three,
        }
// unindentified
        // some comment
        auto some() -> distraction
    )";

const std::string enum_class_some_another = R"(
// unindentified
        // some comment
        auto some() -> distraction
        enum class some_another {
          one,
          two,
          fifty,
          utf-8,
          three,
        }
  // unindentified
    // some comment
        auto some() -> distraction
    )";

const std::string failing_enum_class_should_fail = R"(
// unindentified
        // some comment
        auto some() -> distraction
      // unindentified
              // some comment
        auto some() -> distraction
        enum class should::fail {
          one,
          two,
          three,
        }
// unindentified
        // some comment
        auto some() -> distraction
    )";

TEST(test_enum, enum_search_foo)
{
    ASSERT_EQ(test_regex_enum_search(enum_foo), R"(enum foo {
          one,
          two,
          three,
        })");
}

TEST(test_enum, enum_search_failing_enum_foo)
{
    try
    {
        test_regex_enum_search(failing_enum_foo);
        FAIL() << "Expected std::runtime_error";
    }
    catch (const std::runtime_error& err)
    {
        EXPECT_EQ(err.what(), std::string("No matches found"));
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error";
    }
}

TEST(test_enum, enum_search_some_another)
{
    ASSERT_EQ(test_regex_enum_search(enum_class_some_another), R"(enum class some_another {
          one,
          two,
          fifty,
          utf-8,
          three,
        })");
}

TEST(test_enum, enum_search_failing_enum_class_should_fail)
{
    try
    {
        test_regex_enum_search(failing_enum_class_should_fail);
        FAIL() << "Expected std::runtime_error";
    }
    catch (const std::runtime_error& err)
    {
        EXPECT_EQ(err.what(), std::string("No matches found"));
    }
    catch (...)
    {
        FAIL() << "Expected std::runtime_error";
    }
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
