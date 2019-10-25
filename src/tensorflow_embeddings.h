//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
#define TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H

#include "tensorflow_wrapper_core.h"
#include "tensorflow_base.h"

class TensorFlowEmbeddings : public TensorflowWrapperCore
{
public:
    TensorFlowEmbeddings() = default;
    virtual ~TensorFlowEmbeddings() = default;

    int batch_size;

    std::string inference(const std::vector<cv::Mat> &imgs) override;
    std::vector<std::vector<float>> getOutputEmbeddings();


protected:
    tensorflow::Status _status;
//    virtual void clearSession();
    std::vector<std::vector<float>> embeddings;


};

#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
