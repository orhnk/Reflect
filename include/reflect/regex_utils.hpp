#include <regex>
#include <string_view>

namespace regex_utils {
    // Regex matching constants to find out things for the header file
    // clang-format off
    // TODO: Add support for multiline comments
    // TODO: Add support for multiline functions
    // TODO: Add support for multiline macros
    // TODO: Add support for multiline classes
    // TODO: Add support for multiline structs
    // TODO: Add support for multiline enum
    // TODO: Add support for multiline enum class
    // TODO: Add support for std::string_view // Maybe
    inline const std::string header_guard = R"(#ifndef\s+(\w+)\s+#define\s+\1)";
    inline const std::string namespace_ = R"(namespace\s+(\w+)\s+{)";
    inline const std::string include = "#include\\s+<(.+)>";
    inline const std::string function = R"((\w+)\s+(\w+)\s*\((.*)\)\s*{)";
    inline const std::string global_variable = R"((\w+)\s+(\w+)\s*;)";
    inline const std::string variable = R"((\w+)\s+(\w+)\s*;)";
    inline const std::string comment = "//(.+)";
    inline const std::string macro = R"(#define\s+(\w+)\s+(.+))";
    inline const std::string class_ = R"(class\s+(\w+)\s*{)";
    inline const std::string struct_ = R"(struct\s+(\w+)\s*{)";
    inline const std::string enum_ = R"(enum\s+(\w+)\s*{)";
    inline const std::string enum_class = R"(enum\s+class\s+(\w+)\s*{)";
    inline const std::string enum_class_struct = R"(enum\s+class\s+(\w+)\s*{)";

    inline auto operator""_r(const char* str, size_t /*unused*/) {
        return std::regex(str /*std::regex::extended*/);
    }
}  // namespace regex_utils
