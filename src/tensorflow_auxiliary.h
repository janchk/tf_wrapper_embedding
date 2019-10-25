//
// Created by jakhremchik
//

#ifndef TF_WRAPPER_EMBEDDING_TENSORFLOW_AUXILIARY_H
#define TF_WRAPPER_EMBEDDING_TENSORFLOW_AUXILIARY_H
#define TFDEBUG

#include "opencv/cv.h"
#include "opencv/cv.hpp"

#include "tensorflow/core/public/session.h"
#include "tensorflow/core/graph/default_device.h"

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
    void fastResizeIfPossible(const cv::Mat& in, cv::Mat *dist, const cv::Size& size);

    /// \brief function to convert output tensor of embeddings to vector of embeddings
    /// \param tensor
    /// \return Vector of embeddings
    std::vector<std::vector<float>> convertTensorToVector(const tensorflow::Tensor& tensor);

    ///
    /// \param img
    /// \return
    tensorflow::Tensor convertMatToTensor_v2(cv::Mat img);

    ///
    /// \param tensor
    /// \return
    std::vector<int> get_tensor_shape(tensorflow::Tensor& tensor);

    /// \brief convertTensorToMat Converts batch of Mats to Tensor format
    /// \param imgs Vector of images (batch) of cv::Mat format, they must be uchar type
    /// \param height Output Tensor height
    /// \param width Output Tensor width
    /// \param depth Output Tensor depth
    /// \return Ready to inference Tensor with batch of images
    template<tensorflow::DataType T>
    tensorflow::Tensor convertMatToTensor(const std::vector<cv::Mat>& imgs, int height, int width, int depth,
                                           bool normalize, const std::vector<float>& mean) {

        using namespace tensorflow;

        if (mean.size() != depth) {
            std::cerr << "convertMatToTensor: wrong mean or channel size!" << std::endl;
            return Tensor();
        }

        Tensor input(T, TensorShape({imgs.size(), height, width, depth}));

        using POD_type = typename tensorflow::EnumToDataType<T>::Type;
        auto input_tensor_mapped = input.tensor<POD_type, 4>();
//        auto input_tensor_mapped = input.tensor<float, 4>();

        const auto batch_size = imgs.size();
        for(size_t i = 0; i < batch_size; ++i)
        {
            cv::Mat img;
    #ifdef TFDEBUG
        {
        PROFILE_BLOCK("resize img");
    #endif
            fastResizeIfPossible(imgs[i], &img, cv::Size(width, height));
    #ifdef TFDEBUG
         }
    #endif

    #ifdef TFDEBUG
        {
        PROFILE_BLOCK("convert img");
    #endif
            img.forEach<cv::Vec3b>([&](cv::Vec3b& pixel, const int position[]) -> void {
                for (short c = 0; c < 3; ++c) {
                    POD_type val(pixel[c]);
                    val -= mean[c];
                    if(normalize)
                    {
                        val /= 255.0;
                        val -= 0.5;
                        val *= 2.0;
                    }
                    // "2 - c" performs cv::COLOR_BGR2RGB
                    input_tensor_mapped(i, position[0], position[1], 2 - c) = val;
                }
            });
    #ifdef TFDEBUG
        }
    #endif
        }
        return input;
}


struct profiler {
    std::string name;
    std::chrono::high_resolution_clock::time_point p;
    profiler(std::string const &n) :
        name(n), p(std::chrono::high_resolution_clock::now()) { }
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
