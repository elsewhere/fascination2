//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "path.hpp"
#include "opengl.hpp"
#include "hermitecurve.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Spline class code
//--------------------------------------------------------------------------------------------

Spline::Spline()
{
	count = 0;
	points = new Lista();
}


Spline::~Spline()
{
	points->destroy();
	delete points;
}

void Spline::addpoint(Vector4 &point)
{
	count++;
	points->add(new Vector4(point.x, point.y, point.z));
}

void Spline::draw()
{
	glPushAttrib(GL_ENABLE_BIT);	/* GL_TEXTURE_2D */
	glPushAttrib(GL_CURRENT_BIT); /* väri */
	glDisable(GL_TEXTURE_2D); /* ei kosketa wrapperiin ollenkaan */

	glColor4f(1,1,1,1);
	glBegin(GL_LINE_STRIP);
	for (float t=0;t<1.0f;t+=0.005f)
	{
		Vector4 v = getValue(t);
		glVertex3f(v.x, v.y, v.z);
	}
	glEnd();
	glPopAttrib();
	glPopAttrib();
}

Vector4 Spline::getValue(float t)
{
	/* missä nodessa ollaan menossa */
	int nodepos = (int)floor((t*(count-1)));

	points->goToNode(nodepos);

	/* pyöristyksen takia ollaan ohitettu nodeposin osoittama node, eli 
	   käyrän Vector4t ovat:

	   alkupiste = lista [nodepos]
	   alkutangentti = lista[nodepos+1] - lista[nodepos]
	   lopputangentti = lista[nodepos+2] - lista[nodepos+1]
	   loppupiste = lista[nodepos+1]
	*/

	Vector4 *startpoint = (Vector4 *)points->getCurrent();
	points->goForward();
	Vector4 *endpoint = (Vector4 *)points->getCurrent();
	Vector4 starttangent = *endpoint - *startpoint;		/* luodaan uusi Vector4, tätä ei ole olemassa oikeasti */
	points->goForward();
	Vector4 endtangent = *(Vector4 *)points->getCurrent() - (*endpoint);	/* kuten myös */

	HermiteCurve c;
	c.set(*startpoint, starttangent, endtangent, *endpoint);

	float pos = (t*(count-1))-nodepos;
	return c.getValue(pos);
}

Vector4 Spline::getDerivative(float t)
{
	/* missä nodessa ollaan menossa */
	int nodepos = (int)floor((t*(count-1)));

	points->goToNode(nodepos);

	/* pyöristyksen takia ollaan ohitettu nodeposin osoittama node, eli 
	   käyrän Vector4t ovat:

	   alkupiste = lista [nodepos]
	   alkutangentti = lista[nodepos+1] - lista[nodepos]
	   lopputangentti = lista[nodepos+2] - lista[nodepos+1]
	   loppupiste = lista[nodepos+1]
	*/

	Vector4 *startpoint = (Vector4 *)points->getCurrent();
	points->goForward();
	Vector4 *endpoint = (Vector4 *)points->getCurrent();
	Vector4 starttangent = *endpoint - *startpoint;		/* luodaan uusi Vector4, tätä ei ole olemassa oikeasti */
	points->goForward();
	Vector4 endtangent = *(Vector4 *)points->getCurrent() - (*endpoint);	/* kuten myös */

	HermiteCurve c;
	c.set(*startpoint, starttangent, endtangent, *endpoint);

	float pos = (t*(count-1))-nodepos;
	return c.getDerivative(pos);
}
