//
// Created by jakhremchik
//

#include "wrapper_base.h"
#include "gtest/gtest.h"

class WrapperBaseWrapper : WrapperBase {
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
