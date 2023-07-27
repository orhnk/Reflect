#include <iostream>
#include <regex>
#include <string_view>
#include <vector>

namespace reflect
{
    namespace search
    {
        /// @brief Finds all matches of a regex pattern in a string
        /// @param input The string to search in
        /// @param regex_pattern The regex pattern to search for
        /// @return A vector of strings containing all matches
        /// @note This function is not recursive
        inline auto find_matches(const std::string& input, const std::regex& pattern)
            -> std::vector<std::string>
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
        inline const auto include = R"(#include\s+<(.+)>)";

        // HACK: regex uses [\w:<>]+ to match std::vector<int> like literals could remove <, > support to drop templates
        // NOTE: This regex catches function prototypes, function definitions, and function declarations
        inline const auto function = R"(\b([\w:<>]+)\s+[\w:<>]+\s*\(\s*([^\)]*)\s*\))";

        // these may give false positives when it comes to compound statements, functions, etc. (curly braces)
        inline const auto enum_ = R"(\benum(\s+class|\s+struct)?\s+(\w+)\s*\{[^{}]*\})";

        // NOTE: some expressions does not include trailing semicolon, so regexes which
        // catches them will probably get removed in the future because of the code quality
        // <> are not supported, "I don't a use case so."
        inline const auto using_ = R"(\busing\s+([\w:]+\s*(?:,\s*[\w:]+\s*)*);)";

        // NOTE: let me now are there any other features that I skipped
        inline const auto using_alias = R"(\busing\s*\w+\s*=\s*[\w<>:]+;)";

        // NOTE: let me now are there any other features that I skipped
        inline const auto using_namespace = R"(\busing\s+namespace\s+[\w:]+\s*;)";

        inline const auto typedef_ = R"(typedef\s+([\w:<>]+)\s+([\w:<>]+);)";
        inline const auto header_guard = R"(#ifndef\s+(\w+)\s+#define\s+\1)";
        inline const auto namespace_ = R"(namespace\s+(\w+)\s+{)";
        inline const auto global_variable = R"((\w+)\s+(\w+)\s*;)";
        inline const auto variable = R"((\w+)\s+(\w+)\s*;)";
        inline const auto comment = "//(.+)";
        inline const auto macro = R"(#define\s+(\w+)\s+(.+))";
        inline const auto class_ = R"(class\s+(\w+)\s*{)";
        inline const auto struct_ = R"(struct\s+(\w+)\s*{)";
        inline const auto enum_class = R"(enum\s+class\s+(\w+)\s*{)";
        inline const auto enum_class_struct = R"(enum\s+class\s+(\w+)\s*{)";

        inline auto operator""_r(const char* str, size_t /*unused*/)
        {
            return std::regex(str /*std::regex::extended*/);
        }
    }  // namespace utils
}  // namespace reflect
