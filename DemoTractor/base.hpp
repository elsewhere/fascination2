#ifndef _BASE_HPP_
#define _BASE_HPP_

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Base class
//--------------------------------------------------------------------------------------------

	class __declspec(dllexport) Base
	{
		friend class EffectManager;

		public:
			
			// constructori ei voi olla virtual
			Base() { };
			virtual ~Base() { };

			virtual bool init(unsigned long s, unsigned long e);
			virtual void update(float t);
			virtual void draw() = 0;
			virtual void release();

			// checks if the effect is active
			bool isActive();

			virtual void renderScene(float pos, float alpha) = 0;

		protected:

			bool active;			
			float time;
			unsigned long startTime, endTime;
	};

}

#endif