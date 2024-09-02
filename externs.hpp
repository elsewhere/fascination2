#ifndef _EXTERNS_HPP_
#define _EXTERNS_HPP_




//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include <windows.h>

#include "DemoTractor/opengl.hpp"
#include "DemoTractor/font.hpp"
#include "DemoTractor/texturemanager.hpp"
#include "DemoTractor/objectmanager.hpp"
#include "DemoTractor/effectmanager.hpp"
#include "DemoTractor/beziercurve.hpp"
#include "DemoTractor/hermitecurve.hpp"
#include "DemoTractor/path.hpp"
#include "DemoTractor/t3d.hpp"
#include "DemoTractor/spline.hpp"

#include "ext.hpp"
#define DMS_TEXTURE 0x01



//--------------------------------------------------------------------------------------------
//  Link needed libraries
//--------------------------------------------------------------------------------------------

#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "DemoTractor/release/demotractor.lib")
#pragma comment(lib, "DemoTractor/lib/opengl32.lib")
#pragma comment(lib, "DemoTractor/lib/glu32.lib")
//#pragma comment(lib, "DemoTractor/winmm.lib")
//#pragma comment(lib, "DemoTractor/fmodvc.lib")
//#pragma comment(lib, "DemoTractor/libpng.lib")
//#pragma comment(lib, "DemoTractor/libz.lib")

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

#include "mathematics.hpp"
#include "ext.hpp"
#include "lista2.hpp"
#include "postproc.hpp"
#include "bpm.hpp"
#include "trigger.hpp"
#include "shader.hpp"
#include "catmullrom.hpp"
#include "bezier.hpp"
#include "camera.hpp"
#include "mesh.hpp"
#include "meshfactory.hpp"
#include "frametimer.hpp"
#include "frustumculler.hpp"
#include "cubemap.hpp"
#include "writer.hpp"

extern Vector3 getKasariColor();

extern Vector3 clearcol;

////////////////////////////////
// Global extension functions
////////////////////////////////
// to help tigital with the porting ;)


extern PFNGLGENBUFFERSARBPROC glGenBuffersARB;					// VBO Name Generation Procedure
extern PFNGLBINDBUFFERARBPROC glBindBufferARB;					// VBO Bind Procedure
extern PFNGLBUFFERDATAARBPROC glBufferDataARB;					// VBO Data Loading Procedure
extern PFNGLDELETEBUFFERSARBPROC glDeleteBuffersARB;				// VBO Deletion Procedure


extern PFNGLMULTITEXCOORD2FARBPROC 					glMultiTexCoord2fARB;
extern PFNGLACTIVETEXTUREARBPROC 						glActiveTextureARB;
extern PFNGLPOINTPARAMETERFARBPROC 					glPointParameterfARB;
extern PFNGLPOINTPARAMETERFVARBPROC 					glPointParameterfvARB;
extern PFNGLISRENDERBUFFEREXTPROC 						glIsRenderbufferEXT;
extern PFNGLBINDRENDERBUFFEREXTPROC 					glBindRenderbufferEXT;
extern PFNGLDELETERENDERBUFFERSEXTPROC 				glDeleteRenderbuffersEXT;
extern PFNGLGENRENDERBUFFERSEXTPROC 					glGenRenderbuffersEXT;
extern PFNGLRENDERBUFFERSTORAGEEXTPROC 				glRenderbufferStorageEXT;
extern PFNGLGETRENDERBUFFERPARAMETERIVEXTPROC 			glGetRenderbufferParameterivEXT;
extern PFNGLISFRAMEBUFFEREXTPROC 						glIsFramebufferEXT;
extern PFNGLBINDFRAMEBUFFEREXTPROC 					glBindFramebufferEXT;
extern PFNGLDELETEFRAMEBUFFERSEXTPROC 					glDeleteFramebuffersEXT;
extern PFNGLGENFRAMEBUFFERSEXTPROC 					glGenFramebuffersEXT;
extern PFNGLCHECKFRAMEBUFFERSTATUSEXTPROC				glCheckFramebufferStatusEXT;
extern PFNGLFRAMEBUFFERTEXTURE1DEXTPROC				glFramebufferTexture1DEXT;
extern PFNGLFRAMEBUFFERTEXTURE2DEXTPROC				glFramebufferTexture2DEXT;
extern PFNGLFRAMEBUFFERTEXTURE3DEXTPROC				glFramebufferTexture3DEXT;
extern PFNGLFRAMEBUFFERRENDERBUFFEREXTPROC				glFramebufferRenderbufferEXT;
extern PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVEXTPROC glGetFramebufferAttachmentParameterivEXT;
extern PFNGLGENERATEMIPMAPEXTPROC						glGenerateMipmapEXT;
extern PFNGLGETUNIFORMFVPROC				glGetUniformfvARB;
extern PFNGLGETUNIFORMIVPROC				glGetUniformivARB;
extern PFNGLCREATEPROGRAMOBJECTARBPROC		glCreateProgramObjectARB;
extern PFNGLDELETEOBJECTARBPROC			glDeleteObjectARB;
extern PFNGLCREATESHADEROBJECTARBPROC		glCreateShaderObjectARB;
extern PFNGLSHADERSOURCEARBPROC			glShaderSourceARB;
extern PFNGLCOMPILESHADERARBPROC			glCompileShaderARB;
extern PFNGLGETOBJECTPARAMETERIVARBPROC	glGetObjectParameterivARB;
extern PFNGLATTACHOBJECTARBPROC			glAttachObjectARB;
extern PFNGLGETINFOLOGARBPROC				glGetInfoLogARB;
extern PFNGLLINKPROGRAMARBPROC				glLinkProgramARB;
extern PFNGLUSEPROGRAMOBJECTARBPROC		glUseProgramObjectARB;
extern PFNGLGETUNIFORMLOCATIONARBPROC		glGetUniformLocationARB;
extern PFNGLDELETEPROGRAMPROC				glDeleteProgram;
extern PFNGLDELETESHADERPROC				glDeleteShader;
extern PFNGLISPROGRAMPROC					glIsProgram;
extern PFNGLISSHADERPROC					glIsShader;
extern PFNGLGETPROGRAMINFOLOGPROC			glGetProgramInfoLog;
extern PFNGLGETSHADERINFOLOGPROC			glGetShaderInfoLog;
extern PFNGLUNIFORM4FARBPROC			glUniform4fARB;
extern PFNGLUNIFORM3FARBPROC			glUniform3fARB;         
extern PFNGLUNIFORM2FPROC				glUniform2fARB;
extern PFNGLUNIFORM1FARBPROC			glUniform1fARB;
extern PFNGLUNIFORM1IARBPROC			glUniform1iARB;
extern PFNGLUNIFORM1IPROC				glUniform1i;
extern PFNGLUNIFORM2IPROC				glUniform2i;
extern PFNGLUNIFORM3IPROC				glUniform3i;
extern PFNGLUNIFORM4IPROC				glUniform4i;
extern PFNGLUNIFORM1FVPROC				glUniform1fv;
extern PFNGLUNIFORM2FVPROC				glUniform2fv;
extern PFNGLUNIFORM3FVPROC				glUniform3fv;
extern PFNGLUNIFORM4FVPROC				glUniform4fv;
extern PFNGLUNIFORM1IVPROC				glUniform1iv;
extern PFNGLUNIFORM2IVPROC				glUniform2iv;
extern PFNGLUNIFORM3IVPROC				glUniform3iv;
extern PFNGLUNIFORM4IVPROC				glUniform4iv;
extern PFNGLUNIFORMMATRIX2FVPROC		glUniformMatrix2fv;
extern PFNGLUNIFORMMATRIX3FVPROC		glUniformMatrix3fv;
extern PFNGLUNIFORMMATRIX4FVPROC		glUniformMatrix4fv;
extern PFNGLVALIDATEPROGRAMPROC		glValidateProgram;
extern PFNGLVERTEXATTRIB1DPROC			glVertexAttrib1d;
extern PFNGLVERTEXATTRIB1DVPROC		glVertexAttrib1dv;
extern PFNGLVERTEXATTRIB1FPROC			glVertexAttrib1f;
extern PFNGLVERTEXATTRIB1FVPROC		glVertexAttrib1fv;
extern PFNGLVERTEXATTRIB1SPROC			glVertexAttrib1s;
extern PFNGLVERTEXATTRIB1SVPROC		glVertexAttrib1sv;
extern PFNGLVERTEXATTRIB2DPROC			glVertexAttrib2d;
extern PFNGLVERTEXATTRIB2DVPROC		glVertexAttrib2dv;
extern PFNGLVERTEXATTRIB2FPROC			glVertexAttrib2f;
extern PFNGLVERTEXATTRIB2FVPROC		glVertexAttrib2fv;
extern PFNGLVERTEXATTRIB2SPROC			glVertexAttrib2s;
extern PFNGLVERTEXATTRIB2SVPROC		glVertexAttrib2sv;
extern PFNGLVERTEXATTRIB3DPROC			glVertexAttrib3d;
extern PFNGLVERTEXATTRIB3DVPROC		glVertexAttrib3dv;
extern PFNGLVERTEXATTRIB3FPROC			glVertexAttrib3f;
extern PFNGLVERTEXATTRIB3FVPROC		glVertexAttrib3fv;
extern PFNGLVERTEXATTRIB3SPROC			glVertexAttrib3s;
extern PFNGLVERTEXATTRIB3SVPROC		glVertexAttrib3sv;
extern PFNGLVERTEXATTRIB4NBVPROC		glVertexAttrib4Nbv;
extern PFNGLVERTEXATTRIB4NIVPROC		glVertexAttrib4Niv;
extern PFNGLVERTEXATTRIB4NSVPROC		glVertexAttrib4Nsv;
extern PFNGLVERTEXATTRIB4NUBPROC		glVertexAttrib4Nub;
extern PFNGLVERTEXATTRIB4NUBVPROC		glVertexAttrib4Nubv;
extern PFNGLVERTEXATTRIB4NUIVPROC		glVertexAttrib4Nuiv;
extern PFNGLVERTEXATTRIB4NUSVPROC		glVertexAttrib4Nusv;
extern PFNGLVERTEXATTRIB4BVPROC		glVertexAttrib4bv;
extern PFNGLVERTEXATTRIB4DPROC			glVertexAttrib4d;
extern PFNGLVERTEXATTRIB4DVPROC		glVertexAttrib4dv;
extern PFNGLVERTEXATTRIB4FPROC			glVertexAttrib4f;
extern PFNGLVERTEXATTRIB4FVPROC		glVertexAttrib4fv;
extern PFNGLVERTEXATTRIB4IVPROC		glVertexAttrib4iv;
extern PFNGLVERTEXATTRIB4SPROC			glVertexAttrib4s;
extern PFNGLVERTEXATTRIB4SVPROC		glVertexAttrib4sv;
extern PFNGLVERTEXATTRIB4UBVPROC		glVertexAttrib4ubv;
extern PFNGLVERTEXATTRIB4UIVPROC		glVertexAttrib4uiv;
extern PFNGLVERTEXATTRIB4USVPROC		glVertexAttrib4us;
extern PFNGLVERTEXATTRIBPOINTERPROC	glVertexAttribPointer;


#endif
