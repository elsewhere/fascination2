#include "camera.hpp"

CameraHolder::CameraHolder()
{
    camcount = 0;
    cameras = 0;
}

CameraHolder::~CameraHolder()
{
    if (cameras)
    {
        delete [] cameras;
    }
}

CameraHolder::CameraHolder(int count)
{
    camcount = count;
    cameras = new Camera[camcount];
}

void CameraHolder::update()
{
    time = dmsGetModulePosition();
}
Camera& CameraHolder::getCamera(int index)
{
    return cameras[index];

}

float CameraHolder::getCameraTime(int index)
{
    float campos = (time - cameras[index].st) / (1.0f*(cameras[index].et - cameras[index].st));
    if (campos < 0.0f)
        campos = 0.0f;
    if (campos > 1.0f)
        campos = 1.0f;

    return campos;


}
void CameraHolder::useCamera(int index)
{
    float campos = this->getCameraTime(index);

    Vector3 p = cameras[index].path->getValue(campos);
    Vector3 t = cameras[index].target->getValue(campos);
    Vector3 u = Vector3(0,1,0);  //todo

    glLoadIdentity();
    gluLookAt(p.x, p.y, p.z, t.x, t.y, t.z, u.x, u.y, u.z);



}

void CameraHolder::initCamera(int index, int starttime, int endtime)
{
    cameras[index].path = new CatmullRom(); 
    cameras[index].target = new CatmullRom(); 
    cameras[index].st = starttime;
    cameras[index].et = endtime;

    cameras[index].path->startCreation();
    cameras[index].target->startCreation();
}

void CameraHolder::finalizeCamera(int index)
{
    cameras[index].path->endCreation();
    cameras[index].target->endCreation();
}

void CameraHolder::arcLengthParametrizeCamera(int index)
{
    cameras[index].path->arcLengthParametrize();
}
void CameraHolder::arcLengthParametrizeCameraTarget(int index)
{
    cameras[index].target->arcLengthParametrize();
}

void CameraHolder::addCameraPoint(int index, Vector3 &point)
{
    cameras[index].path->addPoint(point);
}

void CameraHolder::addCameraTargetPoint(int index, Vector3 &point)
{
    cameras[index].target->addPoint(point);

}

