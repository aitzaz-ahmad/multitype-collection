add_library(multitype_collection STATIC
    configurations.cpp
)

target_include_directories(multitype_collection
    PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_compile_options(multitype_collection
    PRIVATE
        -Wall -Wextra -Wpedantic
)
