 #include "mathematics.hpp"

Vector3 Mathematics::sphereToCartesian(float radius, float phi, float theta)
{
	float sp = (float)sin(phi);
	float cp = (float)cos(phi);
	float st = (float)sin(theta);
	float ct = (float)cos(theta);
	Vector3 value = Vector3(radius*sp*ct, radius*sp*st, radius*cp);
	return value;
}
Vector3 Mathematics::cartesianToSphere(float x, float y, float z)
{
	float rho = (float)sqrt(x*x+y*y+z*z);
	if (rho == 0.0f) 
		return Vector3(0,0,0);
/*
    float phi = (float)acos(z/rho);
	float theta = (float)acos(x/(rho*sin(phi)));
*/
    float phi = atan2f(y, x);
    float theta = acosf(z / rho);
	Vector3 value = Vector3(rho, theta, phi);
	return value;
}
float Mathematics::integrateSimpson(float startpoint, float endpoint, int steps, float(*function)(float))
{
	float val = 0.0f;
	float h = (endpoint-startpoint)/steps;
	val += function(startpoint);
	val += function(endpoint);

	for (int i=0;i<steps-1;i++)
	{
		if (!(i&1)) //parillinen
			val += 4*function(h+i*h);
		else
			val += 2*function(h+i*h);
	}
	val *= h/3.0f;
	return val;
}
void Mathematics::antiRotate(Vector3 *x, Vector3 *y, Vector3 *z)
{
	float matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);	
	
	*x = (Vector3(matrix[0], matrix[4], matrix[8]));
	*y = (Vector3(matrix[1], matrix[5], matrix[9]));
	*z = Vector3(matrix[2], matrix[6], matrix[10]);
}

float Mathematics::calcSaturate(float value, float limit1, float limit2, float multiply)
{
	float pos, arvo;
	if (value <= limit1)
		return 0;
	if (value >= limit2)
		return 0;
	else
		pos = (float)(value-limit1)/(limit2-limit1);

	arvo = (float)sin(pos*3.141592f)*multiply;
	if (arvo < 0) 
		arvo = 0;
	if (arvo > 1)
		arvo = 1;

	return arvo;
}

float Mathematics::calcPosFloat(float value, float limit1, float limit2)
{
	if (value <= limit1)
		return 0;
	if (value >= limit2)
		return 1;
	else
		return (float)(value-limit1)/(limit2-limit1);
}

float Mathematics::calcPosSmooth(float value, float limit1, float limit2)
{
	// This might be broken!
	// Check.

	float t = max(1,min(0,(float)(value-limit1)/(limit2-limit1)));
	return t * t * (3 - 2 * t);
}

float Mathematics::calcPosCos(float value, float limit1, float limit2)
{
	if (value <= limit1)
		return 0;
	if (value >= limit2)
		return 1;
	
	const float val = 1.0f-cosf(1.5707963f*Mathematics::calcPosFloat(value, limit1, limit2));
	
	const float accuracy_factor = 0.001f;

	// palautetaan 0 jos ollaan kipupisteen alapuolella 
	//(cosf ei anna nollaa, koska PII/2 ei ole jaollinen)
	if(val < accuracy_factor) return 0.0f;
	else return val;
}

bool Mathematics::prob(float percentage)
{
    if (randFloat() < percentage)
    {
        return true;
    }
    return false;
}


float Mathematics::randFloat()
{
	return (float)((rand()%20000)/20000.0f);
}

float Mathematics::randBetween(float min, float max)
{
    return min + randFloat() * (max - min);
}

float Mathematics::randFloat(float i) {
	if(i<=0) return 0.0f;
	return randFloat()*i;
}

int Mathematics::randInt(int i) {
	if(i<=0) return 0;
	return rand()%i;
}

Vector3 Mathematics::randVector()
{
	return Vector3(randFloat()-0.5f, randFloat()-0.5f, randFloat()-0.5f);
}

Vector3 Mathematics::randVector(float dx, float dy, float dz)
{
	return Vector3(dx*(randFloat()-0.5f), dy*(randFloat()-0.5f), dz*(randFloat()-0.5f));

}

Vector3 Mathematics::randVector2()
{
	return Vector3(randFloat(), randFloat(), randFloat());

}
Vector3 Mathematics::randVectSphere()
{
	float rho = randFloat()*3.141592f;
	float theta = randFloat()*3.141592f*2;

	return sphereToCartesian(1, theta, rho);
}
Vector3 Mathematics::randVectPlane()
{
    float a = randFloat()*2*3.141592f;
    return Vector3(cosf(a), 0, sinf(a));
}

float Mathematics::getClosest(float value, float first, float second) 
{
	  if(fabsf(value - first) < fabsf(value - second))
		return first;
	  return second;
}
