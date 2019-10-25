//
// Created by jakhremchik on 21.10.2019.
//

#ifndef TF_WRAPPER_EMBEDDING_FS_HANDLING_H
#define TF_WRAPPER_EMBEDDING_FS_HANDLING_H

#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "vector"
#include "string"

namespace fs_img
{
    cv::Mat read_img(const std::string& im_filename);
}



#endif //TF_WRAPPER_EMBEDDING_FS_HANDLING_H
