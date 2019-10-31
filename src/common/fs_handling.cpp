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
    cv::Size size = cv::Size(256, 256); // TODO move out this param
    img = cv::imread(im_filename, cv::IMREAD_COLOR);
    cv::cvtColor(img, img, cv::COLOR_BGR2RGB);
    tf_aux::fastResizeIfPossible(img, const_cast<cv::Mat *>(&img), size);
    return img;
}

bool path_is_img(std::string path){
    return path.substr(path.find_last_of(".") + 1) == "jpg";
    
}

std::vector<std::string> fs_img::list_imgs(const std::string &dir_path) {
    std::vector<std::string> vector_of_data;
    for (const auto &entry : fs::recursive_directory_iterator(dir_path)) {
        if (fs::is_regular_file(entry) && path_is_img(entry.path()))
            vector_of_data.emplace_back(entry.path());
    }
    return vector_of_data;
}

bool DatabaseHandling::open_datafile() {
   this->imgs_datafile.open(datafile_path, std::ios::in | std::ios::app);
   return true;
}

bool DatabaseHandling::load_database() {
    using namespace rapidjson;
    std::string line;
    Document doc;
    data_vec_entry base_entry;

//    this->imgs_and_paths = fs_img::read_imgs(imgs_path); //TODO probably move this out


    if (this->imgs_datafile.is_open()) {
        while (std::getline(imgs_datafile, line)) {
            doc.Parse(line.c_str());

            rapidjson::Value &img_name = doc["name"];
            rapidjson::Value &img_embedding = doc["embedding"];

            base_entry.filepath = img_name.GetString();
            for (const auto &value : img_embedding.GetObject()) {
                base_entry.embedding.emplace_back(value.value.GetFloat());
            }
            this->data_vec_base.emplace_back(base_entry);

        }

    } else {
        this->open_datafile();
        this->load_database();
    }
    return true;
}

// Adding images one by one. No batch using.
//bool DatabaseHandling::add_json_entry() {
//    using namespace rapidjson;
//    if (this->imgs_datafile.is_open()){
////        for (auto entry=imgs_and_paths.begin(); entry!=imgs_and_paths.end(); ++entry) {
////        }
//    }
//    else {
//        this->open_datafile();
//        this->add_json_entry();
//
//    }
//}