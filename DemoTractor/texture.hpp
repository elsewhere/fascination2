#ifndef _TEXTURE_HPP_
#define _TEXTURE_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "image.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Texture class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Texture
	{
		public:

			friend class TextureManager;

			Texture();
			~Texture();

			bool loadJPG(char *name);
			bool loadTGA(char *name);
			bool loadPCX(char *name);
			bool loadPNG(char *name);
			bool loadPCXFromMemory(char *name, unsigned char *fileData, unsigned int fileSize);
			bool loadTGAFromMemory(char *name, unsigned char *fileData, unsigned int fileSize);
			bool loadJPGFromMemory(char *name, unsigned char *fileData, unsigned int fileSize);
			bool loadPNGFromMemory(char *name, unsigned char *fileData, unsigned int fileSize);

			void setID(int i);

			int getID();
			unsigned int getWidth();
			unsigned int getHeight();
			unsigned int getType();
			unsigned int *getImgData();
		
			void initTextureParameters();
			void setMipMaps(bool b);
			void setTextureParameters(unsigned int pname, float value);

		private:

			float SET_GL_TEXTURE_MIN_FILTER;
			float SET_GL_TEXTURE_MAG_FILTER;
			float SET_GL_TEXTURE_WRAP_S;
			float SET_GL_TEXTURE_WRAP_T;
			bool buildMipMaps;

			int ID;
			unsigned int width, height;
			unsigned int bpp, type;
			Image image;
	};

}

#endif