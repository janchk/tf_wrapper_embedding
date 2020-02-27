//
// Created by jakhremchik
//

#include "tf_wrapper/wrapper_base.h"
#include "tf_wrapper/common/common_ops.h"
#include "gtest/gtest.h"

class WrapperBaseWrapper : public WrapperBase {
public:
    auto setConfigPath(const std::string &path) {
        this->db_handler->set_config_path(path);
    }
};

TEST(EXECUTION, EXECUTION_Acceptance_Test)
{
    std::string inFileName = "queries/helsinki_1_andante/IMG_7813_4.jpg";
    std::string gt_class = common_ops::extract_class(inFileName);
    auto *tf_wrapper = new WrapperBaseWrapper();
    tf_wrapper->setConfigPath( "config.json");
    tf_wrapper->prepare_for_inference();
    tf_wrapper->topN = 1;

    std::vector<WrapperBase::distance> results = tf_wrapper->inference_and_matching(inFileName);
    std::string predicted_class = common_ops::extract_class(results[0].path);
    ASSERT_EQ(predicted_class, gt_class);
    common_ops::delete_safe(tf_wrapper);
}
