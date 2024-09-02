#ifndef _BPM_HPP_
#define _BPM_HPP_

#include "externs.hpp"

extern class BPM *beat;
extern class BPM *beat2;
extern class BPM *beat4;

class BPM
{
public:
	BPM() {};
	~BPM();
	BPM(float value, int offset);

	float getValue();
	int getBeatcount();
	bool getChanged();


private:
	float value;
	int offset;
	int framecount;
	int previousbeatdist;
	bool changed;


};


#endif
