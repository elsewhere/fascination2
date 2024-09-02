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
			void resetEffects();
			void resetEffect(Base *b);
			bool addEffect(unsigned long s, unsigned long e, unsigned int prio, Base *effect, char *name);
			void sortEffects();
			void setPriority(unsigned int prio, char *name);
			void setPriority(unsigned int prio, unsigned int index);

			unsigned int getEffectCount();
			Base *getEffect(unsigned int index);
			Base *findEffect(char *name);
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