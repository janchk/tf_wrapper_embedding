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

    cv::Mat read_img(const std::string& im_filename);

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

   // important variable. It contains information of image paths and corresponding embeddings.
    std::vector<data_vec_entry> data_vec_base;

    //TODO MOVE IT OUT
    std::string datafile_path = "/media/jakhremchik/ubuntuHD/PROJECTS/test_imgs/data.txt";
    std::string imgs_path = "/media/jakhremchik/ubuntuHD/PROJECTS/test_imgs/";
    bool load_database();
protected:
    std::fstream imgs_datafile;

    std::vector<std::pair<cv::Mat, std::string>> imgs_and_paths;

    bool open_datafile();
//    bool load_database();
    bool add_json_entry();


};



#endif //TF_WRAPPER_EMBEDDING_FS_HANDLING_H
