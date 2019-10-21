//
// Created by jakhremchik on 21.10.2019.
//

#include "image_handling.h"
//TODO add if exception to lng dependent fs
//#include <experimental/filesystem>


//std::vector<cv::Mat> read_batch()
//{
////    using namespace cv;
//    std::vector<cv::Mat> batch;
//    cv::Mat batch_image;
//
//    batch_image = cv::imread()
//}

cv::Mat read_image(std::string im_filename)
{
    cv::Mat img;
    img = cv::imread(im_filename, cv::IMREAD_COLOR);
    return img;
}
