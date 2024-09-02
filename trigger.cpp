#include "trigger.hpp"

#include "math.h"
#include <sstream>
#include <iostream>
#include <string>
#include <fstream>


Trigger::Trigger(int starttime, int endtime, int type)
{
    st = starttime;
    et = endtime;
    interpolateType = type;
}

float Trigger::get(int time)
{
    if (time < st)
        return 0.0f;
    if (time >= et)
        return 0.0f;

	    //välissä 
			
//	float pos = 1 - (float)(time - st) / (float)(et - st);
//	return (float)fabs(sin(pos*1*3.141592f))*pos;

	if(this->interpolateType==TRIGGER_LINEAR) {
			return 1 - (float)(time - st) / (float)(et - st);
	} else if(interpolateType==TRIGGER_COS) {
			return cos ( ((float)(time - st) / (float)(et - st))*1.55f );
	} else if(interpolateType==TRIGGER_POLY2) {
			return pow( 1 - ((float)(time - st) / (float)(et - st)), 2 );
	} else if(interpolateType==TRIGGER_POLY3) {
			return pow( 1 - ((float)(time - st) / (float)(et - st)), 3 );
	} else if(interpolateType==TRIGGER_POLY4) {
			return pow( 1 - ((float)(time - st) / (float)(et - st)), 4 );
	} else if(interpolateType==TRIGGER_POLY5) {
			return pow( 1 - ((float)(time - st) / (float)(et - st)), 5 );
	}

	
	// default to linear
	return 1 - (float)(time - st) / (float)(et - st);

}

TriggerSystem::TriggerSystem()
{
    triggers = new Lista2();
	this->previous = 0;
	changed = false;
}
TriggerSystem::~TriggerSystem()
{
    delete triggers;
}

void TriggerSystem::add(int starttime, int endtime, int type)
{
    Trigger *t = new Trigger(starttime, endtime, type);

    triggers->add(t);
}

float TriggerSystem::get(int time)
{
    int i;
    float value = 0;
    int count = triggers->getNodeCount();
    triggers->goToStart();
    int foundcurrent=-1;

    for (i=0;i<count;i++)
    {
        Trigger *t = (Trigger *)triggers->getCurrent();
        float add = t->get(time);
		if(add>0.01f) foundcurrent =i;
		value += add;
        triggers->goForward();
    }

    if (value > 1.0f) value = 1.0f;

	changed = false;

	if (foundcurrent!=-1 && foundcurrent!=previous)
	{
		changed = true;
		previous = foundcurrent;
	}

    return value;
}

void TriggerSystem::saveList(char *filename) 
{
	std::fstream f;

	f.open(filename, std::ios::out|std::ios::binary);
	std::stringstream text, text2, text3;

	// save list contents
    int count = triggers->getNodeCount();
	triggers->goToStart();
	int i;
    for (i=0;i<count;i++)
    {
        Trigger *t = (Trigger *)triggers->getCurrent();
        //value += t->get(time);

        
		text.str("");
		text << t->st;
		text2.str("");
		text2 << t->et;
		text3.str("");
		text3 << t->interpolateType;

		//f.write(list[i].name.c_str(), list[i].name.length()+1);
		f.write(text.str().c_str(), text.str().length()+1);
		f.write(text2.str().c_str(), text2.str().length()+1);
		f.write(text3.str().c_str(), text3.str().length()+1);

		triggers->goForward();
	}

	f.write("\01", sizeof(char));
	f.close();
}


bool TriggerSystem::loadList(char *filename)
{
	std::fstream f;
	f.open(filename, std::ios::in|std::ios::binary);

	if (!f.is_open())
	{
		printf(">> ERROR: Failed to load %s\n", filename);
		return false;
	}

	// clear old list
	this->triggers->destroy();
	
	while(1)
	{
		std::string start="", end="", type="";
		char chunk_char=' ';
		
		int i;
		for(i=0; chunk_char != '\0';i++)
		{
			f.read(&chunk_char, sizeof(char));
			if (chunk_char == '\01')
			{
				f.close();
				return true;
			}

			if (chunk_char != '\0')
			{
				start.append(1,chunk_char);
			}
		}

		chunk_char=' ';
		
		for(i=0; chunk_char != '\0'; i++)
		{
			f.read(&chunk_char, sizeof(char));

			if (chunk_char != '\0')
			{
				end.append(1,chunk_char);
			}
		}
		chunk_char=' ';

		for(i=0; chunk_char != '\0'; i++)
		{
			f.read(&chunk_char, sizeof(char));

			if (chunk_char != '\0')
			{
				type.append(1,chunk_char);
			}
		}

		this->add(atoi(start.c_str()), atoi(end.c_str()), atoi(type.c_str()) );
	}

	f.close();

	return true;
}

void TriggerSystem::deleteNext(int time) 
{
    int i;
    int count = triggers->getNodeCount();
    triggers->goToStart();
	int trigger_to_delete = -1;
	int last_time = -1;

    for (i=0;i<count;i++)
    {
        Trigger *t = (Trigger *)triggers->getCurrent();
        if(time <= t->st) {

			if(t->st <= last_time || last_time==-1) {

				trigger_to_delete = i;
				last_time = t->st;

			}
		} 
        triggers->goForward();
    }

	// mennään seuraavaan triggeriin

	if(last_time==-1 || trigger_to_delete == -1) return;

	this->triggers->goToNode(trigger_to_delete);
	this->triggers->remove();
}

bool TriggerSystem::getChanged()
{
	return changed;
}

/*#include "trigger.hpp"

Trigger::Trigger(int starttime, int endtime)
{
    st = starttime;
    et = endtime;
    

}

float Trigger::get(int time)
{
    if (time < st)
        return 0.0f;
    if (time >= et)
        return 0.0f;

    //välissä 
    return 1 - (float)(time - st) / (float)(et - st);
}


TriggerSystem::TriggerSystem()
{
    triggers = new Lista2();
}
TriggerSystem::~TriggerSystem()
{
    delete triggers;
}

void TriggerSystem::add(int starttime, int endtime)
{
    Trigger *t = new Trigger(starttime, endtime);
    triggers->add(t);
}

float TriggerSystem::get(int time)
{
    int i;
    float value = 0;
    int count = triggers->getNodeCount();
    triggers->goToStart();
    
    for (i=0;i<count;i++)
    {
        Trigger *t = (Trigger *)triggers->getCurrent();
        value += t->get(time);
        triggers->goForward();
    }

    if (value > 1.0f)
        value = 1.0f;

    return value;
}
*/