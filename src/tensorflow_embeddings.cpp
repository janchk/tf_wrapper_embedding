//
// Created by jakhremchik
//

#include "tensorflow_embeddings.h"

std::vector<std::vector<float>> TensorFlowEmbeddings::getOutputEmbeddings() {
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

std::string TensorFlowEmbeddings::inference(const std::vector<cv::Mat> &imgs) {
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

bool sortbysec(const std::pair<unsigned long, float> &a, const std::pair<unsigned long, float> &b){
    return (a.second < b.second);
}

std::vector<std::pair<unsigned long, float>> TensorFlowEmbeddings::matching(std::vector<std::vector<float>> base,
                                                                            std::vector<float> target){
    std::vector<std::pair<unsigned long, float>> distances;
    std::pair<unsigned long, float> pair;
    for (unsigned long i = 0; i < base.size(); ++i) {
        float distance = this->_calc_distance(base[i], target);
        pair.first = i;
        pair.second = distance;
        distances.push_back(pair);
    }

    std::sort(distances.begin(), distances.end(), sortbysec);

    return distances;
}

float TensorFlowEmbeddings::_calc_distance(std::vector<float> base, std::vector<float> target) {
    auto base_iter  = base.begin();
    auto target_iter = target.begin();
    float sum = 0;
    for (; base_iter != base.end(); ++base_iter, ++ target_iter) {
        sum += pow((*base_iter - *target_iter), 2);
    }
    return sqrt(sum);

}
