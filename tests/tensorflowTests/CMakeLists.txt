set(MODULE_NAME tensorflowTests)
set (SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/testExecutionAcceptance.cpp
        ${CMAKE_CURRENT_LIST_DIR}/testTensorflowCorrectness.cpp
        )

add_executable(${MODULE_NAME} ${SRC_FILES})

set(TEST_DATA_PATH ${CMAKE_BINARY_DIR}/tests/${MODULE_NAME}/queries/helsinki_1_andante)

file(MAKE_DIRECTORY ${TEST_DATA_PATH})
file(COPY ${CMAKE_CURRENT_LIST_DIR}/../test_data/queries/helsinki_1_andante/IMG_7813_4.jpg DESTINATION ${TEST_DATA_PATH})

target_link_libraries(${MODULE_NAME} gtest gtest_main TF_WRAPPER_EMBEDDING)

target_include_directories(${MODULE_NAME} PUBLIC
                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR})

add_test(
        NAME
            ${MODULE_NAME}
        COMMAND
            ./${MODULE_NAME}
)