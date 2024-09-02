#ifndef _MESHFACTORY_HPP_
#define _MESHFACTORY_HPP_

#include "externs.hpp"
#include "mesh.hpp"

class TMeshFactory
{
public:
    //lataa t3d-objektin
    static class TMesh *importT3D(char *name);

    //primitiivit
    static class TMesh *createSphere(float radius, int xres, int yres, float texturescale=1.0f);
    static class TMesh *createTorus(float radius1, float radius2, int xres, int yres, float texturescale=1.0f);
    static class TMesh *createCube(float size, int xres, int yres);

};


#endif