cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER)
set(CMAKE_PREFIX_PATH ~/.local)

#include_directories(include)


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
    #Uncomment in case of linker errors
    #link_libraries(clang_rt.profile-x86_64)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    #Uncomment in case of linker errors
    link_libraries(gcov)
endif ()

add_subdirectory(src)
add_subdirectory(application/example)
add_subdirectory(application/metrics)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

enable_testing()
add_subdirectory(tests)