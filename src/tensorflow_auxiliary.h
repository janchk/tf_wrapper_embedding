//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_TENSORFLOW_AUXILIARY_H
#define TF_WRAPPER_EMBEDDING_TENSORFLOW_AUXILIARY_H
#define TFDEBUG

#include <utility>

#include "opencv/cv.h"
#include "opencv/cv.hpp"

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"
#include "tensorflow/cc/ops/image_ops.h"

namespace tf_aux
{
    ////
    /// \brief MAX_SIZE_FOR_PYR_METHOD Max size in fastResize function for that pyrDown or pyrUp will be used
    /// (because method is slower then resize on big images).
    ///
    constexpr int MAX_SIZE_FOR_PYR_METHOD = 500;
    ///

    /// For time measure
    struct profiler;
    /// Profile helper
    #define PROFILE_BLOCK(pbn) tf_aux::profiler _pfinstance(pbn)
    inline void DebugOutput(const std::string& header, const std::string& msg) {
    #ifdef TFDEBUG
        std::cerr << header << ": " << msg << "\n";
    #endif
    }
    bool tfResizeBilinear(const cv::Mat &in, cv::Mat *dist, const cv::Size &size);
    bool fastResizeIfPossible(const cv::Mat &in, cv::Mat *dist, const cv::Size &size);


    ///
    /// \param imgs
    /// \param tensor
    /// \return
    bool convertMatToTensor_v2(const std::vector<cv::Mat> &imgs, tensorflow::Tensor &tensor);

    ///
    /// \param tensor
    /// \return
    std::vector<int> get_tensor_shape(tensorflow::Tensor &tensor);


struct profiler {
    std::string name;
    std::chrono::high_resolution_clock::time_point p;
    explicit profiler(std::string n) :
        name(std::move(n)), p(std::chrono::high_resolution_clock::now()) { }
    ~profiler()
    {
        using dura = std::chrono::duration<double>;
        auto d = std::chrono::high_resolution_clock::now() - p;
        std::cout << name << ": "
            << std::chrono::duration_cast<dura>(d).count()
            << std::endl;
    }
};

}
#endif //TF_WRAPPER_EMBEDDING_TENSORFLOW_AUXILIARY_H
