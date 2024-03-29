//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
#define TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H

#include "common/fs_handling.h"
#include "tensorflow_embeddings.h"

namespace EmbeddingMatching
{
   static float calc_distance_euclid(std::vector<float> base, std::vector<float> target);

   float calc_distance_cosine(std::vector<float> base, std::vector<float> target);
}

class WrapperBase
{
public:

    WrapperBase()
    {
        db_handler = new DataHandling();

        inference_handler = new TensorFlowEmbeddings();

        topN = 1;
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

    unsigned int topN;

    /// In case you want specific config to be used
    /// \param path to config
    /// \return if custom config is used
    bool setConfigPath(std::string path);

    /// \brief main method used for reading images in directory and adding the to th database
    /// \return
    virtual bool prepare_for_inference();

    /// \brief main method used for matching passed image with images that already in database
    /// \param img_path passed image
    /// \return vector of distances between passed image and db images
    virtual std::vector<WrapperBase::distance> inference_and_matching(std::string img_path);

protected:
    DataHandling *db_handler;
    TensorFlowEmbeddings *inference_handler;
    std::vector<std::string> list_of_imgs;
    std::vector<WrapperBase::distance> distances;

    std::vector<std::string> _input_nodes;
    std::vector<std::string> _output_nodes;

//    static float _calc_distance(std::vector<float> base, std::vector<float> target);

    bool _matching(std::vector<DataHandling::data_vec_entry> &base, std::vector<float> &target);

    bool _add_updates();
    bool _check_for_updates();

};



#endif //TF_WRAPPER_EMBEDDING_WRAPPER_BASE_H
