//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_METRICS_BASE_H
#define TF_WRAPPER_METRICS_BASE_H

#include "wrapper_base.h"
#include <algorithm>

class MetricsBase : public WrapperBase
{
public:
    MetricsBase()
    {
//        this->topN = 5;
        this->setConfigPath("config.json");
    };

    ~MetricsBase() = default;

    /// using accuracy as metrics
    /// \param testimg_path path to test image
    /// \return value of accuracy
    float getMetrics(std::string &testimg_path);

    std::vector<WrapperBase::distance> inference_and_matching(std::string img_path) override;


    struct testimg_entry {
        std::string img_path;
        std::string img_class;
        std::string img_class_proposed;
        cv::Mat img;
        float distance;
        bool is_correct;
        //TODO add correction distance
    };
protected:

    std::vector<testimg_entry> testimg_vector;


    bool prepare_for_inference() override;


};

#endif //TF_WRAPPER_METRICS_BASE_H
