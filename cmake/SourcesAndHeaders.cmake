set(sources
    # src/reflect.hpp
    src/regex.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    # include/reflect/reflect.hpp
    include/reflect/regex_utils.hpp
)

set(test_sources
  src/function_test.cpp
  src/include_test.cpp
  src/enum_test.cpp
)
