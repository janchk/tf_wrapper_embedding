//
// Created by jakhremchik
//

#include "common/common_ops.h"
#include "gtest/gtest.h"

TEST(PATH, testLoadUnexistedConfig)
{
   auto *data_handler = new DataHandling;
   data_handler->config_path = "unexisted_config.json";
   ASSERT_FALSE(data_handler->load_config());
}

TEST(PATH, testLoadConfig)
{
    auto *data_handler = new DataHandling;
    data_handler->config_path = "sample_config.json";
    data_handler->load_config();
    auto config = data_handler->config;

    ASSERT_EQ(config.input_size, cv::Size(256, 256));
    ASSERT_EQ(config.datafile_path, "this/is/test/path/testdatafile.txt");
    ASSERT_EQ(config.imgs_path, "this/is/test/path/test_img_path/");
    ASSERT_EQ(config.pb_path,"this/is/test/path/testpb.pb");
    ASSERT_EQ(config.input_node, "test_input_node:0");
    ASSERT_EQ(config.output_node, "test_output_node:0");

    common_ops::delete_safe(data_handler);
}

TEST(DATABASE, testLoadDatabase)
{
    auto *data_handler = new DataHandling;
    data_handler->config_path = "sample_config.json";
    data_handler->load_config();
    data_handler->load_database();

    ASSERT_EQ(data_handler->data_vec_base[0].filepath, "/this/is/test/path/testimg.jpg");
    ASSERT_EQ(data_handler->data_vec_base[0].embedding[0], -0.12846693396568299);

    common_ops::delete_safe(data_handler);
}

TEST(DATABASE, testAddJsonEntry)
{
    auto *data_handler = new DataHandling;

    auto new_entry = DataHandling::data_vec_entry();
    new_entry.filepath = "this/is/test/filepath/testimg1.jpg";
    new_entry.embedding = {0.0010000000474974514};

    data_handler->config_path = "sample_config.json";
    data_handler->load_config();
    data_handler->load_database();
    data_handler->add_json_entry(new_entry);

    data_handler->load_database();

    ASSERT_EQ(data_handler->data_vec_base[1].filepath, "this/is/test/filepath/testimg1.jpg");
    ASSERT_EQ(data_handler->data_vec_base[1].embedding[0], 0.0010000000474974514);

    common_ops::delete_safe(data_handler);


}
