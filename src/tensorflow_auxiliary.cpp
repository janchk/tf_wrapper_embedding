//
// Created by jakhremchik
//

#include "tensorflow_auxiliary.h"


std::vector<int> tf_aux::get_tensor_shape(tensorflow::Tensor &tensor) {
    std::vector<int> shape;
    int num_dimensions = tensor.shape().dims();
    for (int ii_dim = 0; ii_dim < num_dimensions; ii_dim++) {
        shape.push_back(tensor.shape().dim_size(ii_dim));
    }
    return shape;
}

tensorflow::Tensor tf_aux::convertMatToTensor_v2(cv::Mat img) {
    tensorflow::Tensor input_tensor(tensorflow::DT_FLOAT,
                                    tensorflow::TensorShape({1, 256, 256, 3}));

    auto input_tensor_mapped = input_tensor.tensor<float, 4>();

    for (int y = 0; y < img.rows; y++) {
        for (int x = 0; x < img.cols; x++) {
            cv::Vec3b pixel = img.at<cv::Vec3b>(y, x);

            input_tensor_mapped(0, y, x, 0) = pixel.val[2]; //R
            input_tensor_mapped(0, y, x, 1) = pixel.val[1]; //G
            input_tensor_mapped(0, y, x, 2) = pixel.val[0]; //B
        }
    }

    return input_tensor;
}

std::vector<std::vector<float>> tf_aux::convertTensorToVector(const tensorflow::Tensor &tensor) {
    const auto &temp_tensor = tensor.tensor<float, 2>();
    const auto &dims = tensor.shape();
    std::vector<float> temp_vec;

//    TODO prealloc vector?
//    std::vector<std::vector<float>> vec_embeddings(dims.dim_size(0));
    std::vector<std::vector<float>> vec_embeddings;


//    char out_shape;
//    std::sprintf(&out_shape,"%lld, %lld, %lld",dims.dim_size(0), dims.dim_size(1), dims.dim_size(2));
//    std::cout << out_shape << std::endl;
    for (size_t batch_size = 0; batch_size < dims.dim_size(0); ++batch_size){
        std::cout << batch_size << std::endl; //for debug
        for (size_t embedding_size = 0; embedding_size < dims.dim_size(1); ++embedding_size) {
            temp_vec.push_back(temp_tensor(batch_size, embedding_size));
            std::cout << temp_tensor(batch_size, embedding_size) << " "; //for debug
        }
        std::cout << std::endl; //for debug

        vec_embeddings.push_back(temp_vec);
    }

    return vec_embeddings;

}


void tf_aux::fastResizeIfPossible(const cv::Mat &in, cv::Mat *dist, const cv::Size &size) {
    if (in.size() == size) {
        DebugOutput("sizes matches", std::to_string(in.cols) + "x" + std::to_string(in.rows) + "; "
                                     + std::to_string(size.width) + "x" + std::to_string(size.height));
        in.copyTo(*dist);
        return;
    }

    cv::resize(in, *dist, size, 0, 0, cv::INTER_LINEAR);
    return;
}
