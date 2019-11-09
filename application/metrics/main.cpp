//
// Created by jakhremchik
//
#include "metrics_base.h"

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
        std::cout << "Use --test_path $path for images to test$"
                  << std::endl;
        return 0;
    }
    return ret;
}



int main(int argc, char *argv[]) {
    auto *tf_wrapper = new MetricsBase();
    std::string const inPath = parseCommandLine(argc, argv, std::string("--test_path"));
    tf_wrapper->getMetrics((std::string &) inPath);
    std::cout << "Using TOP"<< tf_wrapper->topN << std::endl;

}