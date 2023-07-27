/*
 * Test #include <...> regex to match include statements
 * */
#include <gtest/gtest.h>

#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include "reflect/regex_utils.hpp"

std::string test_regex_<tmp>_search(const std::string& code)
{
    using std::cerr;
    using std::regex;
    using std::string;
    using std::vector;

    // Input code containing function signatures
    // Regular expression to match function signatures
    const regex <tmp>_regex(reflect::utils::<tmp>_);
    // Convert into regex

    // Searching for function signatures in the code
    vector<string> fn_buf = reflect::search::find_matches(code, <tmp>_regex);

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

const std::string <tmp>_foo = R"(

        // some comment
        auto some() -> distraction
        <tmp> foo {
          one,
          two,
          three,
        }

        // some comment
        auto some() -> distraction
    )";

const std::string failing_<tmp>_foo = R"(

        // some comment
        auto some() -> distraction

        <tmp> foo::some {
          one,
          two,
          three,
        }
// unindentified
        // some comment
        auto some() -> distraction
    )";

const std::string <tmp>_class_some_another = R"(
// unindentified
        // some comment
        auto some() -> distraction
        <tmp> class some_another {
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

const std::string failing_<tmp>_class_should_fail = R"(
// unindentified
        // some comment
        auto some() -> distraction
      // unindentified
              // some comment
        auto some() -> distraction
        <tmp> class should::fail {
          one,
          two,
          three,
        }
// unindentified
        // some comment
        auto some() -> distraction
    )";

TEST(test_<tmp>, <tmp>_search_foo)
{
    ASSERT_EQ(test_regex_<tmp>_search(<tmp>_foo), R"(<tmp> foo {
          one,
          two,
          three,
        })");
}

TEST(test_<tmp>, <tmp>_search_failing_<tmp>_foo)
{
    try
    {
        test_regex_<tmp>_search(failing_<tmp>_foo);
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

TEST(test_<tmp>, <tmp>_search_some_another)
{
    ASSERT_EQ(test_regex_<tmp>_search(<tmp>_class_some_another), R"(<tmp> class some_another {
          one,
          two,
          fifty,
          utf-8,
          three,
        })");
}

TEST(test_<tmp>, <tmp>_search_failing_<tmp>_class_should_fail)
{
    try
    {
        test_regex_<tmp>_search(failing_<tmp>_class_should_fail);
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


