//
// Created by jakhremchik
//

#include "wrapper_base.h"
#include "gtest/gtest.h"

class WrapperBaseWrapper : public WrapperBase {
public:
    auto matchingWrapper(std::vector<DataHandling::data_vec_entry> &base, std::vector<float> &target) {
        return _matching(base, target);
    }

    auto add_updatesWrapper() {
        return _add_updates();
    }

    auto check_for_updatesWrapper() {
        return _check_for_updates();
    }

    auto distancesWrapper() {
        return distances;
    }

    auto setTopNWrapper(unsigned int N) {
        topN = N;
    }

    auto setDataVecBase(std::vector<DataHandling::data_vec_entry> &vec_base) {
        this->db_handler->data_vec_base = vec_base;
    }

    auto getDataVecBase() {
        return this->db_handler->data_vec_base;
    }

    auto setListOfImgs(std::vector<std::string> &list_of_imgs) {
        this->list_of_imgs = list_of_imgs;
    }

    auto getListOfImgs() {
        return this->list_of_imgs;
    }

    auto loadConfig() {
        return this->db_handler->load_config();
    }

    auto setNodes() {
        this->_input_nodes = {db_handler->config.input_node};
        this->_output_nodes = {db_handler->config.output_node};
    }

};


TEST(_matching, _matching_testMatchingCorrectnes_Test)
{

    auto *wrapper = new WrapperBaseWrapper;

    wrapper->setTopNWrapper(3);

    std::vector<float> test_target;

    test_target = {0.7, 0.7, 0.7};

    std::vector<DataHandling::data_vec_entry> test_base;

    DataHandling::data_vec_entry test_entry_farthest;
    DataHandling::data_vec_entry test_entry_closest;
    DataHandling::data_vec_entry test_entry_middle;

    test_entry_farthest.embedding = {0.05, 0.05, 0.05};
    test_entry_farthest.filepath = "/testpath/series/farthest_res/randimg.jpg";

    test_entry_closest.embedding = {0.6, 0.6, 0.6};
    test_entry_closest.filepath = "/testpath/series/closest_res/randimg.jpg";

    test_entry_middle.embedding = {0.3, 0.3, 0.3};
    test_entry_middle.filepath = "/testpath/series/middle_res/randimg.jpg";

    test_base.emplace_back(test_entry_farthest);
    test_base.emplace_back(test_entry_closest);
    test_base.emplace_back(test_entry_middle);


    wrapper->matchingWrapper(test_base, test_target);

    ASSERT_EQ(wrapper->distancesWrapper()[0].path, "/testpath/series/closest_res/randimg.jpg");
    ASSERT_EQ(wrapper->distancesWrapper()[1].path, "/testpath/series/middle_res/randimg.jpg");
    ASSERT_EQ(wrapper->distancesWrapper()[2].path, "/testpath/series/farthest_res/randimg.jpg");
//    wrapper->distances[0].


}

TEST(_check_for_updates, _check_no_changes) {
    std::vector<DataHandling::data_vec_entry> test_base;

    DataHandling::data_vec_entry test_entry_farthest;
    DataHandling::data_vec_entry test_entry_closest;
    DataHandling::data_vec_entry test_entry_middle;

    test_entry_farthest.embedding = {0.05, 0.05, 0.05};
    test_entry_farthest.filepath = "/testpath/series/farthest_res/randimg.jpg";

    test_entry_closest.embedding = {0.6, 0.6, 0.6};
    test_entry_closest.filepath = "/testpath/series/closest_res/randimg.jpg";

    test_entry_middle.embedding = {0.3, 0.3, 0.3};
    test_entry_middle.filepath = "/testpath/series/middle_res/randimg.jpg";

    test_base.emplace_back(test_entry_farthest);
    test_base.emplace_back(test_entry_closest);
    test_base.emplace_back(test_entry_middle);

    std::vector<std::string> test_list_of_imgs;
    test_list_of_imgs.emplace_back(test_entry_farthest.filepath);
    test_list_of_imgs.emplace_back(test_entry_closest.filepath);
    test_list_of_imgs.emplace_back(test_entry_middle.filepath);

    auto *wrapper = new WrapperBaseWrapper;
    wrapper->setDataVecBase(test_base);
    wrapper->setListOfImgs(test_list_of_imgs);
    wrapper->check_for_updatesWrapper();

    ASSERT_TRUE(wrapper->getListOfImgs().empty());
}

TEST(_check_for_updates, _check_some_changes) {
    std::vector<DataHandling::data_vec_entry> test_base;

    DataHandling::data_vec_entry test_entry_closest;
    DataHandling::data_vec_entry test_entry_middle;

    test_entry_closest.embedding = {0.6, 0.6, 0.6};
    test_entry_closest.filepath = "/testpath/series/closest_res/randimg.jpg";

    test_entry_middle.embedding = {0.3, 0.3, 0.3};
    test_entry_middle.filepath = "/testpath/series/middle_res/randimg.jpg";

    test_base.emplace_back(test_entry_closest);
    test_base.emplace_back(test_entry_middle);

    std::vector<std::string> test_list_of_imgs;
    test_list_of_imgs.emplace_back("/testpath/series/farthest_res/randimg.jpg");
    test_list_of_imgs.emplace_back(test_entry_closest.filepath);
    test_list_of_imgs.emplace_back(test_entry_middle.filepath);

    auto *wrapper = new WrapperBaseWrapper;
    wrapper->setDataVecBase(test_base);
    wrapper->setListOfImgs(test_list_of_imgs);
    wrapper->check_for_updatesWrapper();
    ASSERT_FALSE(wrapper->getListOfImgs().empty());
}

TEST(_check_for_updates, _remembers_images_that_are_not_present_anymore) {
    std::vector<DataHandling::data_vec_entry> test_base;

    DataHandling::data_vec_entry test_entry_farthest;
    DataHandling::data_vec_entry test_entry_closest;
    DataHandling::data_vec_entry test_entry_middle;

    test_entry_farthest.embedding = {0.05, 0.05, 0.05};
    test_entry_farthest.filepath = "/testpath/series/farthest_res/randimg.jpg";

    test_entry_closest.embedding = {0.6, 0.6, 0.6};
    test_entry_closest.filepath = "/testpath/series/closest_res/randimg.jpg";

    test_entry_middle.embedding = {0.3, 0.3, 0.3};
    test_entry_middle.filepath = "/testpath/series/middle_res/randimg.jpg";

    test_base.emplace_back(test_entry_farthest);
    test_base.emplace_back(test_entry_closest);
    test_base.emplace_back(test_entry_middle);

    std::vector<std::string> test_list_of_imgs;
    test_list_of_imgs.emplace_back(test_entry_farthest.filepath);
    test_list_of_imgs.emplace_back(test_entry_closest.filepath);

    auto *wrapper = new WrapperBaseWrapper;
    wrapper->setDataVecBase(test_base);
    wrapper->setListOfImgs(test_list_of_imgs);
    wrapper->check_for_updatesWrapper();

    ASSERT_TRUE(wrapper->getListOfImgs().empty());
}

TEST(_add_updates, adds_new_images) {
    auto *wrapper = new WrapperBaseWrapper;

    std::vector<DataHandling::data_vec_entry> test_base;

    DataHandling::data_vec_entry test_entry_farthest;

    test_entry_farthest.embedding = {0.05, 0.05, 0.05};
    test_entry_farthest.filepath = "/testpath/series/farthest_res/randimg.jpg";

    test_base.emplace_back(test_entry_farthest);

    std::vector<std::string> test_list_of_imgs;
    test_list_of_imgs.emplace_back("./Lenna.jpg");

    wrapper->setDataVecBase(test_base);
    wrapper->setListOfImgs(test_list_of_imgs);
    wrapper->setConfigPath("./config.json");
    wrapper->loadConfig();
    wrapper->setNodes();

    wrapper->add_updatesWrapper();

    auto new_vec_base = wrapper->getDataVecBase();

    ASSERT_EQ(new_vec_base[1].filepath, "./Lenna.jpg");
}

TEST(calc_distance_cosine, test_codine_distance_calculation) {
    std::vector<float> base{1.f, 2.f, 5.f};
    std::vector<float> target{5.f, 2.f, 1.f};

    float dist = EmbeddingMatching::calc_distance_cosine(base, target);
    ASSERT_EQ(dist, 16.f / 30.f);
}













