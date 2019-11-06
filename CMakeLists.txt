cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER)

add_subdirectory(src)
add_subdirectory(application)

enable_testing()
add_subdirectory(tests)