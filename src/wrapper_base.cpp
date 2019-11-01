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
    this->add_updates();



}

bool WrapperBase::add_updates() {
    cv::Mat img;
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


//    for (const auto &new_img)

}

bool WrapperBase::check_for_updates() {
    for (auto img_path=this->list_of_imgs.begin(); img_path!=this->list_of_imgs.end(); ++img_path) {
        for (const auto &entry : db_handler->data_vec_base ) {
            if (*img_path == entry.filepath) {
                list_of_imgs.erase(img_path);
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
