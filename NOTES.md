# Notes

- Trailing return syntax: This project embraces modern looking perfectly aligned
  trailing return syntax (C++20)

## Other

I thought I could use some regex to find & copy C++ text without the need of
parsing. But that turns out to be wrong. There are a ton of complexity in C++
which could potentially corrupt the transpilation process so I am planning to
use a C++20 (I hope so) parsing library which would do the whole heavy-lifting
for me. As of now I am just searching for one.

Or I'll try to adabt regex to my code. As I said refactoring are welcomed and
instead of improper copies (declarations in a header file) compiler errors are
preferencial
