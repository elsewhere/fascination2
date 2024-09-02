#include "primitives.hpp"

Vector *primitivegrid;// = new Vector[slices*slices];
bool gridinit;

void Primitives::init()
{
    primitivegrid = new Vector[25*25];
}
void Primitives::drawDebugGrid(float alpha)
{
    int i;
	glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDisable(GL_DEPTH_TEST);
    glDisable(GL_TEXTURE_2D);
    glLineWidth(1.0f);

    glColor4f(1,1,1,alpha*0.1f);
    glBegin(GL_LINES);
    const int slices = 50;
    const float planesize = 5.0f;
    for (i = 0; i < slices; i++)
    {
        const float t = i / (float)slices;
        float x = -planesize*(1-t) + planesize*t;

        Vector v1 = Vector(x, 0, -planesize);
        Vector v2 = Vector(x, 0, planesize);
        glVertex3fv((float *)&v1);
        glVertex3fv((float *)&v2);
    }
    for (i = 0; i < slices; i++)
    {
        const float t = i / (float)slices;
        float x = -planesize*(1-t) + planesize*t;

        Vector v1 = Vector(-planesize, 0, x);
        Vector v2 = Vector(planesize, 0, x);
        glVertex3fv((float *)&v1);
        glVertex3fv((float *)&v2);
    }
    glEnd();

}
void Primitives::drawBillboard(Vector3 &point, float size)
{
	Vector3 x, y, z;
	Mathematics::antiRotate(&x, &y, &z);

    glBegin(GL_QUADS);

	Vector3 v1 = point - x*size - y*size;
	Vector3 v2 = point + x*size - y*size;
	Vector3 v3 = point + x*size + y*size;
	Vector3 v4 = point - x*size + y*size;

	glTexCoord2f(0, 0);
	glVertex3fv((float *)&v1);
	glTexCoord2f(1, 0);
	glVertex3fv((float *)&v2);
	glTexCoord2f(1, 1);
	glVertex3fv((float *)&v3);
	glTexCoord2f(0, 1);
	glVertex3fv((float *)&v4);

    glEnd();
}


void Primitives::flatTausta(float r, float g, float b, float alpha)
{
	glDisable(GL_DEPTH_TEST);
	//glDisable(GL_DEPTH_MASK);
	glDisable(GL_TEXTURE_2D);
    glDepthMask(0);

	dmsPerspective2D(1,1);
	glLoadIdentity();

	glBegin(GL_QUADS);
    glColor4f(r,g,b, alpha);

	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);

	glEnd();

    glDepthMask(1);
	dmsPerspective3D();
	glLoadIdentity();


}
void Primitives::textureTaustaMove(bool xflip, bool yflip, float xoff, float yoff)
{
	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_MASK);
	glEnable(GL_TEXTURE_2D);
    glDepthMask(0);

	dmsPerspective2D(1,1);
	glLoadIdentity();

	float x0 = 0;
	float x1 = 1;
	float y0 = 1;
	float y1 = 0;

	if (xflip)
	{
		x1 = 0;
		x0 = 1;
	}
	if (yflip)
	{
		y0 = 0;
		y1 = 1;
	}

	glBegin(GL_QUADS);

	glTexCoord2f(x0+xoff, y0+yoff);
	glVertex2f(0, 0);
	glTexCoord2f(x1+xoff, y0+yoff);
	glVertex2f(1, 0);
	glTexCoord2f(x1+xoff, y1+yoff);
	glVertex2f(1, 1);
	glTexCoord2f(x0+xoff, y1+yoff);
	glVertex2f(0, 1);

	glEnd();

    glDepthMask(1);
	dmsPerspective3D();
	glLoadIdentity();
}
void Primitives::textureTaustaScale(bool xflip, bool yflip, float scale)
{
	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_MASK);
	glEnable(GL_TEXTURE_2D);

	dmsPerspective2D(1,1);
	glLoadIdentity();

	float x0 = 0+scale;
	float x1 = 1-scale;
    float y0 = 1-scale;//*(480/640.0f);
	float y1 = 0+scale;//*(480/640.0f);

	if (xflip)
	{
        float temp = x1;
        x1 = x0;
        x0 = temp;
	}
	if (yflip)
	{
        float temp = y1;
        y1 = y0;
        y0 = temp;
	}

	glBegin(GL_QUADS);

	glTexCoord2f(x0, y0);
	glVertex2f(0, 0);
	glTexCoord2f(x1, y0);
	glVertex2f(1, 0);
	glTexCoord2f(x1, y1);
	glVertex2f(1, 1);
	glTexCoord2f(x0, y1);
	glVertex2f(0, 1);

	glEnd();

	dmsPerspective3D();
	glLoadIdentity();
}

void Primitives::textureTaustaScaleMove(bool xflip, bool yflip, float scale, float xoff, float yoff)
{
	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_MASK);
	glEnable(GL_TEXTURE_2D);

	dmsPerspective2D(1,1);
	glLoadIdentity();

	float x0 = 0+scale;
	float x1 = 1-scale;
    float y0 = 1-scale;//*(480/640.0f);
	float y1 = 0+scale;//*(480/640.0f);

	if (xflip)
	{
        float temp = x1;
        x1 = x0;
        x0 = temp;
	}
	if (yflip)
	{
        float temp = y1;
        y1 = y0;
        y0 = temp;
	}

	glBegin(GL_QUADS);

	glTexCoord2f(x0+xoff, y0+yoff);
	glVertex2f(0, 0);
	glTexCoord2f(x1+xoff, y0+yoff);
	glVertex2f(1, 0);
	glTexCoord2f(x1+xoff, y1+yoff);
	glVertex2f(1, 1);
	glTexCoord2f(x0+xoff, y1+yoff);
	glVertex2f(0, 1);

	glEnd();

	dmsPerspective3D();
	glLoadIdentity();
}

void Primitives::textureTausta(bool xflip, bool yflip)
{
	glDisable(GL_DEPTH_TEST);
//	glDisable(GL_DEPTH_MASK);
	glEnable(GL_TEXTURE_2D);

	dmsPerspective2D(1,1);
	glLoadIdentity();

	float x0 = 0;
	float x1 = 1;
	float y0 = 1;
	float y1 = 0;

	if (xflip)
	{
		x1 = 0;
		x0 = 1;
	}
	if (yflip)
	{
		y0 = 0;
		y1 = 1;
	}

	glBegin(GL_QUADS);

	glTexCoord2f(x0, y0);
	glVertex2f(0, 0);
	glTexCoord2f(x1, y0);
	glVertex2f(1, 0);
	glTexCoord2f(x1, y1);
	glVertex2f(1, 1);
	glTexCoord2f(x0, y1);
	glVertex2f(0, 1);

	glEnd();

	dmsPerspective3D();
	glLoadIdentity();




}

void Primitives::fadeText(float x, float y, float scale, float alpha, float pos, float starttime, float endtime, float ramp,
				 		  char *fontti, char *teksti)
{
	if (pos < starttime || pos > endtime)
		return;

	float fadekohta = (pos-starttime) / (endtime-starttime);
	fadekohta = (float)sin(fadekohta*3.141592f); //ylös ja alas
	fadekohta = (float)pow(fadekohta, ramp);

	dmsWrite2D(x, y, alpha*fadekohta, scale, fontti, teksti);

//void dmsWrite2D(float x, float y, float a, float scale, char *fontName, char *msg);

}


void Primitives::flatCube(float size)
{
	Vector upleftback = Vector( -size, -size, -size);
	Vector upleftfront = Vector(-size, -size, +size);
	Vector uprightback = Vector( size, -size, -size);
	Vector uprightfront = Vector(size, -size, +size);

	Vector downleftback = Vector( -size, size, -size);
	Vector downleftfront = Vector(-size, size, +size);
	Vector downrightback = Vector( size, size, -size);
	Vector downrightfront = Vector(size, size, +size);

	glBegin(GL_QUADS);

	//yläsivu
    glNormal3f(0, 1, 0);
	glVertex3fv((float *)&upleftback);
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&upleftfront);

	//alasivu
    glNormal3f(0, -1, 0);
	glVertex3fv((float *)&downleftback);
	glVertex3fv((float *)&downrightback);
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downleftfront);

	//etusivu
    glNormal3f(0, 0, -1);
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downleftfront);

	//takasivu
    glNormal3f(0, 0, 1);
	glVertex3fv((float *)&upleftback);
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&downrightback);
	glVertex3fv((float *)&downleftback);

	//vasen sivu
    glNormal3f(1, 0, 0);
	glVertex3fv((float *)&upleftback);
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&downleftfront);
	glVertex3fv((float *)&downleftback);

	//oikea sivu
    glNormal3f(-1, 0, 0);
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downrightback);

	glEnd();
}






void Primitives::wireCube(float size)
{
	if (size <= 0) return;
	Vector upleftback = Vector( -size, -size, -size);
	Vector upleftfront = Vector(-size, -size, +size);
	Vector uprightback = Vector( size, -size, -size);
	Vector uprightfront = Vector(size, -size, +size);

	Vector downleftback = Vector( -size, size, -size);
	Vector downleftfront = Vector(-size, size, +size);
	Vector downrightback = Vector( size, size, -size);
	Vector downrightfront = Vector(size, size, +size);
	
	glBegin(GL_LINES);

	//yläsivu vasen
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&upleftback);
	//yläsivu oikea
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&uprightback);
	//yläsivu etu
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&upleftfront);
	//yläsivu taka
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&upleftback);

	//alasivu vasen
	glVertex3fv((float *)&downleftfront);
	glVertex3fv((float *)&downleftback);
	//alasivu oikea
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downrightback);
	//alasivu etu
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downleftfront);
	//alasivu taka
	glVertex3fv((float *)&downrightback);
	glVertex3fv((float *)&downleftback);

	//oikea sivu ylä
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&uprightback);
	//oikea sivu ala
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downrightback);
	//oikea sivu etu
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&downrightfront);
	//oikea sivu taka
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&downrightback);

	//vasen sivu ylä
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&upleftback);
	//vasen sivu ala
	glVertex3fv((float *)&downleftfront);
	glVertex3fv((float *)&downleftback);
	//vasen sivu etu
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&downleftfront);
	//vasen sivu taka
	glVertex3fv((float *)&upleftback);
	glVertex3fv((float *)&downleftback);

	//etusivu ylä
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&upleftfront);
	//etusivu ala
	glVertex3fv((float *)&downrightfront);
	glVertex3fv((float *)&downleftfront);
	//etusivu oikea
	glVertex3fv((float *)&uprightfront);
	glVertex3fv((float *)&downrightfront);
	//etusivu vasen
	glVertex3fv((float *)&upleftfront);
	glVertex3fv((float *)&downleftfront);

	//takasivu ylä
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&upleftback);
	//takasivu ala
	glVertex3fv((float *)&downrightback);
	glVertex3fv((float *)&downleftback);
	//takasivu oikea
	glVertex3fv((float *)&uprightback);
	glVertex3fv((float *)&downrightback);
	//takasivu vasen
	glVertex3fv((float *)&upleftback);
	glVertex3fv((float *)&downleftback);

	glEnd();
}

void Primitives::texturedCube(float size, float tmul)
{
	Vector upleftback = Vector( -size, -size, -size);
	Vector upleftfront = Vector(-size, -size, +size);
	Vector uprightback = Vector( size, -size, -size);
	Vector uprightfront = Vector(size, -size, +size);

	Vector downleftback = Vector( -size, size, -size);
	Vector downleftfront = Vector(-size, size, +size);
	Vector downrightback = Vector( size, size, -size);
	Vector downrightfront = Vector(size, size, +size);

	glBegin(GL_QUADS);

	//yläsivu
//    glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&upleftback);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&uprightback);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&uprightfront);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&upleftfront);

	//alasivu
//    glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&downleftback);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&downrightback);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&downrightfront);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&downleftfront);

	//etusivu
//    glNormal3f(0, 0, -1);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&upleftfront);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&uprightfront);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&downrightfront);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&downleftfront);

	//takasivu
//    glNormal3f(0, 0, 1);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&upleftback);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&uprightback);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&downrightback);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&downleftback);

	//vasen sivu
//    glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&upleftback);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&upleftfront);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&downleftfront);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&downleftback);

	//oikea sivu
//    glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3fv((float *)&uprightback);
	glTexCoord2f(tmul, 0);
	glVertex3fv((float *)&uprightfront);
	glTexCoord2f(tmul, tmul);
	glVertex3fv((float *)&downrightfront);
	glTexCoord2f(0, tmul);
	glVertex3fv((float *)&downrightback);

	glEnd();

}

void Primitives::renderTexturedPlaneWithFadeOut(Vector &p1, Vector &p2, Vector &p3, Vector &p4, int slices, 
                                                float texturetimes, Vector color, Vector origin, float mindist, float 
                                                maxdist, float alpha) 
{
	
    slices = 25;
	Vector col = Vector();
	
	if(texturetimes==0.0f) texturetimes=1.0f;
	//p1----p2
	//|     |
	//|     |
	//|     |
	//p4----p3

	int x, y;

	Vector dy1 = (p4-p1)*(1.0f/(slices-1));
	Vector dy2 = (p3-p2)*(1.0f/(slices-1));

	Vector u1 = p1;
	Vector u2 = p2;

	for (y=0;y<slices;y++)
	{
		Vector dx = (u2-u1)*(1.0f/(slices-1));
		Vector v = u1;
		for (x=0;x<slices;x++)
		{
			primitivegrid[x+y*slices] = v;
			v += dx;
		}
		u1 += dy1;
		u2 += dy2;
	}

	//primitivegridi tehty
	glBegin(GL_QUADS);
	for (y=0;y<slices-2;y++)
	{
		for (x=0;x<slices-2;x++)
		{
			Vector v1 = primitivegrid[x+   y*slices];
			Vector v2 = primitivegrid[x+1+ y*slices];
			Vector v3 = primitivegrid[x+1+(y+1)*slices];
			Vector v4 = primitivegrid[x+  (y+1)*slices];
			
			const float div = slices/texturetimes;

			const float mod1 = (1-Mathematics::calcPosFloat((origin-v1).length(), mindist, maxdist));
			col = color*mod1;
			glColor4f(col.x, col.y, col.z, alpha*mod1);
			glTexCoord2f(x/div,y/div);
			glVertex3fv((float *)&v1);

			const float mod2 = (1-Mathematics::calcPosFloat((origin-v2).length(), mindist, maxdist));
			col = color*mod2;
			glColor4f(col.x, col.y, col.z, alpha*mod2);
			glTexCoord2f((x+1)/div,y/div);
			glVertex3fv((float *)&v2);

			const float mod3 = (1-Mathematics::calcPosFloat((origin-v3).length(), mindist, maxdist));
			col = color*mod3;
			glColor4f(col.x, col.y, col.z, alpha*mod3);
			glTexCoord2f((x+1)/div,(y+1)/div);
			glVertex3fv((float *)&v3);

			const float mod4 = (1-Mathematics::calcPosFloat((origin-v4).length(), mindist, maxdist));
			col = color*mod4;
			glColor4f(col.x, col.y, col.z, alpha*mod4);
			glTexCoord2f(x/div,(y+1)/div);
			glVertex3fv((float *)&v4);

		}
	}
	glEnd();

}
