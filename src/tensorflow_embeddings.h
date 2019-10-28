//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
#define TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H

#include "tensorflow_wrapper_core.h"
#include "tensorflow_base.h"
#include "math.h"

class TensorFlowEmbeddings : public TensorflowWrapperCore
{
public:
    TensorFlowEmbeddings() = default;
    virtual ~TensorFlowEmbeddings() = default;

    int batch_size;

    std::string inference(const std::vector<cv::Mat> &imgs) override;
    std::vector<std::vector<float>> getOutputEmbeddings();
    std::vector<std::pair<unsigned long, float>> matching(std::vector<std::vector<float>> base, std::vector<float> target);


protected:
    tensorflow::Status _status;
//    virtual void clearSession();
    std::vector<std::vector<float>> embeddings;
    float _calc_distance(std::vector<float> base, std::vector<float> target);


};

#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
