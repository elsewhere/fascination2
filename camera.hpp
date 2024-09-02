#ifndef _CAMERA_HPP_
#define _CAMERA_HPP_

#include "externs.hpp"
#include "catmullrom.hpp"

extern class CameraHolder *cam;

class Camera
{
public:
    Vector3 position;
    Vector3 direction;
    Vector3 upwards;

    int st;
    int et;

    class CatmullRom *path;
    class CatmullRom *target;

};

class CameraHolder
{
public:
    CameraHolder();
    CameraHolder(int count);
    ~CameraHolder();

    void update();

    void initCamera(int index, int starttime, int endtime);
    void finalizeCamera(int index);
    void arcLengthParametrizeCamera(int index);
    void arcLengthParametrizeCameraTarget(int index);
    void addCameraPoint(int index, Vector3 &point);
    void addCameraTargetPoint(int index, Vector3 &point);
    void useCamera(int index);
    
    Camera& getCamera(int index);
    float getCameraTime(int index);

    int time;
    int camcount;
    Camera *cameras;



};

#endif