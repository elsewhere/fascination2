//////////////////////////////////////////////////////////////////////
// shader.h: place your shader classes here
//			- derived from baseclasses found in cg.h
//////////////////////////////////////////////////////////////////////

#ifndef _SHADER_H_
#define _SHADER_H_

class Ext;

#include "ext.hpp"


void debugShader(GLuint obj, const char *name);

extern class Ext glExt;
extern class ShaderHolder shaders;


//////////////////////////////////////
// Shader class
//////////////////////////////////////

class Shader {
public:

	Shader() {};
	~Shader() {};
	// name for debug - frag, vert
	void init(const char *name, const char *frag, const char *vert);
	
	// this does not currently work.
	void initFromFile(const char *name, char *fragFile, char *vertFile);
	
	// fetch string from file
	bool loadFromFile(char *filename, char* buffer);

	void deinit();

	const char *name;

	GLhandleARB vertex;
	GLhandleARB fragment;
	// edelliset yhdes
	GLhandleARB program;

	void bind();
	void unbind();

	// Send parameters
	bool setUniform1f(char* varname, GLfloat v0);  
	bool setUniform2f(char* varname, GLfloat v0, GLfloat v1); 
	bool setUniform3f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2); 
	bool setUniform4f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3); 
	
	bool setUniform1i(char* varname, GLint v0);
	bool setUniform2i(char* varname, GLint v0, GLint v1);
	bool setUniform3i(char* varname, GLint v0, GLint v1, GLint v2);
	bool setUniform4i(char* varname, GLint v0, GLint v1, GLint v2, GLint v3);
	
	bool setUniform1fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform2fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform3fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform4fv(char* varname, GLsizei count, GLfloat *value);
	bool setUniform1iv(char* varname, GLsizei count, GLint *value);
	bool setUniform2iv(char* varname, GLsizei count, GLint *value);
	bool setUniform3iv(char* varname, GLsizei count, GLint *value);
	bool setUniform4iv(char* varname, GLsizei count, GLint *value);
	   
	bool setUniformMatrix2fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);
	bool setUniformMatrix3fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);
	bool setUniformMatrix4fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value);
	
	// Receive Uniform variables:
	void GetUniformfv(char* name, GLfloat* values);
	void GetUniformiv(char* name, GLint* values); 
	
	// Vertex Attributes
	bool setVertexAttrib1f(char* varname, GLfloat v0);
	bool setVertexAttrib2f(char* varname, GLfloat v0, GLfloat v1);
	bool setVertexAttrib3f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2);
	bool setVertexAttrib4f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);	

protected:
	GLint GetUniLoc(const GLcharARB *name);        
};


//////////////////////////////////////
// Holder for shaders
//////////////////////////////////////

class ShaderHolder
{
public:
	ShaderHolder() 
	{ 
		init_ok = false;
	};
	~ShaderHolder() {};
	
	void init(); 
	void deinit();
	
    Shader *kristalli;
    Shader *cubereflect;

	Shader	*kappale;
	Shader	*g ;

	Shader *kitaratunneli;

	Shader *synkka;
	Shader *synkkatausta;

	Shader *lightray;

	// Lattia
	Shader *floor1;

	Shader *waterReflect;
	Shader *waterReflect2;
 	
	// shadow mapping
	Shader *shadowMap;
	Shader *shadowMapTex;
	Shader *shadowBlur;

	// chrome
	Shader *chrome;
	Shader *sindistort;
	Shader *color;

	// blur stuff
	Shader	*blurx;
	Shader	*blury;
	Shader	*blur2x;
	Shader	*blur2y;
	
	// glow stuff
	Shader	*darken;
	Shader	*glowc;

	// edge detection stuff
	Shader	*edge;

    // displacement
    Shader  *displace;
    Shader    *sivuttaintausta;

    //invert
    Shader  *invert;

	Shader	*blackwhite;
	Shader	*gradientfade;

	Shader  *dof;

	// lighting
	Shader  *lightdir;
	Shader  *lightpoint;
	Shader  *lightambientpoint;

	Shader *jytky;
	
	// light + grad fader
	Shader *lightfade;

	// envmap reflection
	Shader *envrefl;

	// vapauta frag/vert-ohjelma
	void unbind();

protected:
	bool init_ok;
};


#endif