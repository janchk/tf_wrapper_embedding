# Locates the tensorFlow library and include directories.

include(FindPackageHandleStandardArgs)
unset(TENSORFLOW_FOUND)

find_path(Core_INCLUDE_DIR
        NAMES
        tensorflow/core
        tensorflow/cc
        HINTS
        ${PATH_TO_TENSORFLOW} )
find_path(Core_Gen_INCLUDE_DIR
        NAMES
        tensorflow/core/framework
        tensorflow/core/protobuf
        HINTS
        ${PATH_TO_TENSORFLOW} )
find_path(Eigen_archive_INCLUDE_DIR
        NAMES
        unsupported/Eigen/CXX11/Tensor
        HINTS
        ${PATH_TO_TENSORFLOW}/bazel-tensorflow/external/eigen_archive )
find_path(Nsync_INCLUDE_DIR
        NAMES
        nsync.h
        HINTS
        ${PATH_TO_TENSORFLOW}/bazel-tensorflow/external/nsync/public )
find_path(Protobuf_INCLUDE_DIR
        NAMES
        google/protobuf
        HINTS
        ${PATH_TO_TENSORFLOW}/bazel-tensorflow/external/com_google_protobuf/src )
find_path(Google_absl_INCLUDE_DIR
        NAMES
        absl
        HINTS
        ${PATH_TO_TENSORFLOW}/bazel-tensorflow/external/com_google_absl )

find_library(CC_LIBRARY
    NAMES
    tensorflow_cc
    HINTS
    ${PATH_TO_TENSORFLOW}/bazel-bin/tensorflow )
find_library(FW_LIBRARY
    NAMES
    tensorflow_framework
    HINTS
    ${PATH_TO_TENSORFLOW}/bazel-bin/tensorflow )
#find_library(TF_LIBRARY
#    NAMES
#    tensorflow
#    HINTS
#    ${PATH_TO_TENSORFLOW}/bazel-bin/tensorflow )

set(TensorFlow_INCLUDE_DIR
    ${Core_INCLUDE_DIR}
    ${Core_Gen_INCLUDE_DIR}
    ${Eigen_archive_INCLUDE_DIR}
    ${Nsync_INCLUDE_DIR}
    ${Protobuf_INCLUDE_DIR}
    ${Google_absl_INCLUDE_DIR})


set(TensorFlow_LIBRARY
    ${FW_LIBRARY}
    ${CC_LIBRARY})
#    ${TF_LIBRARY})

# set TensorFlow_FOUND
find_package_handle_standard_args(TensorFlow DEFAULT_MSG TensorFlow_INCLUDE_DIR TensorFlow_LIBRARY)

# set external variables for usage in CMakeLists.txt
if(TENSORFLOW_FOUND)
    set(TensorFlow_LIBRARIES ${TensorFlow_LIBRARY})
    set(TensorFlow_INCLUDE_DIRS ${TensorFlow_INCLUDE_DIR})
endif()

#message("${TensorFlow_INCLUDE_DIR}")

# hide locals from GUI
mark_as_advanced(TensorFlow_INCLUDE_DIRS TensorFlow_LIBRARIES)

