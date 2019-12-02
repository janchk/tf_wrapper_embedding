//
// Created by ucLh
//

#ifndef TF_WRAPPER_WRAPPER_BASE_TESTS_H
#define TF_WRAPPER_WRAPPER_BASE_TESTS_H

#include "../tf_test/tf_test.h"
#include "wrapper_base.h"

class WrapperBaseTest : public WrapperBase {
public:
    static float wrap_calc_distance(std::vector<float> &base, std::vector<float> &target) {
        return _calc_distance(base, target);
    }
};

#endif //TF_WRAPPER_WRAPPER_BASE_TESTS_H
