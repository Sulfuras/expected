# CMakeList.txt : CMake project for Expected, include source and define
# project specific logic here.
#

add_library(Expected 
"include/Expected.h" "Expected.cpp")

target_include_directories(Expected PUBLIC include)

set_target_properties(Expected PROPERTIES LINKER_LANGUAGE CXX)

target_compile_features(Expected PRIVATE cxx_std_20)
