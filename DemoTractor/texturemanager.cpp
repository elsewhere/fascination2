//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>

#ifdef _DEBUG
	#include <stdio.h>
	#include "mmgr.h"
#endif

#include "texturemanager.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Static members
//--------------------------------------------------------------------------------------------

bool TextureManager::createdFlag = false;
TextureManager *TextureManager::instance = NULL;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

TextureManager::TextureManager()
{
	nTextures = 0;
}

TextureManager::~TextureManager()
{
}

TextureManager *TextureManager::create()
{
	if(!createdFlag)
	{				
		instance = new TextureManager;
		if(!instance)
		{
			throw "TextureManager::create(): Memory allocation error";
			return NULL;
		}

		createdFlag = true;

		dmsMsg("TextureManager::create(): TextureManager instance created\n");
	}
	else
	{		
		throw "One instance of class TextureManager allready running";
		return NULL;
	}	

	return instance;
}

bool TextureManager::addTexture(char *fname, char *name, int type)
{		
	int size = strlen(name);
	char buf[256] = {0};
	
	switch(type)
	{
		case PCX:
		{	
			Texture *texture = new Texture;

			if(!texture->loadPCX(fname)) 
			{	
				dmsMsg("TextureManager::addTexture(): File load failed with %s\n", fname);
				return false; 
			}			
			
			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTexture(): File \"%s\" loaded and added as texture \"%s\"\n", fname, name);			
						
		} break;

		case TGA:
		{			
			Texture *texture = new Texture;

			if(!texture->loadTGA(fname)) 
			{
				dmsMsg("TextureManager::addTexture(): File load failed with %s\n",fname);
				return false; 
			}		
						
			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTexture(): File \"%s\" loaded and added as texture \"%s\"\n", fname, name);
			
		} break;

		case JPG:
		{
			Texture *texture = new Texture;

			if(!texture->loadJPG(fname)) 
			{
				dmsMsg("TextureManager::addTexture(): File load failed with %s\n",fname);
				return false; 
			}

			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTexture(): File \"%s\" loaded and added as texture \"%s\"\n", fname, name);

		} break;

		case PNG:
		{			
			Texture *texture = new Texture;

			if(!texture->loadPNG(fname)) 
			{
				dmsMsg("TextureManager::addTexture(): File load failed with %s\n",fname);
				return false; 
			}

			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTexture(): File \"%s\" loaded and added as texture \"%s\"\n", fname, name);

		} break;

		default:
		{
			dmsMsg("TextureManager::addTexture(): File type not supported or invalid file type(%s)\n",fname);
		};
	}

	return true;
}

bool TextureManager::addTextureFromMemory(char *file, unsigned char *fileData, unsigned int fileSize, char *name, int type)
{		
	//int size = strlen(name);
	char buf[256] = {0};
	
	switch(type)
	{
		case PCX:
		{	
			Texture *texture = new Texture;

			if(!texture->loadPCXFromMemory(file, fileData, fileSize)) 
			{	
				dmsMsg("TextureManager::addTextureFromMemory(): File load failed with %s\n", file);
				return false; 
			}			
			
			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTextureFromMemory(): File \"%s\" loaded and added as texture \"%s\"\n", file, name);
						
		} break;

		case TGA:
		{	
			Texture *texture = new Texture;

			if(!texture->loadTGAFromMemory(file, fileData, fileSize)) 
			{	
				dmsMsg("TextureManager::addTextureFromMemory(): File load failed with %s\n", file);
				return false; 
			}			
			
			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTextureFromMemory(): File \"%s\" loaded and added as texture \"%s\"\n", file, name);
						
		} break;

		case JPG:
		{
			Texture *texture = new Texture;

			if(!texture->loadJPGFromMemory(file, fileData, fileSize)) 
			{
				dmsMsg("TextureManager::addTextureFromMemory(): File load failed with %s\n",file);
				return false; 
			}

			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTextureFromMemory(): File \"%s\" loaded and added as texture \"%s\"\n", file, name);

		} break;

		case PNG:
		{
			Texture *texture = new Texture;

			if(!texture->loadPNGFromMemory(file, fileData, fileSize)) 
			{
				dmsMsg("TextureManager::addTextureFromMemory(): File load failed with %s\n",file);
				return false; 
			}

			textures.addTail(texture, name, 0);
			nTextures++;

			dmsMsg("TextureManager::addTextureFromMemory(): File \"%s\" loaded and added as texture \"%s\"\n", file, name);

		} break;
		
		default:
		{
			dmsMsg("TextureManager::addTextureFromMemory(): File type not supported or invalid file type(%s)\n",file);
		};
	}

	return true;
}

bool TextureManager::addRenderToTexture(unsigned int w, unsigned int h, char *name)
{
	Texture *texture = new Texture;
						
	if(!texture)
	{
		dmsMsg("TextureManager::addRenderToTexture Error");
		return false;
	}

	texture->width = w;
	texture->height = h;
	texture->bpp = 32;
	texture->image.imagedata = new unsigned int[w * h];
	memset(texture->image.imagedata, 0, w*h*sizeof(unsigned int));
	
	textures.addTail(texture, name, 0);
	nTextures++;

	dmsMsg("TextureManager::addTexture(): RenderToTexture loaded and added as texture \"%s\"\n", name);		
	return true;
}

unsigned int TextureManager::getTextureCount()
{
	return nTextures;
}

 
//	HUOM! ID: 0 on openGL:n varaama ID, default-texturelle. Speksien mukaan
//	ei voi kuitenkaan luottaa siihen että numerointi menee aina lineaarisesti(?)
//
//  Meidän systeemissä textuurit on aina 32bit
void TextureManager::uploadTextures()
{
	unsigned int i, w, h, type;
	Node<Texture> *getNode = NULL;
	Texture *texture = NULL;

	dmsMsg("TextureManager::uploadTextures(): Uploading textures\n");

	for(i = 0; i < nTextures; i++)
	{
		unsigned int ID = 0;

		dmsLoadBar( 0.5f+ 0.15f*(i/float(nTextures)));

		getNode = textures.get(i);
		texture = getNode->a;

		w = texture->getWidth();
		h = texture->getHeight();
		type = texture->getType();		
		
		glGenTextures(1, &ID);
		glBindTexture(GL_TEXTURE_2D, ID);

		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,		texture->SET_GL_TEXTURE_WRAP_S);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,		texture->SET_GL_TEXTURE_WRAP_T);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,	texture->SET_GL_TEXTURE_MAG_FILTER);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,	texture->SET_GL_TEXTURE_MIN_FILTER);


		if(texture->buildMipMaps)
		{
			// tyyppi RGBA, eli oletetaan että kaikki textuurit ovat 32bit
			gluBuild2DMipmaps(GL_TEXTURE_2D, 4, w, h, GL_RGBA, GL_UNSIGNED_BYTE, texture->getImgData());	
		} 
		else 
		{
			glTexImage2D(GL_TEXTURE_2D, 0, 4, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->getImgData());		
		}

		texture->setID(ID);
	}

	dmsLoadBar(0.65f);

}

Texture *TextureManager::getTexture(unsigned int index)
{
	Node<Texture> *getNode = NULL;

	(index > nTextures-1) ? index = nTextures-1 : index = index;
	(index < 0) ? index = 0 : index = index;
	
	getNode = textures.get(index);

	if(getNode) return getNode->a;

	return NULL;
}

Texture *TextureManager::getTextureName(char *name)
{
	Node<Texture> *getNode = NULL;
	
	getNode = textures.find(name);
	
	if(getNode) return getNode->a;

	return NULL;
}

void TextureManager::debug()
{
	textures.debug();
}

void TextureManager::release()
{
	unsigned int i;
	Node<Texture> *getNode;
	Texture *texture;
	unsigned int ID;

	if(createdFlag)
	{

		for(i = 0; i < nTextures; i++)
		{		
			getNode = textures.get(i);
			texture = getNode->a;

			if(texture)
			{
				ID = texture->getID();
				glDeleteTextures(1, &ID);
			}
		}

		textures.freeList();
	
		createdFlag = false;
		nTextures = 0;

		if(instance)
		{
			delete instance;
			instance = NULL;
		}

		dmsMsg("TextureManager::release(): Instance deleted\n");
	}
}