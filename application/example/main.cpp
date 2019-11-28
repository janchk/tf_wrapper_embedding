#include <iostream>
#include "wrapper_base.h"

#include <vector>
#include <string>
#include <algorithm>

char *getCmdOption(char **begin, char **end, const std::string &option) {
    char **itr = std::find(begin, end, option);
    if (itr != end && ++itr != end) {
        return *itr;
    }
    return nullptr;
}

bool cmdOptionExists(char **begin, char **end, const std::string &option) {
    return std::find(begin, end, option) != end;
}


std::string parseCommandLine(int argc, char *argv[], const std::string& c) {
    std::string ret;
    if (cmdOptionExists(argv, argv + argc, c)) {
        char *filename = getCmdOption(argv, argv + argc, c);
        ret = std::string(filename);
    } else {
        std::cout << "Use -img $image$"
                  << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return ret;
}


int main(int argc, char *argv[]) {
    std::string const inFileName = parseCommandLine(argc, argv, std::string("-img"));

    auto *tf_wrapper = new WrapperBase();
    tf_wrapper->prepare_for_inference();
    tf_wrapper->topN = 10;
    std::vector<WrapperBase::distance> results = tf_wrapper->inference_and_matching(inFileName);
    common_ops::delete_safe(tf_wrapper);

    for (const auto &result : results)
        std::cout << "Dst " << result.dist << " path " << result.path <<std::endl;


    return 0;
}