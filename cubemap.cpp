
#include "cubemap.hpp"


Cubemap::Cubemap()
{
    this->cubeMap = 0;
    this->renderToTexture = false;
    this->dynamic = false;
}

void Cubemap::setupDynamic(int res)
{
    this->res = res;
    this->renderToTexture = false;
    this->dynamic = true;

    //luodaan cubemapit
    glGenTextures(1, &this->cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, this->cubeMap);

    unsigned int *tempdata = new unsigned int [this->res * this->res];

    for (int i = 0; i < this->res * this->res; i++)
    {
        tempdata[i] = 0;
    }

    //tyhjiä tekstuureja
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);

	rotations[0][0] = -90.0f; rotations[0][1] = 0.0f; rotations[0][2] = 1.0f; rotations[0][3] = 0.0f;
	rotations[1][0] =  90.0f; rotations[1][1] = 0.0f; rotations[1][2] = 1.0f; rotations[1][3] = 0.0f;
	rotations[2][0] = -90.0f; rotations[2][1] = 1.0f; rotations[2][2] = 0.0f; rotations[2][3] = 0.0f;
	rotations[3][0] =  90.0f; rotations[3][1] = 1.0f; rotations[3][2] = 0.0f; rotations[3][3] = 0.0f;
	rotations[4][0] = 180.0f; rotations[4][1] = 1.0f; rotations[4][2] = 0.0f; rotations[4][3] = 0.0f;
	rotations[5][0] = 180.0f; rotations[5][1] = 0.0f; rotations[5][2] = 0.0f; rotations[5][3] = 1.0f;

    //tekstuuriparametrit. TODO: siirto muualle? 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP);	
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    delete [] tempdata;
}


void Cubemap::setupDynamic(int res, string name)
{
    int i = 0;
    this->res = res;
    this->renderToTexture = true;
    this->dynamic = true;

    //nimet tekstuureille
    for (i = 0; i < 6; i++)
    {
        this->texturenames[i] = name;
    }

    this->texturenames[0].append("00");
    this->texturenames[1].append("01");
    this->texturenames[2].append("02");
    this->texturenames[3].append("03");
    this->texturenames[4].append("04");
    this->texturenames[5].append("05");

    //luodaan tekstuurit
    for (i = 0; i < 6; i++)
    {
        dmsAddRenderToTexture(this->res, this->res, this->texturenames[i].c_str());
        this->textureID[i] = dmsGetTexture(this->texturenames[i].c_str())->getID();

    }

    //luodaan cubemapit
    glGenTextures(1, &this->cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, this->cubeMap);

    unsigned int *tempdata = new unsigned int [this->res * this->res];
    for (i = 0; i < this->res * this->res; i++)
    {
        tempdata[i] = 0;
    }

    //tyhjiä tekstuureja
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, tempdata);

    //tekstuuriparametrit. TODO: siirto muualle? 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP);	
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
/*
	cubeTarget[0] = GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT;
	cubeTarget[1] = GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT;
	cubeTarget[2] = GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT;
	cubeTarget[3] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT;
	cubeTarget[4] = GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT;
	cubeTarget[5] = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT;

*/
	rotations[0][0] = -90.0f; rotations[0][1] = 0.0f; rotations[0][2] = 1.0f; rotations[0][3] = 0.0f;
	rotations[1][0] =  90.0f; rotations[1][1] = 0.0f; rotations[1][2] = 1.0f; rotations[1][3] = 0.0f;
	rotations[2][0] = -90.0f; rotations[2][1] = 1.0f; rotations[2][2] = 0.0f; rotations[2][3] = 0.0f;
	rotations[3][0] =  90.0f; rotations[3][1] = 1.0f; rotations[3][2] = 0.0f; rotations[3][3] = 0.0f;
	rotations[4][0] = 180.0f; rotations[4][1] = 1.0f; rotations[4][2] = 0.0f; rotations[4][3] = 0.0f;
	rotations[5][0] = 180.0f; rotations[5][1] = 0.0f; rotations[5][2] = 0.0f; rotations[5][3] = 1.0f;
    delete [] tempdata;
}


void Cubemap::setupStatic(Texture *t1)
{
    this->renderToTexture = false;

    this->res = t1->getWidth(); //oletetaan neliö

    glGenTextures(1, &this->cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, this->cubeMap);

    unsigned int *texturedata = t1->getImgData();
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, texturedata);

	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP);	
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
}

void Cubemap::setupStatic(Texture *t1, Texture *t2, Texture *t3, Texture *t4, Texture *t5, Texture *t6)
{
    this->renderToTexture = false;
    this->res = t1->getWidth(); //oletetaan neliö

    glGenTextures(1, &this->cubeMap);
    glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, this->cubeMap);

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t1->getImgData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t2->getImgData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t3->getImgData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t4->getImgData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t5->getImgData());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_EXT, 0, 3, this->res, this->res, 0, GL_RGBA, GL_UNSIGNED_BYTE, t6->getImgData());

	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
    glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_CUBE_MAP_EXT, GL_TEXTURE_WRAP_T, GL_CLAMP);	
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
    glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP_EXT);
}

void Cubemap::bind()
{
	glBindTexture(GL_TEXTURE_CUBE_MAP_EXT, this->cubeMap);
}

unsigned int Cubemap::getID()
{
    return this->cubeMap;
}

void Cubemap::startRendering()
{
    //matriisit talteen
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();

    glViewport(0, 0, this->res, this->res);
    //viewportti kohdalleen ja 90 asteen FOV
	glLoadIdentity();
	gluPerspective(90.0f, 1.0f, 1.0f, 5000.0f); //TODO: near ja far-planet kunnolla
	glMatrixMode(GL_MODELVIEW);

    this->bind();

}

void Cubemap::endRendering()
{
    glViewport(0, 0, dmsGetWindowWidth(), dmsGetWindowHeight());	
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();


}

void Cubemap::setupRenderSide(int side)
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	glRotatef(rotations[side][0], rotations[side][1], rotations[side][2], rotations[side][3]);
	if(side == 0 || side == 1)
	{
		glRotatef(180.0f, 0.0f, 0.0f, 1.0f);			
	}
}

void Cubemap::finishRenderSide(int side)
{
    this->bind(); //??
	glCopyTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X_EXT+side, 0, 0, 0, 0, 0, this->res, this->res);

    //TODO: fbo
    if (this->renderToTexture)
    {
	    switch(side)
	    {
		    case 0: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[0]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;

		    case 1: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[1]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;

		    case 2: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[2]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;

		    case 3: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[3]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;

		    case 4: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[4]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;

		    case 5: 
		    {
			    glBindTexture(GL_TEXTURE_2D, this->textureID[5]);
			    glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 0, 0, this->res, this->res, 0);
		    } break;
	    }		
    }
}


Cubemap::~Cubemap()
{

}