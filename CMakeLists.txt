cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER_EMBEDDING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_MODULE_PATH
    ${PROJECT_SOURCE_DIR}/cmake
    ${CMAKE_MODULE_PATH})

# set(PATH_TO_TENSORFLOW "/home/jakhremchik/Downloads/tensorflow/")

# message(${PATH_TO_TENSORFLOW})
#set(PATH_TO_TENSORFLOW $ENV{TF_PATH})
# if( NOT PATH_TO_TENSORFLOW)
#   message( FATAL_ERROR "Set environment variable TF_PATH to tensorflow root directory" )
#   message( STATUS "use tf_cc" )
#   list(APPEND CMAKE_PREFIX_PATH "/opt/tensorflow_cc/lib/cmake")
#   find_package(TensorflowCC COMPONENTS Shared REQUIRED)
# else()
#   message( STATUS "Looking for Tensorflow in " ${PATH_TO_TENSORFLOW} )
#   find_package(TensorFlow REQUIRED)
# endif()
find_package(TensorflowCC REQUIRED)
find_package( OpenCV REQUIRED )

add_executable(TF_WRAPPER_EMBEDDING src/main.cpp src/tensorflow_base.cpp src/tensorflow_base.h src/tensorflow_wrapper_core.cpp src/tensorflow_wrapper_core.h src/common/fs_handling.cpp src/common/fs_handling.h src/tensorflow_embeddings.cpp src/tensorflow_embeddings.h src/tensorflow_auxiliary.cpp src/tensorflow_auxiliary.h src/wrapper_legacy.cpp src/wrapper_legacy.h)

# message("${TensorFlow_INCLUDE_DIRS}")

# target_include_directories(TF_WRAPPER_EMBEDDING PRIVATE ${TensorFlow_INCLUDE_DIRS})
#target_link_libraries(TF_WRAPPER_EMBEDDING TensorflowCC::Shared ${OpenCV_LIBS})
target_link_libraries(TF_WRAPPER_EMBEDDING TensorflowCC::Static ${OpenCV_LIBS})

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
