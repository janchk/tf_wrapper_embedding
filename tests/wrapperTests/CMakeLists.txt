set(MODULE_NAME wrapperTests)
set (SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/testWrapperBase.cpp
#        ${CMAKE_CURRENT_LIST_DIR}/testTensorflowCorrectness.cpp
        )

add_executable(${MODULE_NAME} ${SRC_FILES})


target_link_libraries(${MODULE_NAME} gtest gtest_main TF_WRAPPER_EMBEDDING)

target_include_directories(${MODULE_NAME} PUBLIC
                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR})

add_test(
        NAME
            ${MODULE_NAME}
        COMMAND
            ./${MODULE_NAME}
)