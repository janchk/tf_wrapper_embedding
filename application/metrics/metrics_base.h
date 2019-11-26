//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_METRICS_BASE_H
#define TF_WRAPPER_METRICS_BASE_H

#include "wrapper_base.h"

class MetricsBase : public WrapperBase
{
public:
    MetricsBase()
    {
        db_handler->config_path = "../../../application/metrics/config.json";

//        db_handler->load_config();
    };

    ~MetricsBase() = default;


    float getMetrics(std::string &testimg_path);

    std::vector<WrapperBase::distance> inference_and_matching(std::string img_path) override;

//    std::string inference(const std::vector<cv::Mat> &imgs) override;

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
