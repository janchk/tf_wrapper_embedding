//
// Created by jakhremchik
//

#include "tensorflow_embeddings.h"




bool TensorFlowEmbeddings::normalize_image(cv::Mat &img) {
    double  min, max;
//    cv::Mat out_img;

//    tf_aux::fastResizeIfPossible()
    cv::Scalar data = img.at<cv::Vec3b>(0,0);
    cv::minMaxLoc(img, &min, &max);
    img.convertTo(img, CV_32F, 1, 0); //TODO normalize it in a right way
    img = ((img - cv::Scalar(min, min, min)) / (max - min));
    img = (img * 2) - cv::Scalar(1);
    return true;

}

std::string TensorFlowEmbeddings::prepare_inference(std::string path, std::string db_path) {
    //open file


}

std::string TensorFlowEmbeddings::inference(const std::vector<cv::Mat> &imgs) {
    using namespace tensorflow;
    for (const cv::Mat &img : imgs) {
        auto data = &img.at<cv::Vec3b>(0,0);
        if(!tf_aux::fastResizeIfPossible(img, const_cast<cv::Mat *>(&img), cv::Size(256, 256))) {
            return "Fail to normalize images";
        }
        data = &img.at<cv::Vec3b>(0,0);
        if(!normalize_image(const_cast<cv::Mat &>(img))){
            return "Fail to normalize images";
        }
        auto fdata = &img.at<cv::Vec3f>(0,1);
        std::cout << *fdata << std::endl;
    }

    if (!tf_aux::convertMatToTensor_v2(imgs, this->_input_tensor)){
        return "Fail to convert Mat to Tensor";
    }

//    Tensor input = getConvertFunction(INPUT_TYPE::DT_FLOAT)(imgs, _input_height,
//            _input_width, _input_depth, _convert_to_float, _mean);
    //preprocess imgs first
//    Tensor input = tf_aux::convertMatToTensor_v2(imgs);
    std::vector in_tensor_shape = tf_aux::get_tensor_shape(this->_input_tensor);

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


std::vector<std::vector<float>> TensorFlowEmbeddings::getOutputEmbeddings() {
    if(_output_tensors.empty() || !_is_loaded) {
        std::cerr << "Can't get output Embeddings" << std::endl;
        return {};
    }

    if (out_embeddings.empty()){
        const auto& output = _output_tensors[0];
//        std::cout << _output_tensors[0](0,0) std::endl;
        out_embeddings = convertTensorToVector(output);

    }

    return out_embeddings;
}


std::vector<std::vector<float>> TensorFlowEmbeddings::convertTensorToVector(const tensorflow::Tensor &tensor) {
    const auto &temp_tensor = tensor.tensor<float, 2>();
    const auto &dims = tensor.shape();
//    auto eig_vec = tensor.matrix<tensorflow::bfloat16>();
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
            std::cout <<  uchar( temp_tensor(batch_size, embedding_size)) << " ";
//            temp_vec.push_back(uchar( temp_tensor(batch_size, embedding_size)));
            std::cout << temp_tensor(batch_size, embedding_size) << " "; //for debug
        }
        std::cout << std::endl; //for debug

        vec_embeddings.push_back(temp_vec);
    }

    return vec_embeddings;

}
