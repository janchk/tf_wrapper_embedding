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

//class WrapperDBInterface : public DBInterface
//{
//public:
//
//    bool set_config_path(std::string path) override {return db.set_config_path(path);};
//
//    bool load_config() override {return db.load_config();};
//
//    bool load_colors() override {return db.load_colors();}
//
//    cv::Size get_config_input_size() override {return db.get_config_input_size();}
//
//    std::string get_config_input_node() override {return db.get_config_input_node();}
//
//    std::string get_config_output_node() override {return db.get_config_output_node();}
//
//    std::string get_config_pb_path() override {return db.get_config_pb_path();}
//
//    std::string get_config_colors_path() override {return db.get_config_colors_path();}
//
//    std::vector<std::array<int, 3>> get_colors() override {return db.get_colors();}
//
//    bool set_config_input_size(const cv::Size& size) override {return db.set_config_input_size(size);}
//
//    bool set_config_input_node(const std::string& input_node) override {return db.set_config_input_node(input_node);}
//
//    bool set_config_output_node(const std::string& output_node) override {return db.set_config_output_node(output_node);}
//
//    bool set_config_pb_path(const std::string& pb_path) override {return db.set_config_pb_path(pb_path);}
//
//    bool set_config_colors_path(const std::string& colors_path) override {return db.set_config_colors_path(colors_path);}
//
//private:
//
//    DataHandling db;
//
//};

#endif //TF_WRAPPER_WRAPPER_INTERFACES_H
