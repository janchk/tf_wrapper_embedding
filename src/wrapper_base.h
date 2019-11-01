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

    bool prepare_for_inference();
//    bool inference_and_matching();
protected:
    DatabaseHandling *db_handler;
    TensorFlowEmbeddings *inference_handler;
    std::vector<std::string> list_of_imgs;

    bool add_updates();
    bool check_for_updates();

};

#endif //TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
