MESSAGE( STATUS "Including GTest on Tests build" )
#include_directories (${GTest_INCLUDE_DIR}/..)

set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}
    ${CMAKE_MODULE_PATH}../cmake)

#set (SRC_FILES
#        ${CMAKE_CURRENT_LIST_DIR}/tf_test.cpp)
#
#set (HDR_FILES
#        ${CMAKE_CURRENT_LIST_DIR}/tf_test.h)

find_package(TensorFlow CONFIG REQUIRED)

#add_executable(tf_test ${SRC_FILES} ${HDR_FILES})

#target_link_libraries(tf_test TensorFlow::TensorFlow gtest gtest_main TF_WRAPPER_EMBEDDING)



# Configuring test data

set(TEST_DATA_DIRECTORY ${CMAKE_BINARY_DIR}/tests/test_data/series)

configure_file(test_data/config.json ${CMAKE_BINARY_DIR}/tests COPYONLY)

#file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/tests/test_data/queries)

file(MAKE_DIRECTORY TEST_DATA_DIRECTORY)

file(GLOB_RECURSE TEST_DATA ${CMAKE_CURRENT_LIST_DIR}/test_data/series/*.jpg)

#foreach(DATA ${TEST_DATA})
#    message(STATUS ${DATA})
#    configure_file(${DATA} ${TEST_DATA_DIRECTORY} COPYONLY)
#    file(COPY ${DATA} DESTINATION ${TEST_DATA_DIRECTORY})
#    endforeach(DATA)

message(STATUS ${TEST_DATA})
message(STATUS ${TEST_DATA_DIRECTORY})

#file(COPY ${TEST_DATA} ${TEST_DATA_DIRECTORY})
#configure_file(queries/ ${CMAKE_BINARY_DIR}/tests COPYONLY)



#target_include_directories(tf_test PUBLIC
#                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR})

add_subdirectory(common_tests)

#add_test(
#        NAME
#            tf_test
#        COMMAND
#            ./tf_test
#)