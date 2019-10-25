#include <iostream>
#include "tensorflow_wrapper_core.h"
#include "common/fs_handling.h"
#include "tensorflow_embeddings.h"

#include <vector>
#include <string>
#include <algorithm>

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}


std::string parseCommandLine(int argc, char *argv[], std::string c) {
    std::string ret;
    if (cmdOptionExists(argv, argv + argc, c)) {
        char *filename = getCmdOption(argv, argv + argc, c);
        ret = std::string(filename);
    } else {
        std::cout << "Use -f $image$"
                     " -pb frozen.pb"
                     "-batch sizeOfButch"
                  << std::endl;
        return 0;
    }
    return ret;
}


int main(int argc, char *argv[]) {
    std::vector<std::vector<float>> output;
    auto *tf_embed = new TensorFlowEmbeddings();
    std::string const inFileName = parseCommandLine(argc, argv, std::string("-img"));
    std::string m_tfNetPath = parseCommandLine(argc, argv, std::string("-pb"));
    std::string const m_tfInputNode = parseCommandLine(argc, argv, std::string("--input_node"));
//    std::string batchSizeStr = parseCommandLine(argc, argv, std::string("-batch"));
//    std::string numTurnStr = parseCommandLine(argc, argv, std::string("-Nturn"));


    cv::Mat img = fs_img::read_img(inFileName);
    tf_embed->load(m_tfNetPath, m_tfInputNode);


    tf_embed->inference({img});
    output = tf_embed->getOutputEmbeddings();

    return 0;
}