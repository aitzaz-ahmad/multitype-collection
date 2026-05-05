include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(multitype_collection_tests
    configurations_tests.cpp
)

target_link_libraries(multitype_collection_tests
    PRIVATE
        multitype_collection
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(multitype_collection_tests)
