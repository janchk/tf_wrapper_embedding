cmake_minimum_required(VERSION 3.10)
project(TF_WRAPPER_EMBEDDING_APP)

add_executable(TF_WRAPPER_EXAMPLE main.cpp)

target_link_libraries(TF_WRAPPER_EXAMPLE TF_WRAPPER_EMBEDDING)
message( dir ${TF_WRAPPER_EMBEDDING_SOURCE_DIR}   )
target_include_directories(TF_WRAPPER_EXAMPLE 
                            PUBLIC 
                            ${TF_WRAPPER_EMBEDDING_SOURCE_DIR} 
                            .
                            )