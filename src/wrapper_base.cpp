//
// Created by jakhremchik
//

#include "wrapper_base.h"



bool WrapperBase::prepare_for_inference() {
//    auto *db_handler = new DataHandling();
//    db_handler->datafile_path = "";
//    db_handler->imgs_path = "";


    db_handler->load_config();
    std::cout << "Config was loaded" << std::endl;
    db_handler->load_database();
    std::cout << "Database was loaded" << std::endl;
    this->list_of_imgs = fs_img::list_imgs(db_handler->config.imgs_path); //TODO rewrite it
    this->_check_for_updates();
    if (!list_of_imgs.empty())
        this->_add_updates();
    else
       std::cout << "No new images found" << std::endl;

    this->_input_nodes = {db_handler->config.input_node};
    this->_output_nodes = {db_handler->config.output_node};

}

std::vector<WrapperBase::distance> WrapperBase::inference_and_matching(std::string img_path) {
    std::vector<float> embedding;

    cv::Mat img = fs_img::read_img(img_path, db_handler->config.input_size);

    if(!inference_handler->isLoaded())
        inference_handler->load(db_handler->config.pb_path, this->_input_nodes[0]);

    inference_handler->set_input_output(this->_input_nodes, this->_output_nodes);
    inference_handler->inference({img});

    embedding = inference_handler->getOutputEmbeddings()[0];

    this->_matching(db_handler->data_vec_base, embedding);
    inference_handler->clearSession();

    return distances;
}

bool WrapperBase::_add_updates() {
    cv::Mat img;
    inference_handler->load(db_handler->config.pb_path, db_handler->config.input_node);
    std::vector<float> out_embedding; //TODO remember about batch
    DataHandling::data_vec_entry new_data;
    for (const auto &img_path : this->list_of_imgs) {
        img = fs_img::read_img(img_path, db_handler->config.input_size);
        inference_handler->inference({img}); //TODO remember about batch
        new_data.embedding = inference_handler->getOutputEmbeddings()[0]; //TODO BATCH
        inference_handler->clearSession();
        new_data.filepath = img_path;
        db_handler->data_vec_base.push_back(new_data);
        db_handler->add_json_entry(new_data);
    }

}

bool WrapperBase::_check_for_updates() {
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
            std::cout << "Found new data " << entry << std::endl;
        }
    }

    return true;
}
bool sortbydist(const WrapperBase::distance &a, const WrapperBase::distance &b){
    return (a.dist < b.dist);
}

bool WrapperBase::_matching(std::vector<DataHandling::data_vec_entry> &base,
                            std::vector<float> &target){
    this->distances.clear();
    WrapperBase::distance distance;

    for (auto & it : base) {
        distance.dist = WrapperBase::_calc_distance(it.embedding , target);
        distance.path = it.filepath;
        this->distances.push_back(distance);
    }
    std::sort(this->distances.begin(), this->distances.end(), sortbydist);
    if (topN > this->distances.size())
        topN = this->distances.size();
    this->distances.erase(this->distances.begin() + topN, this->distances.end());

    return true;
}

float WrapperBase::_calc_distance(std::vector<float> base, std::vector<float> target) {
    float sum = 0;
    auto target_it = target.begin();
    for (auto base_it = base.begin(); base_it !=base.end(); ++base_it, ++target_it) {
        sum += pow((*base_it - *target_it), 2);
    }
    return sqrt(sum);

}


