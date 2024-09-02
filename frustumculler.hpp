#ifndef _FRUSTUMCULLER_HPP_
#define _FRUSTUMCULLER_HPP_

#include "externs.hpp"

const int FRUSTUM_SIDE_RIGHT = 0;
const int FRUSTUM_SIDE_LEFT = 1;
const int FRUSTUM_SIDE_BOTTOM = 2;
const int FRUSTUM_SIDE_TOP = 3;
const int FRUSTUM_SIDE_BACK = 4;
const int FRUSTUM_SIDE_FRONT = 5;

extern class FrustumCuller *cull;

class BoundingSphere
{
public:
    BoundingSphere() { this->pos = Vector3(0, 0, 0); this->radius = 0.0f; }
    BoundingSphere(Vector3 &pos, float radius) { this->set(pos, radius); }
    ~BoundingSphere() {}

    void set(Vector3 &pos, float radius) { this->pos = pos; this->radius = radius; }

    Vector3 pos;
    float radius;
};

class BoundingBox
{
public:
    //TODO


};


class FrustumPlane
{
public:
    FrustumPlane() { this->a = 0; this->b = 0; this->c = 0; this->d = 0;};
    ~FrustumPlane() {}; 

    void normalize();

    float a, b, c;
    float d;
};

class FrustumCuller
{
public:
    FrustumCuller();
    ~FrustumCuller();

    void setup();
    
    bool testPoint(Vector3 &point);
    bool testSphere(Vector3 &coord, float radius);
    bool testSphere(BoundingSphere &sphere);
    bool testBox(BoundingBox &box);

private:

    FrustumPlane **frustum;



};








#endif