#include "PBDObj.h"

namespace PBD {

PBDobj::PBDobj()
{

}

PBDobj::~PBDobj()
{
    for(uint p=0; p<m_ConPtrs.size(); p++)
    {
        delete m_ConPtrs[p];
    }
    for(uint i=0 ;i< m_PointsPtr.size(); i++)
    {
        delete m_PointsPtr[i];
    }
}

void PBDobj::addConstraint(DistanceConstraint* m_Constraint)
{
    m_ConPtrs.push_back(m_Constraint);
}

void PBDobj::addObjectToList(CollisionObj * _newColObj)
{
    OtherObjs.push_back(_newColObj);
}

void PBDobj::initialize(glm::vec3 _pos, int _width, int _height, float _patchsize, float _damping)
{
    m_patchsize = _patchsize;
    m_width=_width;
    m_height=_height;
    m_pos=_pos;
    m_damp=_damping;

    //--------------------------------

    for(uint i=0; i<m_width; i++)
    {
        for(uint j=0;j<m_height; j++)
        {
            Point * newp = new Point(m_pos +glm::vec3( i*m_patchsize,0,j*-m_patchsize),
                                     glm::vec3(0,0,0), 1);
            m_PointsPtr.push_back(newp);
        }
    }

    for(uint i=0 ;i< m_PointsPtr.size(); i++)
    {
        for(uint j=0 ;j< m_PointsPtr.size(); j++)
        {
            auto a0 = m_PointsPtr.at(i)->m_ppos;
            auto b0 = m_PointsPtr.at(j)->m_ppos;
            auto a1 = a0+ glm::vec3(m_patchsize, 0, 0);
            auto a2 = a0+ glm::vec3(0, 0, m_patchsize);
            auto a3 = a0+ glm::vec3(m_patchsize, 0, m_patchsize);
            if(LML::aproximateVec3(b0,a1,0.05)==true ||
                    LML::aproximateVec3(b0,a2,0.05)==true ||
                    LML::aproximateVec3(b0,a3,0.05)==true)
            {
                DistanceConstraint* _Con= new DistanceConstraint(m_PointsPtr[i], m_PointsPtr[j]);
                addConstraint(_Con);
            }

        }
    }
    for(uint p=0; p<m_ConPtrs.size(); p++)
    {
        auto pA = m_ConPtrs[p]->m_pA->m_ppos;
        auto pB = m_ConPtrs[p]->m_pB->m_ppos;
        //std::cout<<"PA ("<<pA.x<<" "<<pA.y<<" "<<pA.z<<") ";
        //std::cout<<"PB ("<<pB.x<<" "<<pB.y<<" "<<pB.z<<") \n";
    }
}


void PBDobj::runSolver(float dt)
{
    //Predict Location

    float inv_dt=1/dt;


    //colision prediction
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_pvel+=m_grav*m_damp*p.m_invMass*inv_dt;
        p.tmp_pos=p.m_ppos+p.m_pvel*inv_dt;

        if(OtherObjs.size()>0)
        {
            for(uint j=0; j<OtherObjs.size(); j++)
            {
                CollisionObj& o = *(OtherObjs[j]);
                for(uint k=0; k<o.vertices.size(); k++)
                {
                    if(o.CheckCollision1(k,p.tmp_pos)==true)
                    {
                        //p.tmp_pos=p.m_ppos;
                        //a+=0.05;
                        //p.m_ppos-=p.m_pvel;
                        //p.m_pvel-=p.m_pvel;
                    }
                }
                //                o.CheckCollision(p);
            }
        }
    }

    //update constraints

    for (uint i=0; i<5; i++)
    {
        for (uint i=0; i<m_ConPtrs.size(); i++)
        {
            m_ConPtrs[i]->update();
        }
    }
    std::cout<<"\n";


    //update position
    for (uint i=0; i<m_PointsPtr.size(); i++)
    {
        Point& p = *(m_PointsPtr[i]);
        p.m_pvel = (p.tmp_pos - p.m_ppos)/inv_dt;// * inv_dt;
        p.m_ppos=p.tmp_pos;
        //std::cout<<p.tmp_pos.x<<" "<<p.tmp_pos.y<<" "<<p.tmp_pos.z<<"\n";
    }

}

}
