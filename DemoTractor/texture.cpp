//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>
#include <stdio.h>

#ifdef _DEBUG
	#include "mmgr.h"
#endif

#include "texture.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Texture::Texture()
{
	width = 0;
	height = 0;
	bpp = 0;
	ID = 0;
}

Texture::~Texture()
{
	image.release();
}

//-------------------------------------------------------
//	Public functions
//-------------------------------------------------------

bool Texture::loadTGA(char *name)
{
	if(!image.LoadTGA(name))
	{
		dmsMsg("Texture::loadTGA() failed with \"%s\"", name);
		return false;
	}

	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

bool Texture::loadPCX(char *name)
{
	if(!image.LoadPCX(name))
	{	
		dmsMsg("Texture::loadPCX() failed with \"%s\"", name);
		return false;
	}

	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

bool Texture::loadJPG(char *name)
{
	if(!image.LoadJPG(name))
	{		
		dmsMsg("Texture::loadJPG() failed with \"%s\"", name);
		return false;
	}

	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

bool Texture::loadPNG(char *name)
{
	if(!image.LoadPNG(name))
	{
		dmsMsg("Texture::loadJPG() failed with \"%s\"", name);
		return false;
	}

	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

bool Texture::loadPCXFromMemory(char *name, unsigned char *fileData, unsigned int fileSize)
{
	if(!image.LoadMemoryPCX(name, fileData, fileSize))
	{			
		dmsMsg("Texture::loadPCXFromMemory() failed with \"%s\"", name);
		return false;
	}
		
	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();	

	initTextureParameters();

	return true;
}

bool Texture::loadTGAFromMemory(char *name, unsigned char *fileData, unsigned int fileSize)
{
	if(!image.LoadMemoryTGA(name, fileData, fileSize))		
	{
		dmsMsg("Texture::loadTGAFromMemory() failed with \"%s\"", name);
		return false;
	}
		
	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();		

	initTextureParameters();

	return true;
}

bool Texture::loadJPGFromMemory(char *name, unsigned char *fileData, unsigned int fileSize)
{
	if(!image.LoadMemoryJPG(fileData, fileSize))
	{		
		dmsMsg("Texture::loadJPGFromMemory() failed with \"%s\"", name);
		return false;
	}
		
	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

bool Texture::loadPNGFromMemory(char *name, unsigned char *fileData, unsigned int fileSize)
{
	if(!image.LoadMemoryPNG(fileData, fileSize))
	{		
		dmsMsg("Texture::loadPNGFromMemory() failed with \"%s\"", name);
		return false;
	}
		
	width = image.GetWidth();
	height = image.GetHeight();
	type = image.getType();

	initTextureParameters();

	return true;
}

void Texture::setID(int i)
{
	ID = i;
}

int Texture::getID()
{
	return ID;
}

unsigned int Texture::getHeight()
{
	return height;
}

unsigned int Texture::getWidth()
{
	return width;
}

unsigned int Texture::getType()
{
	return type;
}

unsigned int *Texture::getImgData()
{
	return image.GetPtr();
}


void Texture::initTextureParameters()
{
	int w = width;
	int h = height;

	if((w == 1024 && h == 1024) || (w == 512 && h == 512) || (w == 256 && h == 256) || (w == 128 && h == 128) || (w == 64 && h == 64))
	{	
		buildMipMaps = false;
		setTextureParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
		setTextureParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);
		setTextureParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		setTextureParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		buildMipMaps = true;
		setTextureParameters(GL_TEXTURE_WRAP_S, GL_REPEAT);
		setTextureParameters(GL_TEXTURE_WRAP_T, GL_REPEAT);
		setTextureParameters(GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		setTextureParameters(GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	}
}

void Texture::setMipMaps(bool b)
{
	this->buildMipMaps = b;
}

void Texture::setTextureParameters(unsigned int pname, float value)
{
	switch(pname)
	{
	case GL_TEXTURE_MIN_FILTER:
			this->SET_GL_TEXTURE_MIN_FILTER = value;
		break;
	case GL_TEXTURE_MAG_FILTER:
			this->SET_GL_TEXTURE_MAG_FILTER = value;
		break;
	case GL_TEXTURE_WRAP_S:
			this->SET_GL_TEXTURE_WRAP_S = value;
		break;
	case GL_TEXTURE_WRAP_T:
			this->SET_GL_TEXTURE_WRAP_T = value;
		break;
	default:
		dmsMsg("Texture::setTextureParameters(): Unknown parameter name %i", pname);
		break;
	}
}