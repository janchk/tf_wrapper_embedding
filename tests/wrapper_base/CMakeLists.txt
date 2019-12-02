MESSAGE( STATUS "Including GTest on Tests build" )
#include_directories (${GTest_INCLUDE_DIR}/..)

set(CMAKE_MODULE_PATH
        ${PROJECT_SOURCE_DIR}
        ${CMAKE_MODULE_PATH}../cmake)

set (SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base_tests.cpp)

set (HDR_FILES
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base_tests.h)

find_package(TensorFlow CONFIG REQUIRED)

add_executable(wrapper_base_tests ${SRC_FILES} ${HDR_FILES})

target_link_libraries(wrapper_base_tests TensorFlow::TensorFlow gtest gtest_main TF_WRAPPER_EMBEDDING)

target_include_directories(wrapper_base_tests PUBLIC
        ${TF_WRAPPER_EMBEDDING_SOURCE_DIR})

add_test(
        NAME
        wrapper_base_tests
        COMMAND
        ./wrapper_base_tests
)