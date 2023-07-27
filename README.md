# Reflect

A C/C++ header file generator (WIP)

```
.cpp -> .hpp
.c   -> .h

transpiler
```

## Author Notes

I am thinking this program as a script. I have just finished learning C++ from
[cpplearn.com] so I think that's a good way to get my hands dirty.

I am not thinking about something complex here, I will create a "script" that
recursively search your directory tree for `.cpp` files which will than filtered
by regexes which will get written to `.hpp` files.

Refactoring could be a choice even It's not welcomed (to refactor generated
`.hpp` files)

I'm planning to make it customizable like the formatter, header guard names, or
the file extensions (`.hh`, `.hxx`, `.H` etc.) and many more

I'm planning to create scripts (specially for (Neo)Vim which Is my daily driver)
that will help my workflow to integrate with this software. (Some examples may
include: Refresh the corresponding header when the source file gets modified)

I may try to make it more generalized on demand but currently I develop It for
my personal use

## LICENSE

This project is distributed under MIT LICENSE see `LICENSE` for details
