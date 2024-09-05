# CMakeList.txt : CMake project for expected, include source and define
# project specific logic here.
#

add_library(expected 
"include/expected.h" "expected.cpp")

target_include_directories(expected PUBLIC include)

set_target_properties(expected PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(expected PRIVATE cxx_std_20)
