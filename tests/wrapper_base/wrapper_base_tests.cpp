//
// Created by ucLh
//

#include "wrapper_base_tests.h"

using namespace std;



TEST(Distance, test_calc_distance) {
    vector<float> base{1.f, 2.f, 2.f};
    vector<float> target{3.f, -4.f, 5.f};

    float dist = WrapperBaseTest::wrap_calc_distance(base, target);
    ASSERT_EQ(dist, 7.f);

}
