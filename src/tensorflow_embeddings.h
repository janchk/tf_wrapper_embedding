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

    bool set_input_output(std::vector<std::string> in_nodes, std::vector<std::string> out_nodes);

    /// \brief function for inferencing vector of input images
    /// \param imgs is vector of images
    /// \return status message
    std::string inference(const std::vector<cv::Mat> &imgs) override;

    /// \brief
    /// \return vector of output embeddings after inference
    std::vector<std::vector<float>> getOutputEmbeddings();

    /// \brief function to normalize input image
    /// \param img is an input_image
    /// \return state of processing
    bool normalize_image(cv::Mat &img);

    /// \brief function to convert output tensor of embeddings to vector of embeddings
    /// \param tensor
    /// \return Vector of embeddings
    static  std::vector<std::vector<float>> convertTensorToVector(const tensorflow::Tensor& tensor);


protected:
    tensorflow::Status _status;
    tensorflow::Tensor _input_tensor;
    std::vector<std::vector<float>> _out_embeddings;

};

#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_EMBEDDINGS_H
