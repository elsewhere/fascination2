#ifndef _SOUND_HPP_
#define _SOUND_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "fmod.h"
#include "fmod_errors.h"

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Callback prototypes
//--------------------------------------------------------------------------------------------

	signed char endcallback(FSOUND_STREAM *stream, void *buff, int len, int param);

//--------------------------------------------------------------------------------------------
//
//  Singleton Sound class
//
//  Initializes FMOD 
//
//--------------------------------------------------------------------------------------------

	class Sound
	{
		public:

			~Sound();

			static Sound *create();
			static bool checkEnabled();
			bool init();		
			void setVolume(FMUSIC_MODULE *mod, int i);
			void close();

			/* Palauttaa taulukon jossa ‰‰nen spektri */
			float *getSpectrum();

			static bool checkSync();
			static void setEnabled(bool f);
			static void setSync(bool f);

		private:

			static bool createdFlag;
			static bool enabled;
			static Sound *instance;
			static bool syncFlag;
			
			Sound() {}
			Sound(const Sound &) {}
			Sound& operator = (const Sound &) {}
	};

//--------------------------------------------------------------------------------------------
//  Sample class (WAV)
//--------------------------------------------------------------------------------------------

	class Sample
	{
		public:

			Sample();
			~Sample();

			bool load(char *name);
			void play();
			void release();

		private:

			FSOUND_SAMPLE *sample;
	};

//--------------------------------------------------------------------------------------------
//
//  Song class
//
//  Handles stream and module supperted in FMOD
//
//--------------------------------------------------------------------------------------------

	class Song
	{
		public:

			Song();
			~Song();
			
			bool loadMod(char *name);
			bool loadStream(char *name);
			
			void start();
			void stop();
			void release();		
			
			void setPosition(unsigned int offset);
			void setPause(bool f);

			int getLenght();
			int getPosition();
			bool checkPlaying();
			FMUSIC_MODULE *getMod();

		private:

			int mode;
			bool isPlaying;

			FMUSIC_MODULE *mod;
			FSOUND_STREAM *stream;

			char *data;
			
			int lenght;
			int channel;
	};

}

#endif