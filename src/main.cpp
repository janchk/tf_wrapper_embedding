#include <iostream>
#include "tensorflow_wrapper_core.h"
#include "common/fs_handling.h"
#include "tensorflow_embeddings.h"
#include "wrapper_base.h"

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
        std::cout << "Use -img $image$"
                     " -pb frozen.pb"
                     "-batch size of batch"
                     "--input_node name of input node"
                  << std::endl;
        return 0;
    }
    return ret;
}


int main(int argc, char *argv[]) {
    std::string const inFileName = parseCommandLine(argc, argv, std::string("-img"));
    std::string const filePath = parseCommandLine(argc, argv, std::string("-path"));
    std::string m_tfNetPath = parseCommandLine(argc, argv, std::string("-pb"));
    std::string const m_tfInputNode = parseCommandLine(argc, argv, std::string("--input_node"));
    //TODO this is redundant parameter ?
    std::string batchSizeStr = parseCommandLine(argc, argv, std::string("-batch"));
//    std::string numTurnStr = parseCommandLine(argc, argv, std::string("-Nturn"));


    auto *tf_wrapper = new WrapperBase();
    tf_wrapper->prepare_for_inference();
    std::vector<WrapperBase::distance> results = tf_wrapper->inference_and_matching(inFileName);
    for (const auto &result : results)
        std::cout << "Dst " << result.dist << " path " << result.path <<std::endl;

    return 0;
}