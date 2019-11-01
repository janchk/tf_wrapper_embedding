//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
#define TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H

#include "common/fs_handling.h"
#include "tensorflow_embeddings.h"
//#include ""

class WrapperBase
{
public:
    WrapperBase()
    {
        db_handler = new DatabaseHandling();
        inference_handler = new TensorFlowEmbeddings();
    }
    ~WrapperBase() = default;

    unsigned int topN;

    bool prepare_for_inference();
    bool inference_and_matching(std::string img_path);
protected:
    DatabaseHandling *db_handler;
    TensorFlowEmbeddings *inference_handler;
    std::vector<std::string> list_of_imgs;

    float _calc_distance(std::vector<float> base, std::vector<float> target);

    bool matching(std::vector<DatabaseHandling::data_vec_entry> &base, std::vector<float> &target);

    bool add_updates();
    bool check_for_updates();

};

#endif //TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
