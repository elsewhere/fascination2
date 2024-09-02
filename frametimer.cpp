#include "FrameTimer.hpp"

FrameTimer::FrameTimer()
{
    set(30, 10); //
}
FrameTimer::FrameTimer(int updatetime, int maxiterations)
{
    this->set(updatetime, maxiterations);
}

void FrameTimer::set(int updatetime, int maxiterations)
{
    this->cumultime = 0;
    this->updatetime = updatetime;
    this->maxiterations = maxiterations;
    this->prevtime = 0;
}
void FrameTimer::update()
{
    //aika timeristä
    int currenttime = dmsGetModulePosition();
    this->dt = currenttime - prevtime;
    this->prevtime = currenttime;

    if (this->dt < 0)
        this->dt = -this->dt; 

    this->cumultime += this->dt;

    //klippaus
    if (this->cumultime > this->maxiterations * this->updatetime)
    {
        cumultime = this->maxiterations * this->updatetime;

    }
}

int FrameTimer::getDeltaTime()
{
    return this->dt;
}


bool FrameTimer::stepsLeft()
{
    return (this->cumultime > this->updatetime);

}

void FrameTimer::endStep()
{
    this->cumultime -= this->updatetime;
}