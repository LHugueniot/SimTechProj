#include <clothsimlib_global.h>

//#include <clothsimlib.h>
//#include <clothobj.h>
//#include <distconstraint.h>
#include <ClothPBD.h>

#include <clothsimlib_global.h>
#include <gtest/gtest.h>


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(PBD, aproximateVec3)
{
    EXPECT_TRUE(PBD::aproximateVec3(glm::vec3(0,0,0), glm::vec3(0.04,-0.02,0), 0.05));
}

TEST(PBDobj, initialize)
{
    PBD::PBDobj cloth;
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
    PBD::PBDobj cloth;
    cloth.initialize(glm::vec3(0,0,0), 4, 4, 0.1, 0.99);
    EXPECT_EQ(cloth.m_PointsPtr.size(), 16 );
    EXPECT_EQ(cloth.m_ConPtrs.size(), 33);
}
