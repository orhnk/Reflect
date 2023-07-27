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
    include/reflect/regex.hpp
)

set(test_sources
  src/function_test.cpp
  src/include_test.cpp
  src/enum_test.cpp
  src/using_test.cpp
  src/using_alias_test.cpp
  src/using_namespace_test.cpp
  src/typedef_test.cpp
)
