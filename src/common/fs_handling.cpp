//
// Created by jakhremchik
//

#include "fs_handling.h"
//TODO add if exception to lng dependent fs
//#include <experimental/filesystem>


std::vector<cv::Mat> read_batch(const std::string &imgs_path, int batch_size) {
    std::vector<cv::Mat> batch;
    cv::Mat batch_image;
    batch.push_back(batch_image);

//    batch_image = cv::imread()
}

cv::Mat fs_img::read_img(const std::string& im_filename) {
    cv::Mat img;
    img = cv::imread(im_filename, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    return img;
}

bool path_is_img(std::string path){
    if (path.substr(path.find_last_of(".") + 1) == "jpg") {
        return true;
    }
    else {
        return false;
    }
    
}

std::vector<std::pair<cv::Mat, std::string>> fs_img::read_imgs(const std::string &dir_path) {
    std::vector<std::pair<cv::Mat, std::string>> vector_of_data;
    cv::Mat img;
    cv::Size size = cv::Size(256, 256); // TODO move out this param
    for (const auto &entry : fs::recursive_directory_iterator(dir_path)) {
        if (fs::is_regular_file(entry) && path_is_img(entry.path())) {
            img = read_img(entry.path());
            tf_aux::fastResizeIfPossible(img, const_cast<cv::Mat *>(&img), size);
            vector_of_data.push_back(std::make_pair(img, entry.path()));
        }

    }
    return vector_of_data;

}
