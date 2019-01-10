#include <clothsimlib_global.h>

#include <clothsimlib.h>
#include <clothobj.h>
#include <distconstraint.h>
#include <test.h>

#include <clothsimlib_global.h>
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

TEST(ClothObj, makeMesh)
{
    PBD::ClothObj c;
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

//TEST(distConstraint, ctr)
//{
//    PBD::ClothObj c;
//    c.makeMesh(glm::vec3(0,0,0),3,3,0.5);
//    PBD::distConstraint dc(&c, 0 ,1);
//    EXPECT_EQ(dc.rLength, 0.5);

//}

TEST(bool, aproximateVec3)
{
    EXPECT_TRUE(aproximateVec3(glm::vec3(0,0,0), glm::vec3(0.04,-0.02,0), 0.05));
}

TEST(PBDobj, initialize)
{
    PBDobj cloth;
    cloth.initialize(glm::vec3(0,0,0), 3, 3, 0.5, 0.99);
    EXPECT_EQ(cloth.m_PointsPtr.size(), 9 );
    EXPECT_EQ(cloth.m_ConPtrs.size(), 16);
    for(uint i=0;i<cloth.m_ConPtrs.size(); i++)
    {
        auto pA=cloth.m_ConPtrs[i]->m_pA->m_ppos;
        auto pB=cloth.m_ConPtrs[i]->m_pB->m_ppos;
        if( pA==pB)
        {
            std::cout<<"error"<<i;
        }
        //std::cout<<pA.x<<" "<<pA.y<<" "<<pA.z<<"\n";
    }
}

TEST(PBDobj, initialize1)
{
    PBDobj cloth;
    cloth.initialize(glm::vec3(0,0,0), 4, 4, 0.1, 0.99);
    EXPECT_EQ(cloth.m_PointsPtr.size(), 16 );
    EXPECT_EQ(cloth.m_ConPtrs.size(), 33);
}

//TEST()
//{

//}

//TEST()
//{

//}

//TEST()
//{

//}


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
