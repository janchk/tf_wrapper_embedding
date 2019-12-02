//
// Created by jakhremchik
//

#include "tf_test.h"

using namespace std;

/// Tests required tensorflow to be compiled as shared lib!!!
using namespace tensorflow;
using namespace tensorflow::ops;

TEST(Matrix, testTFMultiply)
{
    Scope root = Scope::NewRootScope();
    // Matrix A = [3 2; -1 0]
    auto A = Const(root, { {3.f, 2.f}, {-1.f, 0.f}});
    // Vector b = [3 5]
    auto b = Const(root, { {3.f, 5.f}});
    // v = Ab^T
    auto v = MatMul(root.WithOpName("v"), A, b, MatMul::TransposeB(true));
    std::vector<Tensor> outputs;
    ClientSession session(root);
    // Run and fetch v
    TF_CHECK_OK(session.Run({v}, &outputs));
    // Expect outputs[0] == [19; -3]
//    float *m_out = outputs[0].matrix<float>().data();
    LOG(INFO) << outputs[0].matrix<float>();
//    ASSERT
    ASSERT_EQ(*outputs[0].matrix<float>().data(), 19.f);
//    ASSERT_EQ(*outputs[1].matrix<float>().data(), -3.f);
}

TEST(PATH, testClassExtraction)
{
    using namespace common_ops;
    ASSERT_ANY_THROW(extract_class(""));
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name-name/images/this_is_img__name.jpg"), "category_name-name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name-name.skip/images/this_is_img__name.jpg"), "category_name-name.skip");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name__DEVICE_NAME.trash/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/series/category_name.skip__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name.skip");

    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name-name/images/this_is_img__name.jpg"), "category_name-name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name__DEVICE_NAME.trash/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name.skip__DEVICE_NAME/images/this_is_img__name.jpg"), "category_name.skip");
    ASSERT_EQ(extract_class("/some/test/path/is_here/queries/category_name-name.skip/images/this_is_img__name.jpg"), "category_name-name.skip");
}


