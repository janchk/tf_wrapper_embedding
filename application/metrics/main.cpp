//
// Created by jakhremchik
//
#include "metrics_base.h"

int main(int argc, char *argv[]) {
    auto *tf_wrapper = new MetricsBase();
    std::cout << tf_wrapper->topN << std::endl;
}