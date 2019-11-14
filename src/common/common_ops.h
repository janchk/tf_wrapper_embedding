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

    void check_end_slash(std::string &path);

    std::vector<std::string> split(const std::string &text, const std::string &delim);

    std::string extract_class(const std::string &path_to_img, std::string &series_path, std::string &queries_path);
}

#endif //TF_WRAPPER_COMMON_OPS_H
