//
// Created by jakhremchik
//

#include "wrapper_base.h"
#include "gtest/gtest.h"

TEST(EXECUTION, EXECUTION_Acceptance_Test)
{
    std::string inFileName = "/home/jakhremchik/CLionProjects/TF_WRAPPER_EMBEDDING/tests/test_data/queries/helsinki_1_andante/IMG_7813_4.jpg";
    std::string gt_class = common_ops::extract_class(inFileName);
    auto *tf_wrapper = new WrapperBase();
    tf_wrapper->setConfigPath( "config.json");
    tf_wrapper->prepare_for_inference();
    tf_wrapper->topN = 1;

    std::vector<WrapperBase::distance> results = tf_wrapper->inference_and_matching(inFileName);
    std::string predicted_class = common_ops::extract_class(results[0].path);
    ASSERT_EQ(predicted_class, gt_class);



}
