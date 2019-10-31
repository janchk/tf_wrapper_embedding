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
