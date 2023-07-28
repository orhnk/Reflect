# Reflect

A C/C++ header file generator (WIP)

```
.cpp -> .hpp
.c   -> .h

transpiler
```

## Author Notes

I am thinking this program as a script. I have finished learning C++ from
[cpplearn.com] so I think that's a good way to get my hands dirty.

Using regexes to parse C++ code? Now that's funny! I thought It'd be easy but it
turns out that there is so much complications when dealing with C++ code I am
now going to (probably) use clang tools to properly parse the C++ source code
and then extract the meaning out of it.

Instead of error prone regex parsing. (For the `Why?` look at the
[Appendix-I](#appendix))

Refactoring could be a choice even It's not welcomed (to refactor generated
`.hpp` files)

I'm planning to make it customizable like the formatter, header guard names, or
the file extensions (`.hh`, `.hxx`, `.H` etc.) and so on

I'm planning to create scripts (specially for (Neo)Vim which Is my daily driver)
that will help my workflow to integrate with this software. (Some examples may
include: Refresh the corresponding header when the source file gets modified)

I may try to make it more generalized on demand but now I'm develop It for my
personal use

## Appendix

### I

- Why I stopped using regexes?

This question may be obvious, but let me give more information upon that.
Firstly, I didn't want this project to get scripted in a language like Python.
Because I want to practice C++ But I didn't want to get into the parsing because
of the potential complexity. but it turns out that there is no better way. so
now I am planning to use some external library to parse the source Then extract
all the declarations out of it. then move it to a `.hpp` file

Here is a simple demonstration why am I doing so:

- How to use regexes to parse C++ variables?

e.g:

```cpp
inline constexpr literal = "some literal";
```

One possible solution may be:

```txt
^\s*\w+\s*\w\s*=\s*[^;];
```

- The above means: catch an expression that:

- Starts from the starting point of the line and followed by an optional
  whitespace(s)
- folloed by some number of words (`inline constexpr`)
- followed by the variable name (`literal`)
- followed by an optional whitespace
- an `=` sign
- followed by another optional whitespace
- and anything till a semicolon (in our case `"some literal"`)

Although this is a simple implementation. This catches some variable
declerations. But there is a lot of vulnerabilities here:

- no brace/paranthesis initialization
- potential `==` sign catch
- possibly catching a variable declaration which is inside a function class etc.
  (We don't need to add it to the header file)
- ...

Also Check out these links:

- https://stackoverflow.com/questions/57024940/c-file-parser-and-function-extractor

## LICENSE

This project is distributed under MIT LICENSE see `LICENSE` for details
