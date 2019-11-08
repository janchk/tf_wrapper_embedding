//
// Created by jakhremchik
//

#include "metrics_base.h"

std::vector<WrapperBase::distance> MetricsBase::inference_and_matching(std::string img_path) {
    return WrapperBase::inference_and_matching(img_path);
}

float MetricsBase::getMetrics(std::string &testimg_path) {

    std::vector<std::string> test_imgs_paths = fs_img::list_imgs(testimg_path);
    testimg_entry test_img;
    WrapperBase::distance test_distance;
    std::string test_class;

    for (const auto &test_img_path : test_imgs_paths ) {
        test_img.img_path = test_img_path;
        test_img.img_class = common_ops::extract_class(test_img_path);
        test_img.img = fs_img::read_img(test_img_path, db_handler->config.input_size);

        testimg_vector.emplace_back(test_img);
    }

    for (auto &entry : testimg_vector) {
        test_distance = inference_and_matching(entry.img_path)[0];
        test_class = common_ops::extract_class(test_distance.path);
        entry.is_correct = test_class == entry.img_class; //So much simplified so wow.
    }



    return 0;
}

bool MetricsBase::prepare_for_inference() {
    return WrapperBase::prepare_for_inference();
}
