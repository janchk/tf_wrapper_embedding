cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER_EMBEDDING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

find_package(TensorflowCC REQUIRED)
find_package( OpenCV REQUIRED )

# add_executable(TF_WRAPPER_EMBEDDING src/main.cpp)
add_library(TF_WRAPPER_EMBEDDING STATIC)

target_include_directories(TF_WRAPPER_EMBEDDING PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../include/ .)

target_sources(TF_WRAPPER_EMBEDDING
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_base.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_wrapper_core.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_embeddings.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_auxiliary.h
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_legacy.h
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base.h
        ${CMAKE_CURRENT_LIST_DIR}/common/fs_handling.h
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_base.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_wrapper_core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_embeddings.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_auxiliary.cpp
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_legacy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/fs_handling.cpp

)

# message("${TensorFlow_INCLUDE_DIRS}")

# target_include_directories(TF_WRAPPER_EMBEDDING PRIVATE ${TensorFlow_INCLUDE_DIRS})
#target_link_libraries(TF_WRAPPER_EMBEDDING TensorflowCC::Shared stdc++fs ${OpenCV_LIBS})
target_link_libraries(TF_WRAPPER_EMBEDDING TensorflowCC::Static  stdc++fs ${OpenCV_LIBS})

# OLD WAY TO INCLUDE TENSORFLOW #

## TensorFlow headers
#include_directories("/usr/local/include/tf/")
#include_directories("/usr/local/include/tf/bazel-genfiles/")
#include_directories("/usr/local/include/tf/tensorflow/")
#include_directories("/usr/local/include/tf/third-party/")
#
## Link TensorFlow libs
#target_link_libraries(TF_WRAPPER_EMBEDDING "/usr/local/lib/libtensorflow_cc.so")
#target_link_libraries(TF_WRAPPER_EMBEDDING "/usr/local/lib/libtensorflow_framework.so")



find_package(CUDA)
if(CUDA_FOUND)
  target_link_libraries(TF_WRAPPER_EMBEDDING ${CUDA_LIBRARIES})
endif()

#message("${TensorFlow_LIBRARIES}")
# message("${TensorFlow_INCLUDE_DIRS}")
