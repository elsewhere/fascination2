//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <fstream>
#include <windows.h>
#include <time.h>
#include "PAKfile.hpp"
#include "globals.hpp"
using namespace std;

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

PAKFile::PAKFile()
{
	memset(sourceFolder, 0, sizeof(sourceFolder));
}

PAKFile::~PAKFile()
{
	for(int i = 0; i < header.nFiles; i++)
	{
		Node <FTEntry> *node = files.get(i);
		if(node)
		{
			FTEntry *ptr = node->a;
			if(ptr)
			{
				delete [] ptr->fileData;
				ptr->fileData = NULL;
			}
		}
	}

	files.freeList();
}

bool PAKFile::create(char *path, char *output)
{
	Node <FTEntry> *node = NULL;
	fpos_t offset = 0;
	FILE *f = NULL;	
	unsigned int i;

	memcpy(sourceFolder, path, strlen(path));

	if(!generateHeader()) return false;
	if(!generateFT()) return false;
	if(!generateFileOffsets()) return false;

	f = fopen(output, "wb");
	if(!f) return false;

	// Write in header
	fwrite(&header, sizeof(PAKHeader), 1, f);

	for(i = 0; i < header.nFiles; i++)
	{		
		node = files.get(i);
		if(node)
		{			
			FTEntry *ptr = node->a;
			if(ptr)
			{
				int index = 0;

				unsigned char *bytes = new unsigned char[sizeof(FTEntry)];
				if(!bytes) return false;

				memcpy(bytes, ptr, sizeof(FTEntry));

				for(index = 0; index < sizeof(FTEntry); index++)
				{
					unsigned char byte = bytes[index];

					fwrite(&byte, sizeof(unsigned char), 1, f);
				}

				if(bytes)
				{
					delete [] bytes;
					bytes = NULL;
				}
			}
		}
	}	

	fclose(f);

	// Write file datas into the PAK file
	// use fsetpos(); to position file pointer to a right offset	

	for(i = 0; i < header.nFiles; i++)
	{
		node = files.get(i);
		if(node)
		{			
			FTEntry *ptr = node->a;
			if(ptr)
			{
				char buffer[512] = {0};
				unsigned int index = 0;
				FILE *source = NULL;
				
				memcpy(buffer, path, strlen(path));
				lstrcat(buffer, "\\");
				lstrcat(buffer, ptr->fileName);				

				f = fopen(output, "r+b");
				source = fopen(buffer, "rb");
				if(!source || !f) return false;

				offset = ptr->fileOffset;
				fsetpos(f, &offset);

				for(index = 0; index < ptr->fileSize; index++)
				{
					unsigned char byte = fgetc(source);

					fwrite(&byte, sizeof(unsigned char), 1, f);
				}

				fclose(source);				
				fclose(f);
			}
		}
	}

	return true;
}

bool PAKFile::read(char *file)
{
	FILE *f = NULL;
	unsigned int i;
	fpos_t offset = 0;

	f = fopen(file, "rb");
	if(!f) return false;

	// Read in header
	fread(&header, sizeof(PAKHeader), 1, f);
/*
	cout << "Signature: " << header.signature << endl;
	cout << "Version: " << header.version << endl;
	cout << "Files in PAK: " << header.nFiles << endl;
	cout << "Cypher: " << header.cipherValue << endl;
	cout << "ID: " << header.uniqueID << endl;
*/
	for(i = 0; i < header.nFiles; i++)
	{
		FTEntry *ft = new FTEntry;

		fread(ft, sizeof(FTEntry), 1, f);

		ft->fileData = new unsigned char[ft->fileSize];
		if(!ft->fileData) return false;

		files.addTail(ft);
	}

	fclose(f);

	for(i = 0; i < header.nFiles; i++)
	{
		f = fopen(file, "rb");
     	if(!f) return false;

		Node <FTEntry> *node = files.get(i);
		if(node)
		{
			FTEntry *ptr = node->a;
			if(ptr)
			{
				offset = ptr->fileOffset;
				fsetpos(f, &offset);

				fread(ptr->fileData, sizeof(unsigned char), ptr->fileSize, f);
			}
		}

		fclose(f);
	}

	return true;
}

FTEntry *PAKFile::getFileTableEntry(int index)
{
	if(index >= 0 && index < files.getNodeCount())
	{
		Node <FTEntry> *node = files.get(index);

		if(node)
		{
			FTEntry *ptr = node->a;

			if(ptr) return ptr;
		}
	}

	return NULL;
}

// Fills in the header information
bool PAKFile::generateHeader()
{
	int i;

	srand(time(0));
	
	memcpy(header.signature, TRCPAK_SIGNATURE, sizeof(TRCPAK_SIGNATURE));
	header.version = TRCPAK_VERSION_NRO;
	header.nFiles = 0;
	header.cipherValue = rand()%8;

	for(i = 0; i < 10; i++)
	{
		header.uniqueID[i] = (unsigned char)rand()%256;
	}

	return true;
}

// Loops through target folder and adds all files to a file table
bool PAKFile::generateFT()
{
	string target = sourceFolder;
	WIN32_FIND_DATA fileData;
	HANDLE find = NULL;
	
	target += "\\*.*";
	find = FindFirstFile((char *)target.c_str(), &fileData);
	if(find == INVALID_HANDLE_VALUE) return false;
	
    while(find != INVALID_HANDLE_VALUE || GetLastError() == ERROR_NO_MORE_FILES)
	{
		if(	strcmp(fileData.cFileName, ".") != 0 && 
			strcmp(fileData.cFileName, "..") != 0 && 
			!( fileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY ) &&
			!( fileData.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN ) )
		{
  			cout << "File \"" << fileData.cFileName << "\" found in the folder" << endl;

			FTEntry *ft = new FTEntry;

			memcpy(ft->fileName, fileData.cFileName, strlen(fileData.cFileName));
			ft->fileOffset = 0;
			ft->fileSize = fileData.nFileSizeLow;

			files.addTail(ft);

			header.nFiles ++;
		}

		if(!FindNextFile(find, &fileData)) break;
	}

    FindClose(find);

	return true;
}

// Loops through file table and updates fileOffsets
bool PAKFile::generateFileOffsets()
{
	Node <FTEntry> *node = NULL;
	unsigned int headerFTSize = 0;
	unsigned int offset;
	unsigned int i = 0;

	headerFTSize = sizeof(PAKHeader) + (header.nFiles*sizeof(FTEntry));

	offset = headerFTSize + 1;
	for(i = 0; i < header.nFiles; i++)
	{
		node = files.get(i);
		if(node)
		{
			FTEntry *ptr = node->a;
			if(ptr)
			{				
				ptr->fileOffset = offset;
				offset += ptr->fileSize;
			}
		}
	}

	return true;
}

void PAKFile::debug()
{
	Node <FTEntry> *node = NULL;
	unsigned int i;

	for(i = 0; i < header.nFiles; i++)
	{
		node = files.get(i);
		if(node)
		{
			FTEntry *ptr = node->a;
			if(ptr)
			{				
				cout << "File name: " << ptr->fileName << endl;
				cout << "File offset: " << ptr->fileOffset << endl;
				cout << "File size: " << ptr->fileSize << endl;

				if(ptr->fileData)
				{
					unsigned int index = 0;

					cout << "File data: ";

					for(index = 0; index < ptr->fileSize; index++)
					{
						cout << ptr->fileData[index];
					}

					cout << endl;
				}
			}
		}
	}
}

unsigned int PAKFile::getFileCount()
{
	return header.nFiles;
}