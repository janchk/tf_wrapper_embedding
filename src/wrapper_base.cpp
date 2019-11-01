//
// Created by jakhremchik
//

#include "wrapper_base.h"



bool WrapperBase::prepare_for_inference() {
//    auto *db_handler = new DatabaseHandling();
//    db_handler->datafile_path = "";
//    db_handler->imgs_path = "";


    db_handler->load_database();
    this->list_of_imgs = fs_img::list_imgs(db_handler->imgs_path); //TODO rewrite it
    this->check_for_updates();
    if (!list_of_imgs.empty())
        this->add_updates();
    else
       std::cout << "No new images found" << std::endl;

}

bool WrapperBase::inference_and_matching(std::string img_path) {
    cv::Mat img = fs_img::read_img(img_path);
    std::vector<float> embedding;
    if(!inference_handler->isLoaded())
        inference_handler->load("/home/jakhremchik/Downloads/optimized_val_84.pb", "image_batch_p:0");
    inference_handler->inference({img});
    embedding = inference_handler->getOutputEmbeddings()[0];
    inference_handler->matching();





}

bool WrapperBase::add_updates() {
    cv::Mat img;
    inference_handler->load("/home/jakhremchik/Downloads/optimized_val_84.pb", "image_batch_p:0"); //TODO move out constants
    std::vector<float> out_embedding; //TODO remember about batch
    DatabaseHandling::data_vec_entry new_data;
    for (const auto &img_path : this->list_of_imgs) {
        img = fs_img::read_img(img_path);
        inference_handler->inference({img}); //TODO remember about batch
        new_data.embedding = inference_handler->getOutputEmbeddings()[0]; //TODO BATCH
        new_data.filepath = img_path;
        db_handler->data_vec_base.push_back(new_data);
        db_handler->add_json_entry(new_data);
    }

}

bool WrapperBase::check_for_updates() {
    for (const auto &entry : db_handler->data_vec_base) {
        for (auto img_path = this->list_of_imgs.begin(); img_path != this->list_of_imgs.end();) {
            if (*img_path == entry.filepath) {
                this->list_of_imgs.erase(img_path);
            } else {
                img_path++;
            }
        }
    }
    if (!list_of_imgs.empty()) {
        for (const auto &entry : list_of_imgs) {
            std::cout << "Found new data" << entry << std::endl;
        }
    }

    return true;
}
bool sortbysec(const std::pair<unsigned long, float> &a, const std::pair<unsigned long, float> &b){
    return (a.second < b.second);
}

bool WrapperBase::matching(std::vector<DatabaseHandling::data_vec_entry> &base,
                            std::vector<float> &target){

    std::vector<std::pair<unsigned long, float>> distances;
    std::pair<unsigned long, float> pair;
    for (unsigned long i = 0; i < base.size(); ++i) {
        float distance = this->_calc_distance(base[i], target);
        pair.first = i;
        pair.second = distance;
        distances.push_back(pair);
    }

    std::sort(distances.begin(), distances.end(), sortbysec);

    return distances;
}

float WrapperBase::_calc_distance(std::vector<float> base, std::vector<float> target) {
    auto base_iter  = base.begin();
    auto target_iter = target.begin();
    float sum = 0;
    for (; base_iter != base.end(); ++base_iter, ++ target_iter) {
        sum += pow((*base_iter - *target_iter), 2);
    }
    return sqrt(sum);

}


