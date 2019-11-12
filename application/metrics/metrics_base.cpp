//
// Created by jakhremchik
//

#include "metrics_base.h"

std::vector<WrapperBase::distance> MetricsBase::inference_and_matching(std::string img_path) {
    return WrapperBase::inference_and_matching(img_path);
}

bool IsCorrect(MetricsBase::testimg_entry &entry) { return entry.is_correct; }

float MetricsBase::getMetrics(std::string &testimg_path) {

    std::vector<std::string> test_imgs_paths = fs_img::list_imgs(testimg_path);
    testimg_entry test_img;
    WrapperBase::distance test_distance;
    std::string test_class;

    std::cout << "Start prepearing for inference" << std::endl;
    prepare_for_inference();
    std::cout << "Preparaing for inference was finished" << std::endl;

    float val_correct;

    for (const auto &test_img_path : test_imgs_paths ) {
        test_img.img_path = test_img_path;
        test_img.img_class = common_ops::extract_class(test_img_path);
        test_img.img = fs_img::read_img(test_img_path, db_handler->config.input_size);

        testimg_vector.emplace_back(test_img);
    }

    for (auto it = testimg_vector.begin(); it != testimg_vector.end(); ++it){
        test_distance = inference_and_matching(it->img_path)[0];
        test_class = common_ops::extract_class(test_distance.path);
        if (test_class == it->img_class) {
            it->is_correct = true;
        } else {
            it->is_correct = false;
            db_handler->add_error_entry(it->img_class, it->img_class, test_class);
            }
            
        }
        it->is_correct = test_class == it->img_class; //So much simplified so wow.
        it->img_class_proposed = test_class;
        it->distance = test_distance.dist;
        std::cout << it - testimg_vector.begin() << " of " << testimg_vector.size() << std::flush;
   
    }

    val_correct = std::count_if(testimg_vector.begin(), testimg_vector.end(), IsCorrect);

    std::cout << "Accuracy is : " << val_correct/testimg_vector.size() * 100.f << "%" << std::endl;

    return 0;
}

bool MetricsBase::prepare_for_inference() {
    return WrapperBase::prepare_for_inference();
}
