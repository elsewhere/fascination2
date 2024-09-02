//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>

#ifdef _DEBUG
	#include <stdio.h>
	#include "mmgr.h"
#endif

#include "fontmanager.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Static members
//--------------------------------------------------------------------------------------------

bool FontManager::createdFlag = false;
FontManager *FontManager::instance = NULL;

//--------------------------------------------------------------------------------------------
//  Externals
//--------------------------------------------------------------------------------------------

extern TextureManager *tManager;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

FontManager::FontManager()
{
	nFonts = 0;	
}

FontManager::~FontManager()
{
}

FontManager *FontManager::create()
{

	if(!createdFlag)
	{					
		instance = new FontManager;
		if(!instance)
		{
			throw "FontManager::create(): Memory allocation error";
		}
		
		createdFlag = true;

		dmsMsg("FontManager::create(): FontManager instance created\n");
	}
	else
	{		
		throw "FontManager::create(): One instance of class FontManager allready funning\n";
	}	

	return instance;
}

void FontManager::debug()
{
	fonts.debug();
}

void FontManager::release()
{	
	if(createdFlag)
	{
		fonts.freeList();
	
		createdFlag = false;
		nFonts = 0;

		if(instance)
		{
			delete instance;
			instance = NULL;
		}

		dmsMsg("FontManager::release(): Instance deleted\n");		
	}
}

bool FontManager::addFont(int x, int y, char *name)
{
	Font *font;

	font = new Font;
	if(!font->init(x, y, name))
	{
		dmsMsg("FontManagaer::addFont Error, font initialization failed\n");
		return false;
	}

	fonts.addTail(font, name, 0);
	nFonts++;

	return true;
}

void FontManager::write2D(float x, float y, float a, float scale, char *name, char *msg, ...)
{
	Node <Font> *node = NULL;
	Font *f = NULL;
	char text[256];

	node = fonts.find(name);
	if(node)
	{
		f = node->a;
		if(f)
		{		
			if(!msg) return;
	
			va_list ap;
			va_start(ap, msg);
				vsprintf(text, msg, ap);
			va_end(ap);

			// muutetaan uppercaseksi ja otetaan pituus
			strupr(text);

			f->write2D(x, y, a, scale, text);
		}
	}
}

void FontManager::write3D(float x, float y, float z, float a, char *name, char *msg, ...)
{
	Node <Font> *node = NULL;
	Font *f = NULL;
	char text[256];

	node = fonts.find(name);
	if(node)
	{
		f = node->a;
		if(f)
		{		
			if(!msg) return;
	
			va_list ap;
			va_start(ap, msg);
				vsprintf(text, msg, ap);
			va_end(ap);

			// muutetaan uppercaseksi ja otetaan pituus
			strupr(text);

			f->write3D(x, y, z, a, text);
		}
	}
}

void FontManager::write3DEx(float x, float y, float z, float rx, float ry, float rz, float angle, float a, char *name, const char *msg, ...)
{
	Node <Font> *node = NULL;
	Font *f = NULL;
	char text[256];

	node = fonts.find(name);
	if(node)
	{
		f = node->a;
		if(f)
		{		
			if(!msg) return;
	
			va_list ap;
			va_start(ap, msg);
				vsprintf(text, msg, ap);
			va_end(ap);

			// muutetaan uppercaseksi ja otetaan pituus
			strupr(text);

			f->write3DEx(x, y, z, rx, ry, rz, angle, a, text);
		}
	}
}

//-------------------------------------------------------
// Getters
//-------------------------------------------------------

unsigned int FontManager::getFontCount()
{
	return nFonts;
}

Font *FontManager::getFont(unsigned int index)
{
	Node<Font> *getNode = NULL;

	(index > nFonts-1) ? index = nFonts-1 : index = index;
	(index < 0) ? index = 0 : index = index;
	
	getNode = fonts.get(index);

	if(getNode) return getNode->a;

	return NULL;
}

Font *FontManager::getFontName(char *name)
{
	Node<Font> *getNode = NULL;
		
	getNode = fonts.find(name);

	if(getNode) return getNode->a;

	return NULL;
}

