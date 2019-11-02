//
// Created by jakhremchik
//

#include "tensorflow_embeddings.h"




bool TensorFlowEmbeddings::normalize_image(cv::Mat &img) {
    double  min, max;

//    tf_aux::fastResizeIfPossible()
    cv::Scalar data = img.at<cv::Vec3b>(0,0);
    cv::minMaxLoc(img, &min, &max);
    img.convertTo(img, CV_32F, 1, 0); //TODO normalize it in a right way
    img = ((img - cv::Scalar(min, min, min)) / (max - min));
    img = (img * 2) - cv::Scalar(1);
    return true;

}

std::string TensorFlowEmbeddings::inference(const std::vector<cv::Mat> &imgs) {
    using namespace tensorflow;
    for (const cv::Mat &img : imgs) {
        if(!normalize_image(const_cast<cv::Mat &>(img))){
            return "Fail to normalize images";
        }
    }

    if (!tf_aux::convertMatToTensor_v2(imgs, this->_input_tensor)){
        return "Fail to convert Mat to Tensor";
    }

//    Tensor input = getConvertFunction(INPUT_TYPE::DT_FLOAT)(imgs, _input_height,
//            _input_width, _input_depth, _convert_to_float, _mean);
    //preprocess imgs first
//    Tensor input = tf_aux::convertMatToTensor_v2(imgs);
//    std::vector in_tensor_shape = tf_aux::get_tensor_shape(this->_input_tensor);
//    std::vector in_tensor_shape = tf_aux::get_tensor_shape(input);

    #ifdef PHASEINPUT
    tensorflow::Tensor phase_tensor(tensorflow::DT_BOOL, tensorflow::TensorShape());
    phase_tensor.scalar<bool>()() = false;
    std::vector<std::pair<string, tensorflow::Tensor>> inputs = {{_input_node_name, input},{"phase_train:0", phase_tensor}};
    #else
    std::vector<std::pair<string, tensorflow::Tensor>> inputs = {{_input_node_name, this->_input_tensor}};
//    std::vector<std::pair<string, tensorflow::Tensor>> inputs = {{_input_node_name, input}};
    #endif

    _status = _session->Run(inputs, _output_node_names, {}, &_output_tensors);

    tf_aux::DebugOutput("NETWORK_STATUS", _status.ToString());
    return _status.ToString();
}




std::vector<std::vector<float>> TensorFlowEmbeddings::getOutputEmbeddings() {
    if(_output_tensors.empty() || !_is_loaded) {
        std::cerr << "Can't get output Embeddings" << std::endl;
        return {};
    }

    if (out_embeddings.empty()){
        const auto& output = _output_tensors[0];
//        std::cout  << "converting tensor to Vector" << std::endl;
        out_embeddings = convertTensorToVector(output);
    } else {
        out_embeddings.clear();
        getOutputEmbeddings();
    }

    return out_embeddings;
}


std::vector<std::vector<float>> TensorFlowEmbeddings::convertTensorToVector(const tensorflow::Tensor &tensor) {
    const auto &temp_tensor = tensor.tensor<float, 2>();
    const auto &dims = tensor.shape();
    std::vector<float> temp_vec;

//    TODO prealloc vector?
    std::vector<std::vector<float>> vec_embeddings;


    for (size_t batch_size = 0; batch_size < dims.dim_size(0); ++batch_size){
//        std::cout << batch_size << std::endl; //for debug
        for (size_t embedding_size = 0; embedding_size < dims.dim_size(1); ++embedding_size) {
            temp_vec.push_back( temp_tensor(batch_size, embedding_size));
        }

        vec_embeddings.push_back(temp_vec);
    }

    return vec_embeddings;

}
