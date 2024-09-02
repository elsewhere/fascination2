#ifndef _BPM_HPP_
#define _BPM_HPP_

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  BPM class
//--------------------------------------------------------------------------------------------

	class BPM
	{
		public:

			BPM() {};
			~BPM();
			BPM(float value, float offset);

			float getValue();
			int getBeatcount();
			bool getChanged();

		private:

			float value;
			float offset;
			int framecount;
			int previousbeatdist;
			bool changed;
	};

}

#endif