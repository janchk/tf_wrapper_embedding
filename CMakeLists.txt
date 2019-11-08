cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER)
set(CMAKE_PREFIX_PATH ~/.local)


add_subdirectory(src)
add_subdirectory(application)

include(cmake/googletest.cmake)
fetch_googletest(
    ${PROJECT_SOURCE_DIR}/cmake
    ${PROJECT_BINARY_DIR}/googletest
    )

enable_testing()
add_subdirectory(tests)