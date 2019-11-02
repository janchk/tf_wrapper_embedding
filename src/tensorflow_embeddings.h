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


    std::string inference(const std::vector<cv::Mat> &imgs) override;
    std::vector<std::vector<float>> getOutputEmbeddings();
    bool normalize_image(cv::Mat &img);

    /// \brief function to convert output tensor of embeddings to vector of embeddings
    /// \param tensor
    /// \return Vector of embeddings
    static  std::vector<std::vector<float>> convertTensorToVector(const tensorflow::Tensor& tensor);


protected:
    tensorflow::Status _status;
    tensorflow::Tensor _input_tensor;
    std::vector<std::vector<float>> out_embeddings;

};

#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
