//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_FS_HANDLING_H
#define TF_WRAPPER_EMBEDDING_FS_HANDLING_H

#include "opencv/cv.h"
#include "opencv/cv.hpp"
#include "vector"
#include "string"
#include "fstream"


#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"

#include "../tensorflow_auxiliary.h"

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

    cv::Mat read_img(const std::string &im_filename, cv::Size &size);

    std::vector<std::string> list_imgs(const std::string & dir_path);
}

class DatabaseHandling
{
public:
    DatabaseHandling() = default;
    virtual ~DatabaseHandling() = default;

    struct data_vec_entry
    {
        std::string filepath;
        std::vector<float> embedding;
    };
    struct config_data {
        cv::Size input_size;
        std::string datafile_path;
        std::string imgs_path;
        std::string input_node;
        std::string pb_path;
    };

    // struct with all config data
    config_data config;

   // important variable. It contains information of image paths and corresponding embeddings.
    std::vector<data_vec_entry> data_vec_base;

    //TODO MOVE IT OUT
    bool load_database();
    bool load_config();
    bool add_json_entry(data_vec_entry new_data);

protected:
    std::fstream imgs_datafile;
    std::fstream config_datafile;

    std::string config_path = "../config.json";

    std::vector<std::pair<cv::Mat, std::string>> imgs_and_paths;

    bool open_datafile();
    bool open_config();
};



#endif //TF_WRAPPER_EMBEDDING_FS_HANDLING_H
