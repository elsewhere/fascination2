#ifndef _PRIMITIVES_HPP_
#define _PRIMITIVES_HPP_

#include "externs.hpp"
#include "mathematics.hpp"

extern Vector *primitivegrid;// = new Vector[slices*slices];
extern bool gridinit;


class Primitives
{
public:

    static void init();

	static void textureTausta(bool xflip, bool yflip);
	static void textureTaustaScale(bool xflip, bool yflip, float scale);
	static void textureTaustaMove(bool xflip, bool yflip, float xoff, float yoff);
	static void textureTaustaScaleMove(bool xflip, bool yflip, float scale, float xoff, float yoff);
    static void flatTausta(float r, float g, float b, float alpha);
	static void renderTexturedPlaneWithFadeOut(Vector &p1, Vector &p2, Vector &p3, Vector &p4, int slices, float texturetimes, Vector color, Vector origin, float mindist, float maxdist, float alpha=1.0f);

	static void wireCube(float size);
	static void flatCube(float size);
	static void texturedCube(float size, float tmul);
    static void wireGridBox(float size, int count);
	static void fadeText(float x, float y, float scale, float alpha, float pos, float starttime, float endtime, float ramp,
				 		  char *fontti, char *teksti);

    static void drawDebugGrid(float alpha);
    static void drawBillboard(Vector3 &point, float size);

};


#endif