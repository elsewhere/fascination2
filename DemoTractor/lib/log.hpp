#ifndef _LOG_HPP_
#define _LOG_HPP_

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  Singleton Log class
//--------------------------------------------------------------------------------------------

	class Log
	{
		public:

			~Log();

			static Log *create(char *name);
			static Log *createHTML(char *name);
			bool writeToLog(char *text);
			bool writeToLog(char *text, char *color);

			void release();			

		private:

			static bool createdFlag;
			static Log *instance;
			static char *filename;
			static bool html;
			static unsigned int nErrors;
			
			Log() {}
			Log(const Log &) {}
			Log& operator = (const Log &) {}
	};

}

#endif