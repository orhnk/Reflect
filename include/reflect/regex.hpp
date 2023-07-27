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
        // Not much grouping done here, just some copy & paste after the compiler checks

        /// @brief Matches `using *;` where * is literally anything (except semicolon)
        /// @note This includes `using namespace *;`, `using std::cout;`, `using myInt = int;`, etc.
        // IMPORTANT! This does not match multiline directives
        inline constexpr auto preprocessor_directives = R"(\b#.*$)";

        /// @brief Matches `<type> <name>(<args>)`
        /// @note This includes `int main(int argc, char** argv)`, `void foo()`, `int bar(int a, int b)`, etc.
        /// @note Also matches trailing return syntax (e.g `auto main() -> int`)
        /// @note WIP: Design it to catch any possible function declaration (e.g `int (*foo)(int)`) without any complexity
        // NOTE: Could try switching \b -> ^
        inline constexpr auto function = R"(\b[+\(]+\([^\)]*\).*(?=\s*\{))";

        /// @brief Matches `enum <name> { ... };`
        /// Cannot Include:
        /// - : (colon) -> Actually this check is unnecessary since Reflect compiles the code first.
        /// This is included because unit tests are not compiled.
        // inline constexpr auto enum_ = R"(\benum[^\{:]+\{[^\}]+\})"; // removed
        inline constexpr auto enum_ = R"(\benum[^\{]+\{[^\}]+\})";

        // NOTE: Could omit the semicolon for simpler post-processing
        // - Adding semicolons to the end of every match without the need of checking whether there is.
        inline constexpr auto using_ = R"(\busing[^;]+;)";
        inline constexpr auto typedef_ = R"(\btypedef[^;]+;)";

        // IMPORTANT: Now things are getting complicated, namespaces has to exist in both header and source files
        // TODO: Add support for nested namespaces, also add support for namespaces, namespace aliases, etc.
        // So I am thinking recursive namespace matching which follows the principle:
        // - namespace { raw } -> if (!namespace -> apply_all_regexes(raw) -> header)
        // - else -> namespace { raw } -> recurse
        inline constexpr auto namespace_ = R"(\bnamespace[^\{]+\{[^\}]+\})";

        /// @brief Matches `... = ...;`
        inline constexpr auto variable = R"(\b[^=;]+=[^=;]+;)";

        /// @brief Matches `// ...`
        inline constexpr auto comment = R"(^\s*//.+$)";

        inline constexpr auto class_ = R"(\bclass.+\{.+\})";
        inline constexpr auto struct_ = R"(\bstruct.+\{.+\})";

        // IMPORTANT! This section is incomplete
        namespace detailed
        {
            // Regex matching constants to find out things for the header file
            // TODO: Add support for nested parentheses (e.g. std::vector<std::pair<int, int>>)
            // TODO: Add support for multiline comments
            // TODO: Add support for multiline functions
            // TODO: Add support for multiline macros
            // TODO: Add support for multiline classes
            // TODO: Add support for multiline structs
            // TODO: Add support for multiline enum
            // TODO: Add support for multiline enum class
            // TODO: Add support for std::string_view // Maybe (In regexes)

            /// @brief Regex matching constants to find out things for the header file
            /// @note These are all regex literals
            inline constexpr auto include = R"(#include\s+<(.+)>)";
            // NOTE: This regex catches preprocessor directives
            // TODO: Add support for multiline preprocessor directives
            // NOTE: maybe remove #include
            inline constexpr auto preprocessor_directives = R"(\b#(\w+)$)";

            // HACK: regex uses [\w:<>]+ to match std::vector<int> like literals could remove <, > support to drop templates
            // NOTE: This regex catches function prototypes, function definitions, and function declarations
            inline constexpr auto function = R"(\b([\w:<>]+)\s+[\w:<>]+\s*\(\s*([^\)]*)\s*\))";

            // these may give false positives when it comes to compound statements, functions, etc. (curly braces)
            inline constexpr auto enum_ = R"(\benum(\s+class|\s+struct)?\s+(\w+)\s*\{[^{}]*\})";

            // NOTE: some expressions does not include trailing semicolon, so regexes which
            // catches them will probably get removed in the future because of the code quality
            // <> are not supported, "I don't a use case so."
            inline constexpr auto using_ = R"(\busing\s+([\w:]+\s*(?:,\s*[\w:]+\s*)*);)";

            // NOTE: let me now are there any other features that I skipped
            inline constexpr auto using_alias = R"(\busing\s*\w+\s*=\s*[\w<>:]+;)";

            // NOTE: let me now are there any other features that I skipped
            inline constexpr auto using_namespace = R"(\busing\s+namespace\s+[\w:]+\s*;)";

            // NOTE: let me now are there any other features that I skipped
            inline constexpr auto typedef_ = R"(\btypedef\s+(?:(struct|class|union)\s+)?([\w:<>,*]+\s*)?([\w_][\w\d_]*)\s*;)";

            inline constexpr auto header_guard = R"(#ifndef\s+(\w+)\s+#define\s+\1)";
            inline constexpr auto namespace_ = R"(namespace\s+(\w+)\s+{)";
            inline constexpr auto global_variable = R"((\w+)\s+(\w+)\s*;)";

            // Most complex one (I think)
            // NOTE: This regex manually checks for C/C++ variable keywords. These has to get expanded
            inline constexpr auto variable_declaration = R"(\b(?:volatile\s+|register\s+|const\s+|auto\s+)?([\w:<>,*]+)\s+([\w_][\w\d_]*)\s*(?:=\s*([^;]+))?\s*;)";
            inline constexpr auto comment = "//(.+)";
            inline constexpr auto macro = R"(#define\s+(\w+)\s+(.+))";
            inline constexpr auto class_ = R"(class\s+(\w+)\s*{)";
            inline constexpr auto struct_ = R"(struct\s+(\w+)\s*{)";
            inline constexpr auto enum_class = R"(enum\s+class\s+(\w+)\s*{)";
            inline constexpr auto enum_class_struct = R"(enum\s+class\s+(\w+)\s*{)";

            inline auto operator""_r(const char* str, size_t /*unused*/)
            {
                return std::regex(str /*std::regex::extended*/);
            }

        }  // namespace detailed
    }  // namespace utils
}  // namespace reflect
