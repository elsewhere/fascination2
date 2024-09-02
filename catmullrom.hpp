#ifndef _CATMULLROM_HPP_
#define _CATMULLROM_HPP_

#include <vector>
#include "externs.hpp"

class CatmullRom
{
public:
    CatmullRom();
    ~CatmullRom();

    //palauttaa kopion
    CatmullRom *clone();

    void startCreation();
    void addPoint(Vector3 &point);
    void endCreation();

    //parametrisoi kaaren pituuden mukaan (laittaa pisteet tasavälein)
    //tuhoaa vanhan splinen, ts. osoittimet taulukkoon hajoavat
    //newSplinePoints on uuden splinin pisteiden määrä (nollalla käyttää alkuperäistä pistemäärää)
    //samples on splinistä otettavien näytteiden määrä 
    void arcLengthParametrize(int newSplinePoints = 0, int samples = 1000);

    Vector3 getValue(float t);
    Vector3 getTangent(float t);

    Vector3 *getPoints() { return this->points; };
    int getPointCount() { return this->pcount; };



private:
    int pcount;
    Vector3 *points;

    void destroy();
    void set(CatmullRom *src);

    std::vector<Vector3> insertedPoints;


};



#endif
