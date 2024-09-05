#find_package(GTest CONFIG REQUIRED)

include(CTest)
include(GoogleTest)

set(TEST_TARGET tests)

add_executable(${TEST_TARGET} "main.cpp" "include/gtest.h" "test_expected.cpp")

target_include_directories(${TEST_TARGET} PUBLIC include)

target_link_libraries(${TEST_TARGET} PRIVATE gtest_main)
target_link_libraries(${TEST_TARGET} PRIVATE GTest::gmock_main)
target_link_libraries(${TEST_TARGET} PRIVATE GTest::gmock)

target_link_libraries(${TEST_TARGET} PRIVATE Expected)

gtest_discover_tests(${TEST_TARGET}
    DISCOVERY_MODE PRE_TEST
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${TEST_TARGET}>)

#project(${TEST_TARGET} LANGUAGES CXX)
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)