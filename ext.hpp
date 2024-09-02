#ifndef _EXT_HPP_
#define _EXT_HPP_

#include "externs.hpp"
#include "DemoTractor/glext.h"

extern class Ext glExt;


class Ext
{
public:

	Ext() {
		initialized = false;
	}

	bool initialized;
	void init();
	void deinit();

	bool logFBOErrors();
	bool logFBOErrors(char *kohta);

	void createDepthTexture(GLuint &i, int w, int h);
	void createTexture(GLuint &i, int w, int h);
	void createTextureRECT(GLuint &i, int w, int h);


    //BAD BAD BAD BAD :)

    //purukumi - tuggummi
    //tehdään nää sit myöhemmin kunnolla

    void bindDepthFBO();
	void bindTextureFBO1024(GLuint textureID);
	void bindTextureFBO512(GLuint textureID);
	void bindTextureFBO256(GLuint textureID);
	void bindTextureFBO128(GLuint textureID);
//	void bindScreenFBO(GLuint textureID);
//	void bindSmallScreenFBO(GLuint textureID);
    void unbindFBO();

	// Draws screenbuffercontents back into screen
	void drawTexture(GLuint textureID);

    GLuint frameBufferTexture1024;
	GLuint frameBufferTexture512;
	GLuint frameBufferTexture256;
	GLuint frameBufferTexture128;
//    GLuint frameBufferScreen;
//    GLuint frameBufferSmallScreen;

    GLuint depthRenderBufferTexture1024;
	GLuint depthRenderBufferTexture512;
	GLuint depthRenderBufferTexture256;
	GLuint depthRenderBufferTexture128;
//    GLuint depthRenderBufferScreen;
//    GLuint depthRenderBufferSmallScreen;

    int screenWidth;
    int screenHeight;

    int smallW;
    int smallH;

	//Particle motion blur tekstuuri
	GLuint motionBlur1024;

	// Ruudun kokoinen tekstuuri
	GLuint glowTexture1024ID;
	GLuint glowTexture1024ID2;
	GLuint glowTexture512ID;
	GLuint glowTexture512ID2;
	GLuint glowTexture256ID;
	GLuint glowTexture256ID2;
	GLuint glowTexture128ID;
	GLuint glowTexture128ID2;

	//GLuint depthTex;
	//GLuint depthFBO;
	GLuint depthFBO, depthColTex, depthTex;

//  GLuint screenTextureID;
//	GLuint smallScreenTextureID;
//	GLuint smallScreenTextureID2;

	// glow
	int glowTextureW;
	int glowTextureH;
};


#endif