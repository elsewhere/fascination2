#ifndef _FrameTimer_HPP_
#define _FrameTimer_HPP_

#include "externs.hpp"

class FrameTimer
{
public:
    FrameTimer();
    //eka luku = p‰ivitysten v‰li (ms), toka luku = kuinka monta kertaa max
    FrameTimer(int updatetime, int maxiterations);

    int getDeltaTime();
    void set(int updatetime, int maxiterations);

    //kutsu update joka frame
    void update();
    //looppaa t‰t‰
    bool stepsLeft();
    //loopin loppuun t‰m‰
    void endStep();

private:
    int dt; //delta edellisen framen j‰ljilt‰
    int prevtime; //edellinen frame
    int cumultime; //kokonaisaika
    int updatetime; //kuinka usein p‰ivitet‰‰n (ms)
    int maxiterations; //kuinka monta kertaa max



};


#endif