#ifndef _OBJECTMANAGER_HPP_
#define _OBJECTMANAGER_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "object.hpp"
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
			void debug();
			void release();
			
			// getterit
			unsigned int getObjectCount();
			Object *getObject(unsigned int index);
			Object *getObjectName(char *name);				
			
		private:

			static bool createdFlag;			// true jos yksi instanssi olemassa
			static ObjectManager *instance;

			unsigned int nObjects;
			List <Object> objects;

			// kun n‰m‰ on privatena niin voidaan est‰‰ uusien ilmentymien luonti
			ObjectManager();
			ObjectManager(const ObjectManager&) {}
			ObjectManager& operator = (const ObjectManager&) {}
	};

}

#endif