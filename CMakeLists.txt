cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER_EMBEDDING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

set(PATH_TO_TENSORFLOW "/home/jakhremchik/Downloads/tensorflow/")

message(${PATH_TO_TENSORFLOW})
#set(PATH_TO_TENSORFLOW $ENV{TF_PATH})
if( NOT PATH_TO_TENSORFLOW)
  message( FATAL_ERROR "Set environment variable TF_PATH to tensorflow root directory" )
  message( STATUS "use tf_cc" )
  list(APPEND CMAKE_PREFIX_PATH "/opt/tensorflow_cc/lib/cmake")
  find_package(TensorflowCC COMPONENTS Shared REQUIRED)
else()
  message( STATUS "Looking for Tensorflow in " ${PATH_TO_TENSORFLOW} )
  find_package(TensorFlow REQUIRED)
endif()

add_executable(TF_WRAPPER_EMBEDDING main.cpp)

message("${TensorFlow_INCLUDE_DIRS}")

target_include_directories(TF_WRAPPER_EMBEDDING PRIVATE ${TensorFlow_INCLUDE_DIRS})
target_link_libraries(TF_WRAPPER_EMBEDDING ${TensorFlow_LIBRARIES})

#message("${TensorFlow_LIBRARIES}")
message("${TensorFlow_INCLUDE_DIRS}")
