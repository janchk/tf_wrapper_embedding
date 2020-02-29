//
// Created by ucLh.
//

#ifndef TF_WRAPPER_WRAPPER_INTERFACES_H
#define TF_WRAPPER_WRAPPER_INTERFACES_H

#include "interfaces.h"

class TensorFlowEmbeddingsInterface : public EmbeddingsInterface
{
public:
    bool set_gpu_number_preferred(int value) override { return embed.set_gpu_number_preferred(value);}

    bool load(const std::string &filename, const std::string &inputNodeName) override { return embed.load(filename, inputNodeName);}

    bool set_input_output(std::vector<std::string> in_nodes, std::vector<std::string> out_nodes) override { return embed.set_input_output(
                in_nodes, out_nodes);}

    std::string inference(const std::vector<cv::Mat> &imgs) override { return embed.inference(imgs);};

    std::string get_visible_devices() override { return embed.get_visible_devices();} //Does not really work yet

    bool is_loaded() override { return embed.is_loaded(); }

    std::vector<std::vector<float>> get_output_embeddings() override { return embed.get_output_embeddings();}

    void clear_session() override { embed.clear_session();};

private:

    TensorFlowEmbeddings embed;
};

#endif //TF_WRAPPER_WRAPPER_INTERFACES_H