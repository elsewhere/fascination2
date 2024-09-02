#include "frustumculler.hpp"

void FrustumPlane::normalize()
{
    float mag = sqrtf(this->a * this->a + this->b * this->b + this->c * this->c);

    this->a *= 1.0f / mag;
    this->b *= 1.0f / mag;
    this->c *= 1.0f / mag;
    this->d *= 1.0f / mag;


}

FrustumCuller::FrustumCuller()
{
    int i = 0;
    this->frustum = new FrustumPlane*[6];

    for (i = 0; i < 6; i++)
    {
        this->frustum[i] = new FrustumPlane();

    }
}

FrustumCuller::~FrustumCuller()
{
    int i = 0;

    for (i = 0; i < 6; i++)
    {
        delete this->frustum[i];
    }
    delete [] this->frustum;

}

void FrustumCuller::setup()
{
    //TODO: 4x4 matriisit? 
    float   projectionMatrix[16];
    float   modelViewMatrix[16];
    float   clippingPlanes[16];

    glGetFloatv( GL_PROJECTION_MATRIX, projectionMatrix );
    glGetFloatv( GL_MODELVIEW_MATRIX, modelViewMatrix );

    //clipplanet = modelview * projection

    clippingPlanes[0] = modelViewMatrix[0] * projectionMatrix[0] + modelViewMatrix[1] * projectionMatrix[4] + modelViewMatrix[2] * projectionMatrix[8] + modelViewMatrix[3] * projectionMatrix[12];
    clippingPlanes[1] = modelViewMatrix[0] * projectionMatrix[1] + modelViewMatrix[1] * projectionMatrix[5] + modelViewMatrix[2] * projectionMatrix[9] + modelViewMatrix[3] * projectionMatrix[13];
    clippingPlanes[2] = modelViewMatrix[0] * projectionMatrix[2] + modelViewMatrix[1] * projectionMatrix[6] + modelViewMatrix[2] * projectionMatrix[10] + modelViewMatrix[3] * projectionMatrix[14];
    clippingPlanes[3] = modelViewMatrix[0] * projectionMatrix[3] + modelViewMatrix[1] * projectionMatrix[7] + modelViewMatrix[2] * projectionMatrix[11] + modelViewMatrix[3] * projectionMatrix[15];

    clippingPlanes[4] = modelViewMatrix[4] * projectionMatrix[0] + modelViewMatrix[5] * projectionMatrix[4] + modelViewMatrix[6] * projectionMatrix[8] + modelViewMatrix[7] * projectionMatrix[12];
    clippingPlanes[5] = modelViewMatrix[4] * projectionMatrix[1] + modelViewMatrix[5] * projectionMatrix[5] + modelViewMatrix[6] * projectionMatrix[9] + modelViewMatrix[7] * projectionMatrix[13];
    clippingPlanes[6] = modelViewMatrix[4] * projectionMatrix[2] + modelViewMatrix[5] * projectionMatrix[6] + modelViewMatrix[6] * projectionMatrix[10] + modelViewMatrix[7] * projectionMatrix[14];
    clippingPlanes[7] = modelViewMatrix[4] * projectionMatrix[3] + modelViewMatrix[5] * projectionMatrix[7] + modelViewMatrix[6] * projectionMatrix[11] + modelViewMatrix[7] * projectionMatrix[15];

    clippingPlanes[8] = modelViewMatrix[8] * projectionMatrix[0] + modelViewMatrix[9] * projectionMatrix[4] + modelViewMatrix[10] * projectionMatrix[8] + modelViewMatrix[11] * projectionMatrix[12];
    clippingPlanes[9] = modelViewMatrix[8] * projectionMatrix[1] + modelViewMatrix[9] * projectionMatrix[5] + modelViewMatrix[10] * projectionMatrix[9] + modelViewMatrix[11] * projectionMatrix[13];
    clippingPlanes[10] = modelViewMatrix[8] * projectionMatrix[2] + modelViewMatrix[9] * projectionMatrix[6] + modelViewMatrix[10] * projectionMatrix[10] + modelViewMatrix[11] * projectionMatrix[14];
    clippingPlanes[11] = modelViewMatrix[8] * projectionMatrix[3] + modelViewMatrix[9] * projectionMatrix[7] + modelViewMatrix[10] * projectionMatrix[11] + modelViewMatrix[11] * projectionMatrix[15];

    clippingPlanes[12] = modelViewMatrix[12] * projectionMatrix[0] + modelViewMatrix[13] * projectionMatrix[4] + modelViewMatrix[14] * projectionMatrix[8] + modelViewMatrix[15] * projectionMatrix[12];
    clippingPlanes[13] = modelViewMatrix[12] * projectionMatrix[1] + modelViewMatrix[13] * projectionMatrix[5] + modelViewMatrix[14] * projectionMatrix[9] + modelViewMatrix[15] * projectionMatrix[13];
    clippingPlanes[14] = modelViewMatrix[12] * projectionMatrix[2] + modelViewMatrix[13] * projectionMatrix[6] + modelViewMatrix[14] * projectionMatrix[10] + modelViewMatrix[15] * projectionMatrix[14];
    clippingPlanes[15] = modelViewMatrix[12] * projectionMatrix[3] + modelViewMatrix[13] * projectionMatrix[7] + modelViewMatrix[14] * projectionMatrix[11] + modelViewMatrix[15] * projectionMatrix[15];

    this->frustum[FRUSTUM_SIDE_RIGHT]->a = clippingPlanes[3] - clippingPlanes[0];
    this->frustum[FRUSTUM_SIDE_RIGHT]->b = clippingPlanes[7] - clippingPlanes[4];
    this->frustum[FRUSTUM_SIDE_RIGHT]->c = clippingPlanes[11] - clippingPlanes[8];
    this->frustum[FRUSTUM_SIDE_RIGHT]->d = clippingPlanes[15] - clippingPlanes[12];
    this->frustum[FRUSTUM_SIDE_RIGHT]->normalize();

    this->frustum[FRUSTUM_SIDE_LEFT]->a = clippingPlanes[3] + clippingPlanes[0];
    this->frustum[FRUSTUM_SIDE_LEFT]->b = clippingPlanes[7] + clippingPlanes[4];
    this->frustum[FRUSTUM_SIDE_LEFT]->c = clippingPlanes[11] + clippingPlanes[8];
    this->frustum[FRUSTUM_SIDE_LEFT]->d = clippingPlanes[15] + clippingPlanes[12];
    this->frustum[FRUSTUM_SIDE_LEFT]->normalize();

    this->frustum[FRUSTUM_SIDE_BOTTOM]->a = clippingPlanes[3] + clippingPlanes[1];
    this->frustum[FRUSTUM_SIDE_BOTTOM]->b = clippingPlanes[7] + clippingPlanes[5];
    this->frustum[FRUSTUM_SIDE_BOTTOM]->c = clippingPlanes[11] + clippingPlanes[9];
    this->frustum[FRUSTUM_SIDE_BOTTOM]->d = clippingPlanes[15] + clippingPlanes[13];
    this->frustum[FRUSTUM_SIDE_BOTTOM]->normalize();

    this->frustum[FRUSTUM_SIDE_TOP]->a = clippingPlanes[3] - clippingPlanes[1];
    this->frustum[FRUSTUM_SIDE_TOP]->b = clippingPlanes[7] - clippingPlanes[5];
    this->frustum[FRUSTUM_SIDE_TOP]->c = clippingPlanes[11] - clippingPlanes[9];
    this->frustum[FRUSTUM_SIDE_TOP]->d= clippingPlanes[15] - clippingPlanes[13];
    this->frustum[FRUSTUM_SIDE_TOP]->normalize();

    this->frustum[FRUSTUM_SIDE_BACK]->a = clippingPlanes[3] - clippingPlanes[2];
    this->frustum[FRUSTUM_SIDE_BACK]->b = clippingPlanes[7] - clippingPlanes[6];
    this->frustum[FRUSTUM_SIDE_BACK]->c = clippingPlanes[11] - clippingPlanes[10];
    this->frustum[FRUSTUM_SIDE_BACK]->d = clippingPlanes[15] - clippingPlanes[14];
    this->frustum[FRUSTUM_SIDE_BACK]->normalize();

    this->frustum[FRUSTUM_SIDE_FRONT]->a = clippingPlanes[3] + clippingPlanes[2];
    this->frustum[FRUSTUM_SIDE_FRONT]->b = clippingPlanes[7] + clippingPlanes[6];
    this->frustum[FRUSTUM_SIDE_FRONT]->c = clippingPlanes[11] + clippingPlanes[10];
    this->frustum[FRUSTUM_SIDE_FRONT]->d = clippingPlanes[15] + clippingPlanes[14];
    this->frustum[FRUSTUM_SIDE_FRONT]->normalize();

}

bool FrustumCuller::testPoint(Vector3 &point)
{
    int i = 0; 

    for (i = 0; i < 6; i++ )
    {
        if (this->frustum[i]->a * point.x + 
            this->frustum[i]->b * point.y + 
            this->frustum[i]->c * point.z + 
            this->frustum[i]->d <= 0)
        {
            return false;
        }
    }

    return true;
}

bool FrustumCuller::testSphere(Vector3 &coord, float radius)
{

    int i = 0; 

    for (i = 0; i < 6; i++ )
    {
        if (this->frustum[i]->a * coord.x + 
            this->frustum[i]->b * coord.y + 
            this->frustum[i]->c * coord.z + 
            this->frustum[i]->d <= -radius)
        {
            return false;
        }
    }

    return true;
}

bool FrustumCuller::testSphere(BoundingSphere &sphere)
{

    int i = 0; 

    for (i = 0; i < 6; i++ )
    {
        if (this->frustum[i]->a * sphere.pos.x + 
            this->frustum[i]->b * sphere.pos.y + 
            this->frustum[i]->c * sphere.pos.z + 
            this->frustum[i]->d <= -sphere.radius)
        {
            return false;
        }
    }

    return true;
}

/*
bool CFrustum::CubeInFrustum( float x, float y, float z, float size )
{
    // This test is a bit more work, but not too much more complicated.
    // Basically, what is going on is, that we are given the center of the cube,
    // and half the length.  Think of it like a radius.  Then we checking each point
    // in the cube and seeing if it is inside the frustum.  If a point is found in front
    // of a side, then we skip to the next side.  If we get to a plane that does NOT have
    // a point in front of it, then it will return false.

    // *Note* - This will sometimes say that a cube is inside the frustum when it isn't.
    // This happens when all the corners of the bounding box are not behind any one plane.
    // This is rare and shouldn't effect the overall rendering speed.

    for(int i = 0; i < 6; i++ )
    {
        if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z - size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y - size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x - size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
           continue;
        if(m_Frustum[i][A] * (x + size) + m_Frustum[i][B] * (y + size) + m_Frustum[i][C] * (z + size) + m_Frustum[i][D] > 0)
           continue;

        // If we get here, it isn't in the frustum
        return false;
    }

    return true;
}
*/

