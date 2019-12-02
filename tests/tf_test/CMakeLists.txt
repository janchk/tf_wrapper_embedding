MESSAGE( STATUS "Including GTest on Tests build" )
#include_directories (${GTest_INCLUDE_DIR}/..)

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_MODULE_PATH}../cmake)

set (SRC_FILES
        tf_test.cpp)

set (HDR_FILES
        tf_test.h)

find_package(TensorFlow CONFIG REQUIRED)

add_executable(tf_test ${SRC_FILES} ${HDR_FILES})

target_link_libraries(tf_test TensorFlow::TensorFlow gtest gtest_main TF_WRAPPER_EMBEDDING)

target_include_directories(tf_test PUBLIC
                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR})

add_test(
        NAME
            tf_test
        COMMAND
            ./tf_test
)