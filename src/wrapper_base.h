//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
#define TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H

#include "common/fs_handling.h"
#include "tensorflow_embeddings.h"

class WrapperBase
{
public:

    WrapperBase()
    {
        db_handler = new DatabaseHandling();

        db_handler->config_path = "../../../config.json"; //Not my best decision

        inference_handler = new TensorFlowEmbeddings();
    }
    ~WrapperBase()
    {
        common_ops::delete_safe(inference_handler);
        common_ops::delete_safe(db_handler);
        common_ops::delete_safe(inference_handler);
    };

    struct distance {
        float dist;
        std::string path;
    };

    unsigned int topN = 1; //it's not very secure to set var like that, but whatever.

    /// \brief main method used for reading images in directory and adding the to th database
    /// \return
    virtual bool prepare_for_inference();

    /// \brief main method used for matching passed image with images that already in database
    /// \param img_path passed image
    /// \return vector of distances between passed image and db images
    virtual std::vector<WrapperBase::distance> inference_and_matching(std::string img_path);

protected:
    DatabaseHandling *db_handler;
    TensorFlowEmbeddings *inference_handler;
    std::vector<std::string> list_of_imgs;
    std::vector<WrapperBase::distance> distances;

    std::vector<std::string> _input_nodes;
    std::vector<std::string> _output_nodes;


    static float _calc_distance(std::vector<float> base, std::vector<float> target);

    bool _matching(std::vector<DatabaseHandling::data_vec_entry> &base, std::vector<float> &target);

    bool _add_updates();
    bool _check_for_updates();

};

#endif //TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
