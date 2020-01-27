//
// Created by ucLh
//

#include "gtest/gtest.h"
#include "metrics_base.h"
#include <algorithm>

class MetricsBaseWrapper : public MetricsBase {
public:
    std::vector<std::string> choose_classes_wrapper (const std::vector<WrapperBase::distance>& matched_images_list,
                                             std::vector<testimg_entry>::iterator &it,
                                             unsigned int top_N_classes=2) {
        return MetricsBase::choose_classes(matched_images_list, it, top_N_classes);
    }
};

TEST(_choose_classes, _chooses_topN_unique_classes)
{
    auto *wrapper = new MetricsBaseWrapper;

    std::vector<WrapperBase::distance> image_list = {{0.1, "series/build1/img/a.jpg"},
                                                     {0.2, "series/build2/img/a.jpg"},
                                                     {0.2, "series/build1/img/a.jpg"},
                                                     {0.2, "series/build3/img/a.jpg"},
                                                     {0.2, "series/build2/img/a.jpg"},
                                                     {0.2, "series/build4/img/a.jpg"},
                                                     {0.2, "series/build5/img/a.jpg"},
                                                     {0.2, "series/build6/img/a.jpg"},
                                                     {0.2, "series/build7/img/a.jpg"},};

    MetricsBase::testimg_entry img_entry;
    img_entry.img_class = "build2";
    std::vector<MetricsBase::testimg_entry> img_entry_vec = {img_entry};
    auto iter = img_entry_vec.begin();
    auto res_vec = wrapper->choose_classes_wrapper(image_list, iter, 5);
    ASSERT_TRUE(img_entry.is_correct);
    ASSERT_TRUE(std::find(res_vec.begin(), res_vec.end(), "build1") != res_vec.end());
    ASSERT_TRUE(std::find(res_vec.begin(), res_vec.end(), "build2") != res_vec.end());
    ASSERT_TRUE(std::find(res_vec.begin(), res_vec.end(), "build3") != res_vec.end());
    ASSERT_TRUE(std::find(res_vec.begin(), res_vec.end(), "build4") != res_vec.end());
    ASSERT_TRUE(std::find(res_vec.begin(), res_vec.end(), "build5") != res_vec.end());
    ASSERT_FALSE(std::find(res_vec.begin(), res_vec.end(), "build6") != res_vec.end());
    ASSERT_FALSE(std::find(res_vec.begin(), res_vec.end(), "build7") != res_vec.end());
};
