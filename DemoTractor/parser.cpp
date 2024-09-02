//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "parser.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Parser::Parser()
{
}

Parser::~Parser()
{
}

bool Parser::readRow(FILE *f, char *buffer)
{
	unsigned int index = 0, i;
	char ch = 0, buf[256] = {0};

	if(!f) return false;

	while(ch != '\n' && ch != '\r')
	{
		if(feof(f)) return false;

		ch = fgetc(f);
		buf[index++] = ch;		
	}

	// Poistetaan rivinvaiho lopusta
	for(i = 0; i < index-1; i++) buffer[i] = buf[i];

	return true;
}