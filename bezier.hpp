#ifndef _Bezier_HPP_
#define _Bezier_HPP_

#include "externs.hpp"

class Bezier
{
public:
    Bezier();
    ~Bezier();
    void destroy();

    //point = piste, tangent = suunta (sis‰lt‰‰ jo pisteen paikan)
    void startCreation();
    void addPoint(Vector3 &point, Vector3 &tangent);
    void endCreation();
    
    Vector3 getValue(float t);

    Vector3 *points;
    Vector3 *tangents;

private:
    std::vector<Vector3> insertedPoints;
    std::vector<Vector3> insertedTangents;
    int pcount;


};



#endif
