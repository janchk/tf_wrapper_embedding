MESSAGE( STATUS "Including GTest on Tests build" )
#include_directories (${GTest_INCLUDE_DIR}/..)

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_MODULE_PATH}../cmake)



find_package(TensorFlow CONFIG REQUIRED)

# Configuring test data

set(TEST_DATA_DIRECTORY ${CMAKE_BINARY_DIR}/tests/test_data/series)

configure_file(test_data/config.json ${CMAKE_BINARY_DIR}/tests/tensorflowTests COPYONLY)


file(MAKE_DIRECTORY TEST_DATA_DIRECTORY)

file(GLOB_RECURSE TEST_DATA ${CMAKE_CURRENT_LIST_DIR}/test_data/series/*.jpg)



message(STATUS ${TEST_DATA})
message(STATUS ${TEST_DATA_DIRECTORY})


add_subdirectory(commonTests)
add_subdirectory(tensorflowTests)

