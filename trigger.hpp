#ifndef _TRIGGER_HPP_
#define _TRIGGER_HPP_

#include "externs.hpp"

const int TRIGGER_LINEAR = 1;
const int TRIGGER_COS	 = 2;
const int TRIGGER_SIN	 = 2;
const int TRIGGER_POLY2  = 3;
const int TRIGGER_POLY3  = 4;
const int TRIGGER_POLY4  = 5;
const int TRIGGER_POLY5  = 6;


class Trigger
{
public:
    Trigger() {};
    Trigger(int starttime, int endtime, int type);
    ~Trigger() {};

    float get(int time);

	int interpolateType;

    int st;
    int et;
};

class TriggerSystem
{
public:
    TriggerSystem();
    ~TriggerSystem();

    void add(int starttime, int endtime, int type = TRIGGER_LINEAR);
    bool getChanged();
    float get(int time);
	
	void saveList(char *filename);
	bool loadList(char *filename);

	void deleteNext(int time);

private:
    Lista2 *triggers;
	
	int previous;
	bool changed;
};



#endif
