//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_FS_HANDLING_H
#define TF_WRAPPER_EMBEDDING_FS_HANDLING_H

#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "vector"
#include "string"

#define EXPERIMENTAL
#ifdef EXPERIMENTAL
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif
namespace fs_img
{

    cv::Mat read_img(const std::string& im_filename);

    std::vector<std::pair<cv::Mat, std::string>> read_imgs(const std::string & dir_path);
}



#endif //TF_WRAPPER_EMBEDDING_FS_HANDLING_H
