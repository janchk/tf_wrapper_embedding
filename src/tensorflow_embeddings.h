//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
#define TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H

#include "tensorflow_wrapper_core.h"
#include "tensorflow_base.h"
#include "opencv2/imgproc/imgproc.hpp"
#include <cmath>

class TensorFlowEmbeddings : public TensorflowWrapperCore
{
public:
    TensorFlowEmbeddings() = default;
    virtual ~TensorFlowEmbeddings() = default;

    int batch_size;

    std::string prepare_inference (std::string path);

    std::string inference(const std::vector<cv::Mat> &imgs) override;
    std::vector<std::vector<float>> getOutputEmbeddings();
    std::vector<std::pair<unsigned long, float>> matching(std::vector<std::vector<float>> base, std::vector<float> target);
    bool normalize_image(cv::Mat &img);

    /// \brief function to convert output tensor of embeddings to vector of embeddings
    /// \param tensor
    /// \return Vector of embeddings
    std::vector<std::vector<float>> convertTensorToVector(const tensorflow::Tensor& tensor);


protected:


    tensorflow::Status _status;
    tensorflow::Tensor _input_tensor;
//    virtual void clearSession();
    std::vector<std::vector<float>> embeddings;
    float _calc_distance(std::vector<float> base, std::vector<float> target);


};

#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
