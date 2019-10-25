#!/bin/bash

cmake-build-debug/TF_WRAPPER_EMBEDDING \
                  -img /home/jakhremchik/Downloads/lena-256x256.jpg \
                  -pb /home/jakhremchik/Downloads/optimized_model_output.pb \
                  --input_node input:0
