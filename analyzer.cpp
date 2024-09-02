#include "analyzer.hpp"

Analyzer::Analyzer(int tapcount)
{
	int i;
	this->tapcount = tapcount;
	this->summat = new float[this->tapcount];
	
	for (i=0;i<this->tapcount;i++)
	{
		summat[i] = 0;
	}
	last_return=0;
}

Analyzer::~Analyzer()
{
    delete [] summat;
}

float Analyzer::get()
{
    int i;
    
	float spectrum[ 512 ];
	for(int m=0; m<511; m++) spectrum[m]=0;
	dmsGetSpectrum( spectrum, 512 );

    float total = 0.0f;
    for (i=0;i<511;i++)
    {
        total += spectrum[i];
    }
    for (i=0;i<tapcount-1;i++)
    {
        summat[i] = summat[i+1];
    }
    summat[tapcount-1] = total;
    float val = 0.0f;
    for (i=0;i<tapcount;i++)
    {
        val += summat[i]*(1.0f/tapcount);
    }
	
    return val;
	
}


// okayish
float Analyzer::get_balanced()
{

	const float drop_per_sec = 7.0f;

	// tää vois olla  riippuvainen keskimääräsestä volasta ja last_returnin korkeudesta - TODO!
	last_return -= dmsGetDeltaTime() * drop_per_sec*5;

	float newvalue = get();

	if(newvalue>last_return) last_return = newvalue;
	//last_return -= dmsGetDeltaTime() * (drop_per_sec+(last_return-drop_per_sec));


//	dmsConsoleMsg( 0, 8, "newvalue:      %f",newvalue);
//	dmsConsoleMsg( 0, 9, "returnval:     %f",last_return);
	
	return last_return;	
}




