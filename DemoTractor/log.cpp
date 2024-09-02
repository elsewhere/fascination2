//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include "log.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Static members
//--------------------------------------------------------------------------------------------

bool Log::createdFlag = false;
bool Log::html = false;
Log *Log::instance = NULL;
char *Log::filename = NULL;
unsigned int Log::nErrors = 0;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Log::~Log()
{
}

Log *Log::create(char *name)
{
	html = false;
	if(!createdFlag)
	{
		FILE *f;
		char buf[256];

		filename = name;
		instance = new Log;
		createdFlag = true;
		
		f = fopen(filename, "w");
		if(!f)
		{
			char buf[512] = {0};
			
			sprintf(buf, "File %s cannot be created!\n", filename);
			throw buf;
			return NULL;
		}		

		sprintf(buf, "-->Log::create(char *name): File %s created\n", filename);
		fputs(buf,f);

		fclose(f);

	}
	else
	{
		throw "One instance of class Log allready running";
		return NULL;
	}

	return instance;
}

Log *Log::createHTML(char *name)
{
	html = true;
	if(!createdFlag)
	{
		FILE *f;
		char buf[256] = {0};

		filename = name;
		createdFlag = true;
		instance = new Log;

		f = fopen(filename, "w");
		if(!f)
		{
			char buf[512] = {0};
			
			sprintf(buf, "File %s cannot be created!\n", filename);
			throw buf;
			return NULL;
		}

		sprintf(buf,"<html>\n<head>\n<title>Log %s</title>\n</head>\n<body>\n", filename);
		fputs(buf, f);

		sprintf(buf,"<center><b>%s</b></center>\n<p>\n<hr>\n<p>\n<table border=\"0\">\n", filename);
		fputs(buf, f);

		sprintf(buf, "<tr>\n<td>\n-->Log::create(char *name): File %s created. </td>\n</tr>\n", filename);
		fputs(buf,f);

		sprintf(buf, "<tr>\n<td>\n&nbsp;</td>\n</tr>\n", filename);
		fputs(buf,f);

		fclose(f);

	}
	else
	{		
		throw "One instance of class Log allready running";
		return NULL;
	}

	return instance;
}

bool Log::writeToLog(char *text)
{
	FILE *f;
	char buf[256] = {0};
		
	f = fopen(filename, "r");
	if(!f)
	{
		if(html)
		{
			sprintf(buf, "<html>\n<head>\n<title>\n%s</title>\n</head>\n<body>\n<center><b>%s</b></center>\n<p>\n<hr>\n<p>\n<table>\n<tr>\n<td>\n-->Log::writeToLog(char *text): Previous %s file not found. File created.</td>\n</tr>\n", filename, filename);
		}
		else
		{
			sprintf(buf, "-->Log::writeToLog(char *text): Previous %s file not found. File created!\n\n");
		}
	}
	else
	{
		fclose(f);
	}

	f = fopen(filename, "a+");
	if(!f)
	{
		char buf[512] = {0};
			
		sprintf(buf, "File %s cannot be created!\n", filename);
		throw buf;
		return false;
	}
	fseek(f, 0, SEEK_END);
	fputs(buf, f);

	memset(buf, 0, 256);

	if(html)
	{
		sprintf(buf, "<tr>\n<td>\n-->Log::writeToLog(char *text): ");
		fputs(buf, f);
		
		fputs(text,f);
		
		sprintf(buf, "</td>\n</tr>\n");
		fputs(buf, f);
	}
	else
	{
		sprintf(buf, "");
		fputs(buf, f);
		fputs(text,f);
	}
	
	fflush(stdout);
	fclose(f);

	return true;
}

bool Log::writeToLog(char *text, char *color)
{
	FILE *f;
	char buf[256];

	memset(buf, 0, 256);
	
	f = fopen(filename, "r");
	if(!f)
	{
		if(html)
		{
			sprintf(buf, "<html>\n<head>\n<title>\n%s</title>\n</head>\n<body>\n<center><b>%s</b></center>\n<p>\n<hr>\n<p>\n<table>\n<tr>\n<td>\n-->Log::writeToLog(char *text) Warning! Previous %s file not found. File created.</td>\n</tr>\n", filename, filename);
		}
		else
		{
			sprintf(buf, "-->Log::writeToLog(char *text) Warning! Previous %s file not found. File created. \n");
		}
	}
	else
	{
		fclose(f);
	}

	f = fopen(filename, "a+");
	if(!f)
	{
		char buf[512] = {0};
			
		sprintf(buf, "File %s cannot be created!\n", filename);
		throw buf;
		return false;
	}
	fseek(f, 0, SEEK_END);
	fputs(buf, f);

	memset(buf, 0, 256);

	if(html)
	{
		sprintf(buf, "<tr>\n<td>\n<font color=\"%s\">\n-->Log::writeToLog(char *text): </font>\n", color);
		fputs(buf, f);
		
		fputs(text,f);
		
		sprintf(buf, "</td>\n</tr>\n");
		fputs(buf, f);
	}
	else
	{
		sprintf(buf, "-->Log::writeToLog(char *text): ");
		fputs(buf, f);
		fputs(text,f);
	}
	
	fflush(stdout);
	fclose(f);

	return true;
}

void Log::release()
{
	FILE *f;
	char buf[256];

	memset(buf, 0, 256);

	f = fopen(filename, "r");
	if(!f)
	{
		if(html)
		{
			sprintf(buf, "<html>\n<head>\n<title>\n%s</title>\n</head>\n<body>\n<center><b>%s</b></center>\n<p>\n<hr>\n<p>\n<table>\n<tr>\n<td>\n-->Log::writeToLog(char *text) Warning! Previous %s file not found. File created.</td>\n</tr>\n", filename, filename);
		}
		else
		{
			sprintf(buf, "-->Log::writeToLog(char *text) Warning! Previous %s file not found. File created. \n\n");
		}
	}
	else
	{
		fclose(f);
	}

	f = fopen(filename, "a+");
	if(!f)
	{
		char buf[512] = {0};
			
		sprintf(buf, "File %s cannot be created!\n", filename);
		MessageBox(NULL, buf, "Error", MB_OK | MB_ICONEXCLAMATION | MB_TOPMOST );
	}
	fseek(f, 0, SEEK_END);
	fputs(buf, f);	

	if(html)
	{
		sprintf(buf, "<tr>\n<td>\n&nbsp;</td>\n</tr>\n", filename);
		fputs(buf,f);

		sprintf(buf, "<tr>\n<td>\n-->Log::free() Instance deleted.</td>\n</tr>\n");
		fputs(buf, f);

		sprintf(buf,"</table>\n</body>\n</html>\n", filename);
		fputs(buf, f);
	}
	else
	{
		sprintf(buf, "\n-->Log::free() Instance deleted.\n");
		fputs(buf, f);
	}		

	fclose(f);
	
	createdFlag = false;

	if(instance)
	{
		delete instance;
		instance = NULL;
	}	
}
