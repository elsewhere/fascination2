#ifndef _FONTMANAGER_HPP_
#define _FONTMANAGER_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "font.hpp"
#include "list.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Singleton FontManager class
//--------------------------------------------------------------------------------------------

	class FontManager
	{
		public:

			~FontManager();			

			// luonti funktio jolla varmistetaan ett‰ luokasta on vain
			// YKSI instanssi olemassa
			static FontManager *create();
					
			bool addFont(int x, int y, char *name);			
			void write2D(float x, float y, float a, float scale, char *name, char *msg, ...);
			void write3D(float x, float y, float z, float a, char *name, char *msg, ...);			
			void write3DEx(float x, float y, float z, float rx, float ry, float rz, float angle, float a, char *name, const char *msg, ...);
			void debug();
			void release();

			// Getters
			unsigned int getFontCount();
			Font *getFont(unsigned int index);
			Font *getFontName(char *name);
			
		private:

			static bool createdFlag;			// true jos yksi instanssi olemassa
			static FontManager *instance;

			unsigned int nFonts;
			List <Font> fonts;

			// kun n‰m‰ on privatena niin voidaan est‰‰ uusien ilmentymien luonti
			FontManager();
			FontManager(const FontManager&) {}
			FontManager& operator = (const FontManager&) {}
	};

}

#endif