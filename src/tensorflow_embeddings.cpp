//
// Created by jakhremchik
//

#include "tensorflow_embeddings.h"

std::vector<std::vector<float>> TensorFlowEmbeddings::getOutputEmbeddings()
{
    if(_output_tensors.empty())
        return {};

    if (embeddings.empty()){
        const auto& output = _output_tensors[0];
        embeddings = tf_base::convertTensorToVector(output);

    }

    return embeddings;
}
