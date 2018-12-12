#include <clothsimlib.cpp>
#include <gtest/gtest.h>
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(ClothSim, userCtor)
{
    ClothSim c(10, 10, 1.0f);

    EXPECT_EQ(c.m_initpatchsize,1.0f);
    EXPECT_EQ(c.m_width,10);
    EXPECT_EQ(c.m_length,10);
    EXPECT_EQ(c.m_ppos.size(),100);

}

TEST(ClothSim, setPointMass)
{
    ClothSim c(10, 10, 1.0f);

    EXPECT_EQ()

}
