#ifndef _FONT_HPP_
#define _FONT_HPP_

#include "texture.hpp"

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

			bool init(int x, int y, char *name);
			bool write2D(float xx, float yy, float a, float scale, const char *msg, ...);
			bool write3D(float x, float y, float z, float a, const char *msg, ...);
			bool write3DEx(float x, float y, float z, float rx, float ry, float rz, float angle, float a, const char *msg, ...);

			// getterit
			int getFontWidth();
			int getFontHeight();

		private:

			Texture *fontMap;
			int fontX, fontY;
			float dx, dy;			// 1 / (texture.koko / fontX) jne.

			FontUV texels[57];		// 26 aakkosta + 17 merkkiä (numerot ja pari muuta)
	};

}

#endif