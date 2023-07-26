set(sources
    src/reflect.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/reflect/reflect.hpp
)

set(test_sources
  src/function_test.cpp
  src/include_test.cpp
)
