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

	class Texture
	{
		public:

			friend class TextureManager;

			Texture();
			~Texture();

			bool loadJPG(char *name);
			bool loadTGA(char *name);
			bool loadPCX(char *name);

			void setID(int i);

			int getID();
			unsigned int getWidth();
			unsigned int getHeight();
			unsigned int getType();
			unsigned int *getImgData();

		private:

			int ID;
			unsigned int width, height;
			unsigned int bpp, type;
			Image image;
	};

}

#endif