#ifndef _FONT_HPP_
#define _FONT_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "texturemanager.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  FontUV class
//--------------------------------------------------------------------------------------------

	class FontUV
	{
		public:

			float u1, v1;		// vasemman ylänurkan texturekoordinaatit
			float u2, v2;		// oikean alanurkan texturekoordinaatit
	};

//--------------------------------------------------------------------------------------------
//  Font class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Font
	{
		public:

			Font();
			~Font();

			bool init(int x, int y, TextureManager *tManager, char *name);
			bool write(float x, float y, float z, const char *msg, ...);
			bool write(float x, float y, float z, float a, const char *msg, ...);

			// getterit
			int getFontWidth();
			int getFontHeight();

		private:

			Texture *fontMap;
			int fontX, fontY;
			float dx, dy;			// 1 / (texture.koko / fontX) jne.

			FontUV texels[43];		// 26 aakkosta + 17 merkkiä (numerot ja pari muuta)
	};

}

#endif