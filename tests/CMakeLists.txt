MESSAGE( STATUS "Including GTest on Tests build" )
include_directories (${GTest_INCLUDE_DIR}/..)

set (SRC_FILES
        ${CMAKE_CURRENT_LIST_DIR}/tf_test.cpp)

set (HDR_FILES
        ${CMAKE_CURRENT_LIST_DIR}/tf_test.h)

find_package(TensorflowCC REQUIRED)

add_executable(tf_test ${SRC_FILES} ${HDR_FILES})



target_link_libraries(tf_test TensorflowCC::Shared)