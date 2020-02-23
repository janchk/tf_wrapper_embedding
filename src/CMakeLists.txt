cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER_EMBEDDING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/../cmake
    ${CMAKE_MODULE_PATH})

find_package(TensorFlow CONFIG REQUIRED)
#message("${CMAKE_MODULE_PATH}")
find_package( OpenCV REQUIRED )

add_library(TF_WRAPPER_EMBEDDING STATIC)

target_include_directories(TF_WRAPPER_EMBEDDING
        PUBLIC
        ~/.local/include
        ${PROJECT_SOURCE_DIR}/../include/
        ${CMAKE_CURRENT_LIST_DIR}
        )

target_sources(TF_WRAPPER_EMBEDDING
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/interfaces.h
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_interfaces.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_base.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_wrapper_core.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_embeddings.h
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_auxiliary.h
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_legacy.h
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base.h
        ${CMAKE_CURRENT_LIST_DIR}/common/fs_handling.h
        ${CMAKE_CURRENT_LIST_DIR}/common/common_ops.h
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_base.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_wrapper_core.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_embeddings.cpp
        ${CMAKE_CURRENT_LIST_DIR}/tensorflow_auxiliary.cpp
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_legacy.cpp
        ${CMAKE_CURRENT_LIST_DIR}/wrapper_base.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/fs_handling.cpp
        ${CMAKE_CURRENT_LIST_DIR}/common/common_ops.cpp

)



message(TF LIBRARIES ${TensorFlow_LIBRARIES})



target_include_directories(TF_WRAPPER_EMBEDDING PRIVATE)
target_link_libraries(TF_WRAPPER_EMBEDDING stdc++fs TensorFlow::TensorFlow ${OpenCV_LIBS})




find_package(CUDA)
if(CUDA_FOUND)
  target_link_libraries(TF_WRAPPER_EMBEDDING ${CUDA_LIBRARIES})
endif()

message("INCLUDING TF LIBS" ${TensorFlow_LIBRARIES})
#message("${TensorFlow_INCLUDE_DIRS}")
