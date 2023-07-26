#include <iostream>
#include <regex>
#include <string_view>
#include <vector>

namespace reflect
{
    namespace
    {
        using std::vector;
        using std::string;
    }

    namespace search
    {
        /// @brief Finds all matches of a regex pattern in a string
        /// @param input The string to search in
        /// @param regex_pattern The regex pattern to search for
        /// @return A vector of strings containing all matches
        /// @note This function is not recursive
        inline auto find_matches(const std::string& input, const std::regex& pattern)
            -> vector<string>
        {
            std::vector<std::string> match_buf;
            std::smatch matches;
            std::string::const_iterator cursor(input.cbegin());

            while (std::regex_search(cursor, input.cend(), matches, pattern))
            {
                match_buf.push_back(matches.str());
                cursor = matches.suffix().first;
            }

            return match_buf;
        }

        // auto recurse_regex(  // NOTE: cppcheck thinks this function is in recursive loop chain (Infinite loop I think)
        //     std::string::const_iterator iter,
        //     std::string::const_iterator end,
        //     const std::smatch& match,
        //     const std::regex& regex_literal) -> std::string;
    }  // namespace search

    namespace utils
    {
        // Regex matching constants to find out things for the header file
        // TODO: Add support for multiline comments
        // TODO: Add support for multiline functions
        // TODO: Add support for multiline macros
        // TODO: Add support for multiline classes
        // TODO: Add support for multiline structs
        // TODO: Add support for multiline enum
        // TODO: Add support for multiline enum class
        // TODO: Add support for std::string_view // Maybe

        /// @brief Regex matching constants to find out things for the header file
        /// @note These are all regex literals
        inline const auto header_guard = R"(#ifndef\s+(\w+)\s+#define\s+\1)";
        inline const auto namespace_ = R"(namespace\s+(\w+)\s+{)";
        inline const auto include = R"(#include\s+<(.+)>)";
        inline const auto function = R"(\b([\w:<>]+)\s+[\w:<>]+\s*\(\s*([^\)]*)\s*\))"; // HACK: regex uses [\w:<>]+ to match std::vector<int> like literals
        inline const auto global_variable = R"((\w+)\s+(\w+)\s*;)";
        inline const auto variable = R"((\w+)\s+(\w+)\s*;)";
        inline const auto comment = "//(.+)";
        inline const auto macro = R"(#define\s+(\w+)\s+(.+))";
        inline const auto class_ = R"(class\s+(\w+)\s*{)";
        inline const auto struct_ = R"(struct\s+(\w+)\s*{)";
        inline const auto enum_ = R"(enum\s+(\w+)\s*{)";
        inline const auto enum_class = R"(enum\s+class\s+(\w+)\s*{)";
        inline const auto enum_class_struct = R"(enum\s+class\s+(\w+)\s*{)";

        inline auto operator""_r(const char* str, size_t /*unused*/)
        {
            return std::regex(str /*std::regex::extended*/);
        }
    }  // namespace utils
}  // namespace reflect
