#find_package(GTest CONFIG REQUIRED)

include(CTest)
include(GoogleTest)

add_executable(test_expected "main.cpp" "include/gtest.h" "test_expected.cpp")

target_include_directories(test_expected PUBLIC include)

target_link_libraries(test_expected PRIVATE gtest_main)
target_link_libraries(test_expected PRIVATE GTest::gmock_main)
target_link_libraries(test_expected PRIVATE GTest::gmock)

target_link_libraries(test_expected PRIVATE expected)

gtest_discover_tests(test_expected
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:test_expected>)

#project(test_expected LANGUAGES CXX)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)