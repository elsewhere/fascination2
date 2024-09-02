#ifndef _PAKFILE_HPP_
#define _PAKFILE_HPP_

//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <iostream>

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"	
#endif

#include "list.hpp"

using namespace std;

#define TRCPAK_SIGNATURE "TRCPAK"
#define TRCPAK_VERSION_NRO 1.0f

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

//--------------------------------------------------------------------------------------------
//  PAKHeader class
//--------------------------------------------------------------------------------------------

	class PAKHeader
	{
		public:

			PAKHeader()
			{
				memset(signature, 0, sizeof(signature));
				memcpy(signature, TRCPAK_SIGNATURE, sizeof(TRCPAK_SIGNATURE));
				version = 1.0f;
				nFiles = 0;
			}

			char signature[6];
			float version;
			unsigned int nFiles;
			unsigned char cipherValue;
			char uniqueID[10];
	};

//--------------------------------------------------------------------------------------------
//  File table entry class
//--------------------------------------------------------------------------------------------

	class FTEntry
	{
		public:

			FTEntry()
			{
				memset(fileName, 0, sizeof(fileName));
				fileSize = 0;
				fileOffset = 0;
				fileData = NULL;
			}

			~FTEntry()
			{
				if(fileData)
				{
					delete [] fileData;
					fileData = NULL;
				}
			}

			char fileName[256];
			unsigned char *fileData;			
			unsigned int fileSize;
			unsigned int fileOffset;
	};

//--------------------------------------------------------------------------------------------
//  PAK file format class
//
//  Structure:
//
//  - PAK File Header
//  - FileTable
//  - Encrypted data (using Ceasers Cypher addition)
//--------------------------------------------------------------------------------------------

	class PAKFile
	{
		public:
			
			PAKFile();
			~PAKFile();

			bool create(char *path, char *output);
			bool read(char *file);
			FTEntry *getFileTableEntry(int index);
			void debug();

			unsigned int getFileCount();

		private:

			bool generateHeader();
			bool generateFT();
			bool generateFileOffsets();

			char sourceFolder[256];
			PAKHeader header;
			List <FTEntry> files;
	};
}

#endif