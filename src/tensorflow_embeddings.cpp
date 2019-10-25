//
// Created by jakhremchik
//

#include "tensorflow_embeddings.h"

std::vector<std::vector<float>> TensorFlowEmbeddings::getOutputEmbeddings(){
    if(_output_tensors.empty() || !_is_loaded) {
        std::cerr << "Can't get output Embeddings" << std::endl;
        return {};
    }

    if (embeddings.empty()){
        const auto& output = _output_tensors[0];
        embeddings = tf_aux::convertTensorToVector(output);

    }

    return embeddings;
}

std::string TensorFlowEmbeddings::inference(const std::vector<cv::Mat> &imgs){
    using namespace tensorflow;
    Tensor input = getConvertFunction(INPUT_TYPE::DT_FLOAT)(imgs, _input_height,
            _input_width, _input_depth, _convert_to_float, _mean);
    std::vector in_tensor_shape = tf_aux::get_tensor_shape(input);

    #ifdef PHASEINPUT
    tensorflow::Tensor phase_tensor(tensorflow::DT_BOOL, tensorflow::TensorShape());
    phase_tensor.scalar<bool>()() = false;
    std::vector<std::pair<string, tensorflow::Tensor>> inputs = {{_input_node_name, input},{"phase_train:0", phase_tensor}};
    #else
    std::vector<std::pair<string, tensorflow::Tensor>> inputs = {{_input_node_name, input}};
    #endif

    _status = _session->Run(inputs, _output_node_names, {}, &_output_tensors);

    tf_aux::DebugOutput("NETWORK_STATUS", _status.ToString());
    return _status.ToString();
}
