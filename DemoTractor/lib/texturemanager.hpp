#ifndef _TEXTUREMANAGER_HPP_
#define _TEXTUREMANAGER_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "texture.hpp"
#include "list.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Defines for supported formats
//--------------------------------------------------------------------------------------------

	#define PCX 0
	#define TGA 1
	#define JPG 2
	#define PNG 3

//--------------------------------------------------------------------------------------------
//  Singleton TextureManager class
//--------------------------------------------------------------------------------------------

	class TextureManager
	{
		public:

			~TextureManager();			

			// luonti funktio jolla varmistetaan ett‰ luokasta on vain
			// YKSI instanssi olemassa
			static TextureManager *create();
			
			void uploadTextures();
			bool addTexture(char *fname, char *name, int type);
			bool addRenderToTexture(unsigned int w, unsigned int h, char *name);
			
			// Getterit
			unsigned int getTextureCount();
			Texture *getTexture(unsigned int index);
			Texture *getTextureName(char *name);		
			void debug();

			void release();
			
		private:

			static bool createdFlag;			// true jos yksi instanssi olemassa
			static TextureManager *instance;

			unsigned int nTextures;
			List <Texture> textures;

			// kun n‰m‰ on privatena niin voidaan est‰‰ uusien ilmentymien luonti
			TextureManager();
			TextureManager(const TextureManager&) {}
			TextureManager& operator = (const TextureManager&) {}
	};

}

#endif