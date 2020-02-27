project(TF_WRAPPER_EMBEDDING_EXAMPLE)

add_executable(TF_WRAPPER_EXAMPLE main.cpp)

target_link_libraries(TF_WRAPPER_EXAMPLE TF_WRAPPER_EMBEDDING)
message( dir ${TF_WRAPPER_EMBEDDING_SOURCE_DIR}   )

configure_file(../../config.json ${CMAKE_BINARY_DIR}/application/example COPYONLY)
target_include_directories(TF_WRAPPER_EXAMPLE
                            PUBLIC
                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR}
                            )
set_target_properties(TF_WRAPPER_EXAMPLE PROPERTIES LINK_FLAGS "-Wl,-rpath,/usr/local/cuda-10.0/lib64")
