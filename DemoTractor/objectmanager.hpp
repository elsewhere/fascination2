#ifndef _OBJECTMANAGER_HPP_
#define _OBJECTMANAGER_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "t3d.hpp"
#include "list.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Singleton ObjectManager class
//--------------------------------------------------------------------------------------------

	class ObjectManager
	{
		public:

			~ObjectManager();			

			// luonti funktio jolla varmistetaan ett‰ luokasta on vain
			// YKSI instanssi olemassa
			static ObjectManager *create();
			bool initObjects();
			bool addObject(char *fileName, char *name);
			bool addObjectFromMemory(char *file, unsigned char *fileData, unsigned int fileSize);
			void debug();
			void release();
			
			// getterit
			unsigned int getObjectCount();
			T3D *getObject(unsigned int index);
			T3D *getObjectName(char *name);				
			
		private:

			static bool createdFlag;			// true jos yksi instanssi olemassa
			static ObjectManager *instance;

			unsigned int nObjects;
			List <T3D> objects;

			// kun n‰m‰ on privatena niin voidaan est‰‰ uusien ilmentymien luonti
			ObjectManager();
			ObjectManager(const ObjectManager&) {}
			ObjectManager& operator = (const ObjectManager&) {}
	};

}

#endif