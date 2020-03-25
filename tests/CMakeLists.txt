message(STATUS "Including GTest on Tests build")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR} ${CMAKE_MODULE_PATH}../cmake)

find_package(TensorFlow CONFIG REQUIRED)

# Configuring test data

file(COPY test_data/test79_rotated.pb
     DESTINATION ${CMAKE_BINARY_DIR}/test_data/)
file(GLOB_RECURSE TEST_DATA ${CMAKE_CURRENT_LIST_DIR}/test_data/series/*.jpg)


add_subdirectory(commonTests)
add_subdirectory(tensorflowTests)
add_subdirectory(wrapperTests)
add_subdirectory(metricsTests)

configure_file(test_data/config.json
               ${CMAKE_BINARY_DIR}/tests/tensorflowTests/config.json COPYONLY)
configure_file(
  test_data/sample_config.json
  ${CMAKE_BINARY_DIR}/tests/commonTests/sample_config.json COPYONLY)
