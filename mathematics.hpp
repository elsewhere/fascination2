#ifndef _MATHEMATICS_HPP_
#define _MATHEMATICS_HPP_

#include "externs.hpp"

class Mathematics
{
public:
	Mathematics() {}; 
	~Mathematics() {};

	//palauttaa Vectorn, jossa on halutut pallokoordinaatit karteesisessa koordinaatistossa
	//phi = [0, pii], theta = [0, 2*pii], radius = [0, inf]
	static Vector3 sphereToCartesian(float radius, float phi, float theta);
	//palauttaa Vectorn, jossa on halutut karteesiset koordinaatit pallokoordinaatistossa
	//v = [radius, phi, theta]. Ei huomioi, missä segmentissä ollaan joten muista tarkistaa
	//kulmat!
	static Vector3 cartesianToSphere(float x, float y, float z);

	//numeerinen integrointi Simpsonin menetelmällä
	static float integrateSimpson(float startpoint, float endpoint, int steps, float(*function)(float));
	static void antiRotate(Vector3 *x, Vector3 *y, Vector3 *z);
	static float calcSaturate(float value, float limit1, float limit2, float multiply);
	static float calcPosFloat(float value, float limit1, float limit2);
	static float calcPosCos(float value, float limit1, float limit2);
	static float calcPosSmooth(float value, float limi1, float limit2);


    //kusee teoreettisesti 1.0 mutta haittaako? 
    static bool prob(float percentage);


	//static Vector slerp(Vector 
	//(sin((1-t)a)v1+sin(ta)v2)/sin(a)

	// palauttaa [0 - 1]
	static float randFloat();
    // palauttaa [min, max]
    static float randBetween(float min, float max);
	// palauttaa rand()%i
	static int randInt(int i);
	// palauttaa [0 - i]
	static float randFloat(float i);

	// Vector( [-0.5f,0.5f] , ..)
	static Vector3 randVector();

	// Vector( [-0.5f, 0.5f]*kerroin
	static Vector3 randVector(float dx, float dy, float dz);

	// Vector( [0,1] , ..);
	static Vector3 randVector2();
	
    static Vector3 randVectSphere();
    static Vector3 randVectPlane();

	static float getClosest(float value, float first, float second);

};

#endif