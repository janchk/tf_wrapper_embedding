//
// Created by ucLh.
//

#ifndef TF_WRAPPER_WRAPPER_INTERFACES_H
#define TF_WRAPPER_WRAPPER_INTERFACES_H

#include "interfaces.h"

class TensorFlowEmbeddingsInterface : public EmbeddingsInterface
{
public:
    bool setGpuNumberPreferred(int value) override { return embed.setGpuNumberPreferred(value);}

    bool load(const std::string &filename, const std::string &inputNodeName) override { return embed.load(filename, inputNodeName);}

    bool set_input_output(std::vector<std::string> in_nodes, std::vector<std::string> out_nodes) override { return embed.set_input_output(
                in_nodes, out_nodes);}

    std::string inference(const std::vector<cv::Mat> &imgs) override { return embed.inference(imgs);};

    std::string getVisibleDevices() override { return embed.getVisibleDevices();} //Does not really work yet

    bool isLoaded() override { return embed.isLoaded(); }

    std::vector<std::vector<float>> getOutputEmbeddings() override { return embed.getOutputEmbeddings();}

    void clearSession() override {embed.clearSession();};

private:

    TensorFlowEmbeddings embed;
};

#endif //TF_WRAPPER_WRAPPER_INTERFACES_H
