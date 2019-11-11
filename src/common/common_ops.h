//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_COMMON_OPS_H
#define TF_WRAPPER_COMMON_OPS_H

#include "fs_handling.h"

namespace common_ops
{
    /// \brief
    /// \param filepath
    /// \return
    std::string extract_class(const std::string &filepath);

    std::vector<std::string> split(const std::string &text, const std::string &delim);

    std::string extract_class_depth_based(const std::string &filepath);
}

#endif //TF_WRAPPER_COMMON_OPS_H
