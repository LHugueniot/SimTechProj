//#include "clothsimlib_global.h"

#include <clothsimlib.h>
#include <gtest/gtest.h>

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//TEST(ClothSim, makeMesh1)
//{
//    PBD::ClothSim c;
//    c.makeMesh1(3,3,0.5f);

//    EXPECT_EQ(c.m_initpatchsize,0.5f);
//    EXPECT_EQ(c.m_width,3);
//    EXPECT_EQ(c.m_height,3);
//    EXPECT_EQ(c.m_ppos.size(),9 * 6);

//}

TEST(ClothSim, makeMesh)
{
    PBD::ClothSim c;
    c.makeMesh(glm::vec3(0,0,0),3,3,0.5);
    EXPECT_EQ(c.m_initpatchsize,0.5);
    EXPECT_EQ(c.m_width,3);
    EXPECT_EQ(c.m_height,3);
    EXPECT_EQ(c.m_ppos.size(),9 * 6);
}

TEST(PBD , makeTriangle)
{
    PBD::Tri triangle;
    triangle.a=glm::vec3(1,1,0);
    triangle.b=glm::vec3(1.5, 1, 0);
    triangle.c=glm::vec3(1, 1.5, 0);

    EXPECT_EQ(PBD::makeTriangle(glm::vec3(1,1,0), 0.5).a, triangle.a);
    EXPECT_EQ(PBD::makeTriangle(glm::vec3(1,1,0), 0.5).b, triangle.b);
    EXPECT_EQ(PBD::makeTriangle(glm::vec3(1,1,0), 0.5).c, triangle.c);
}

//TEST(ClothSim, triMirror)
//{
//    PBD::ClothSim c;
//    PBD::Tri triangle;
//    triangle.a=glm::vec3(1,1,0);
//    triangle.b=glm::vec3(1.5, 1, 0);
//    triangle.c=glm::vec3(1, 1.5, 0);

//    auto quad=c.PBD::ClothSim::triMirror(triangle);
//    EXPECT_EQ(quad.a,-triangle.a);

//}