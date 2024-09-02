#ifndef _ANALYZER_HPP_
#define _ANALYZER_HPP_

#include "externs.hpp"

class Analyzer
{
	public:
		Analyzer(int tapcount);
		~Analyzer();
		float get();
		float get_balanced();
		
	private:
		int tapcount;
		float *summat;
		
		float last_return;	
};

#endif