#include "gtest/gtest.h"
#include "variant/variant.hpp"
#include "test_util.hpp"

using namespace ::testing;

using Ts = Types<void>;

template<typename TestCase>
struct VariantTest : public Test
{};

TYPED_TEST_CASE_P(VariantTest);

TYPED_TEST_P(VariantTest, DefaultConstruction_Empty)
{
    test_case::Variant<TypeParam> v;

    EXPECT_TRUE(v.empty());
}

TYPED_TEST_P(VariantTest, ConstructionFromValue_NotEmpty)
{
    test_case::Variant<TypeParam> v{TypeParam::getValue()};

    EXPECT_FALSE(v.empty());
}


REGISTER_TYPED_TEST_CASE_P(VariantTest,
                           DefaultConstruction_Empty, ConstructionFromValue_NotEmpty);



/* =========================================================== */
/* >>>>>>>>>>              TEST SETUP              <<<<<<<<<<< */
/* =========================================================== */


using variants = TypeList<
    cpp::Variant<int, char, bool>,
    cpp::Variant<std::string, std::vector<int>, char, float>,
    cpp::Variant<cpp::Variant<int, std::string>, bool>
>;

using test_cases = detail::functor_t<TestCases<variants>, Types>; 

INSTANTIATE_TYPED_TEST_CASE_P(TestMultipleVariantInstances, VariantTest, 
    test_cases
);
                           
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
    return ret;
}
