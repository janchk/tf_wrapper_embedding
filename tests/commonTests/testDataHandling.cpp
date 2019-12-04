//
// Created by jakhremchik
//

#include "common/common_ops.h"
#include "gtest/gtest.h"

TEST(PATH, testLoadConfig)
{
    auto *data_handler = new DataHandling;
    data_handler->config_path = "sample_config.json";
    data_handler->load_config();
    auto config = data_handler->config;
    ASSERT_EQ(config.input_size, cv::Size(256, 256));
    ASSERT_EQ(config.datafile_path, "/this/is/test/path/testdatafile.txt");
    ASSERT_EQ(config.imgs_path, "/this/is/test/path/test_img_path/");
    ASSERT_EQ(config.pb_path,"/this/is/test/path/testpb.pb");
    ASSERT_EQ(config.input_node, "test_input_node:0");
    ASSERT_EQ(config.output_node, "test_output_node:0");
}

