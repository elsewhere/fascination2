//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>

#ifdef _DEBUG
	#include <stdio.h>
	#include "mmgr.h"
#endif

#include "objectmanager.hpp"
#include "t3d.hpp"
#include "globals.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Static members
//--------------------------------------------------------------------------------------------

bool ObjectManager::createdFlag = false;
ObjectManager *ObjectManager::instance = NULL;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

ObjectManager::ObjectManager()
{
	nObjects = 0;	
}

ObjectManager::~ObjectManager()
{
}

ObjectManager *ObjectManager::create()
{

	if(!createdFlag)
	{		
		dmsMsg("EffectManager::create(): ObjectManager instance created\n");

		createdFlag = true;
		instance = new ObjectManager;
		if(!instance)
		{
			throw "ObjectManager::create(): Memory allocation error";
		}
	}
	else
	{		
		throw "One instance of class ObjectManager allready running";
	}	

	return instance;
}

bool ObjectManager::initObjects()
{
	unsigned int i;
	Node<T3D> *getNode = NULL;
	T3D *ptr = NULL;

	for(i = 0; i < objects.getNodeCount(); i++)
	{		
		getNode = objects.get(i);
		if(getNode)
		{		
			ptr = getNode->a;
			if(ptr)
			{				
			}
		}		
	}

	return true;
}

bool ObjectManager::addObject(char *fileName, char *name)
{
	T3D *obj = NULL;
	char buf[256] = {0};

	obj = new T3D;
	if(!obj)
	{
		dmsMsg("ObjectManager::addObject() error: Couldn't allocate memory\n");
		return false;
	}

	if(!obj->load(fileName))
	{
		dmsMsg("ObjectManager::addObject() error: Couldn't import %s\n", fileName);
		return false;
	}

	sprintf(buf, "%s", name);
	objects.addTail(obj, buf, 0);
	nObjects++;

	dmsMsg("ObjectManager::addObject(): File \"%s\" loaded and added as object \"%s\"\n", fileName, buf);
		
	return true;
}

bool ObjectManager::addObjectFromMemory(char *file, unsigned char *fileData, unsigned int fileSize)
{
	T3D *obj = NULL;
	char buf[256] = {0};

	obj = new T3D;
	if(!obj)
	{
		dmsMsg("ObjectManager::addObject() error: Couldn't allocate memory\n");
		return false;
	}

	if(!obj->loadFromMemory(fileData, fileSize))
	{
		dmsMsg("ObjectManager::addObject() error: Couldn't import %s\n", file);
		return false;
	}

	sprintf(buf, "%s", file);
	objects.addTail(obj, buf, 0);
	nObjects++;

	dmsMsg("ObjectManager::addObject(): File \"%s\" loaded and added as object \"%s\"\n", file, buf);
	return true;
}

void ObjectManager::debug()
{
	objects.debug();
}

void ObjectManager::release()
{		
	if(createdFlag)
	{
		objects.freeList();
	
		createdFlag = false;
		nObjects = 0;

		if(instance)
		{
			delete instance;
			instance = NULL;
		}

		dmsMsg("ObjectManager::release(): Instance deleted\n");		
	}
}

unsigned int ObjectManager::getObjectCount()
{
	return nObjects;
}

T3D *ObjectManager::getObject(unsigned int index)
{
	Node<T3D> *getNode = NULL;

	(index > nObjects-1) ? index = nObjects-1 : index = index;
	(index < 0) ? index = 0 : index = index;
	
	getNode = objects.get(index);

	if(getNode) return getNode->a;

	return NULL;
}

T3D *ObjectManager::getObjectName(char *name)
{
	Node<T3D> *getNode = NULL;
	
	getNode = objects.find(name);
	
	if(getNode) return getNode->a;

	return NULL;
}
