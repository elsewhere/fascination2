#ifndef _EFFECTMANAGER_HPP_
#define _EFFECTMANAGER_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "base.hpp"
#include "list.hpp"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Singleton EffectManager class
//--------------------------------------------------------------------------------------------

	class EffectManager
	{	
		public:

			~EffectManager();

			static EffectManager *create();

			bool initEffects();
			bool addEffect(unsigned long s, unsigned long e, Base *effect, char *name);

			unsigned int getEffectCount();
			Base *getEffect(unsigned int index);
			Base *getEffect(char *name);
			void release();

			void debug();

		private:

			static bool createdFlag;			// true jos yksi instanssi olemassa
			static EffectManager *instance;

			unsigned int nEffects;
			List <Base> effects;

			// kun n‰m‰ on privatena niin voidaan est‰‰ uusien ilmentymien luonti
			EffectManager();
			EffectManager(const EffectManager&) {}
			EffectManager& operator = (const EffectManager&) {}

	};

}

#endif