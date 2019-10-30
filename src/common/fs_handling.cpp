//
// Created by jakhremchik
//

#include "fs_handling.h"
//TODO add if exception to lng dependent fs
//#include <experimental/filesystem>


std::vector<cv::Mat> read_batch(const std::string &imgs_path, int batch_size){
    using namespace cv;
    std::vector<cv::Mat> batch;
    cv::Mat batch_image;
    batch.push_back(batch_image);

//    batch_image = cv::imread()
}

cv::Mat fs_img::read_img(const std::string& im_filename){
    cv::Mat img;
    img = cv::imread(im_filename, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    return img;
}

std::vector<std::pair<cv::Mat, std::string>> fs_img::read_imgs(const std::string &dir_path) {
    fs

}
