#include "postproc.hpp"

#define ENABLE_POSTPROC

void PostProc::init(bool clear) {
	glExt.bindTextureFBO1024(glExt.glowTexture1024ID);
	
	if(clear) 
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
}

void PostProc::glow(int blur_steps, float blur_step_x, float blur_step_y, float blur_brightness, float darken_alpha, float glow_amount, int disable_dir) 
{

	// Rale 10.7.2006
   	glExt.unbindFBO();

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

	// Tarkastetaan että haluttiin darkensheideri käyttöön
	if(darken_alpha>=0) {
		
		//shaders.darken->setUniform1f("alpha", darken_alpha);  
		shaders.darken->bind();
		glActiveTextureARB(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture1024ID);
		shaders.darken->setUniform1i("tex", 0);  
		shaders.darken->setUniform1f("alpha", darken_alpha);  

	} else shaders.unbind();

	// Piirretään alkuperäinen kuva tummennettuna pikkubufferiin
	glExt.bindTextureFBO512(glExt.glowTexture512ID);

		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture1024ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	 
	glExt.unbindFBO();

	
	if(darken_alpha>=0) {
		shaders.unbind();
	}

	// Rendertargettia pienemmäksi

	glExt.bindTextureFBO256(glExt.glowTexture256ID);
			
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	glExt.bindTextureFBO128(glExt.glowTexture128ID);
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture256ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();


	// Seuraavaksi blurrataan pikkubufferikuvaa
	for(int i=0; i<blur_steps; i++) {

		if(disable_dir!=2)
		{
			shaders.blurx->bind();
			shaders.blurx->setUniform1i("tex", 0);  
			shaders.blurx->setUniform1f("xoff", blur_step_x);
			shaders.blurx->setUniform1f("alpha", blur_brightness);
		}

			glExt.bindTextureFBO128(glExt.glowTexture128ID2);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		if(disable_dir!=2)
		{
			shaders.blurx->unbind();
		}

		if(disable_dir!=1)
		{
			shaders.blury->bind();
			shaders.blury->setUniform1i("tex", 0);  
			shaders.blury->setUniform1f("yoff", blur_step_y);
			shaders.blury->setUniform1f("alpha", blur_brightness);
		}


			glExt.bindTextureFBO128(glExt.glowTexture128ID);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID2);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();
		
		if(disable_dir!=1)
		{
			shaders.blury->unbind();
		}
	}

	/**/

	// blendi päälle - että alphakanavat futaa
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE,GL_ONE);
	glColor4f(1,1,1,1); 

	// Piirretään alkuperäinen ja blurrattu yhdessä 

	shaders.glowc->bind();		

		shaders.glowc->setUniform1f("glow_amount", glow_amount);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.glowTexture1024ID);
		shaders.glowc->setUniform1i("texunit0", 0);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.glowTexture128ID);
		shaders.glowc->setUniform1i("texunit1", 1);

				 glBegin(GL_QUADS);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
					glVertex2i(0, 0);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
					glVertex2i(screensizex, 0);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
					glVertex2i(screensizex, screensizey);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
					glVertex2i(0, screensizey);
				 glEnd();   

		glActiveTextureARB(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);
		

	glActiveTextureARB(GL_TEXTURE0);
	shaders.unbind();


  
	/**/

	glEnable(GL_TEXTURE_2D);

	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);


	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();

}

void PostProc::blur(int blur_steps, float blur_step_x, float blur_step_y) {

   	
	glExt.unbindFBO();

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

	glExt.bindTextureFBO512(glExt.glowTexture512ID);

		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture1024ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	 
	glExt.unbindFBO();

	glExt.bindTextureFBO256(glExt.glowTexture256ID);
			
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	glExt.bindTextureFBO128(glExt.glowTexture128ID);
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture256ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	// Seuraavaksi blurrataan pikkubufferikuvaa
	for(int i=0; i<blur_steps; i++) {

		shaders.blur2x->bind();
		shaders.blur2x->setUniform1i("tex", 0);  
		shaders.blur2x->setUniform1f("xoff", blur_step_x);
		shaders.blur2x->setUniform1f("alpha", 1);

			glExt.bindTextureFBO128(glExt.glowTexture128ID2);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2x->unbind();

		shaders.blur2y->bind();
		shaders.blur2y->setUniform1i("tex", 0);  
		shaders.blur2y->setUniform1f("yoff", blur_step_y);
		shaders.blur2y->setUniform1f("alpha", 1);


			glExt.bindTextureFBO128(glExt.glowTexture128ID);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID2);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2y->unbind();
	}

	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE,GL_ONE);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glColor4f(1,1,1,1); 

		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	/**/

	glEnable(GL_TEXTURE_2D);

	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);


	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();

}

// idea from - http://pages.cpsc.ucalgary.ca/~parker/501/edgedetect.pdf
void PostProc::edge(int blur_steps, float blur_step_x, float blur_step_y, float blur_alpha) {


	glExt.unbindFBO();

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

	glExt.bindTextureFBO512(glExt.glowTexture512ID);

		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture1024ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	 
	glExt.unbindFBO();

	// Seuraavaksi blurrataan pikkubufferikuvaa
	for(int i=0; i<blur_steps; i++) {

		shaders.blur2x->bind();
		shaders.blur2x->setUniform1i("tex", 0);  
		shaders.blur2x->setUniform1f("xoff", blur_step_x);
		shaders.blur2x->setUniform1f("alpha", blur_alpha);

			glExt.bindTextureFBO512(glExt.glowTexture512ID2);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2x->unbind();

		shaders.blur2y->bind();
		shaders.blur2y->setUniform1i("tex", 0);  
		shaders.blur2y->setUniform1f("yoff", blur_step_y);
		shaders.blur2y->setUniform1f("alpha", blur_alpha);


			glExt.bindTextureFBO512(glExt.glowTexture512ID);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID2);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2y->unbind();
	}

	/***/ 

	// nyt meillä on blurrattu kuva - vetästään edgefiltteri
	shaders.edge->bind();
	shaders.edge->setUniform1i("tex", 0);  

		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();


	shaders.edge->unbind();

	/**/

	glEnable(GL_TEXTURE_2D);

	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);


	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();

}

void PostProc::drawOverlay(GLuint &texid) {

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	 
	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();

  
}



void PostProc::initMotionBlur(int frames_delay)
{
	glExt.bindTextureFBO1024(glExt.motionBlur1024);

	float alpha = 1.0f / float(frames_delay);
	glDepthFunc(0);
		
		glPushMatrix();
			dmsPerspective2D(1,1);
			glLoadIdentity();
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glDisable(GL_DEPTH_TEST);
			glDisable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
				
				glColor4f(0.0f, 0.0f, 0.0f, alpha); // ALPHA säätää blurrin määrää 0.5f käytännössä minimi
				glBegin(GL_QUADS);
					glVertex2f(0.0f, 0.0f);
					glVertex2f(1.0f, 0.0f);
					glVertex2f(1.0f, 1.0f);
					glVertex2f(0.0f, 1.0f);			
				glEnd();

			dmsPerspective3D();
			glLoadIdentity();
		glPopMatrix();
	
		glDisable(GL_BLEND);
	
	glDepthFunc(1);
	glColor3f(1,1,1);
}

void PostProc::motionBlur()
{
	glExt.unbindFBO();

	glDepthFunc(0);
	glPushMatrix();

		glColor3f(1,1,1);	
		// PIIRRÄ KUVA
		dmsPerspective2D(1, 1);
		glLoadIdentity();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glDisable(GL_DEPTH_TEST);

		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, glExt.motionBlur1024);
			glBegin(GL_QUADS);
			glTexCoord2i(0, 0);
			glVertex2i(0, 0);
			glTexCoord2i(1, 0);
			glVertex2i(1, 0);
			glTexCoord2i(1, 1);
			glVertex2i(1, 1);
			glTexCoord2i(0, 1);
			glVertex2i(0, 1);
			glEnd();
		dmsPerspective3D();	
		glLoadIdentity();

	glPopMatrix();
	glDepthFunc(1);

	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glEnable(GL_BLEND);

	glDisable(GL_TEXTURE_2D);
//	glEnable(GL_BLEND);
//	glEnable(GL_DEPTH_TEST);
}



void PostProc::initDOF(bool clear) 
{
	glExt.bindDepthFBO();
	
	if(clear) glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);		
}

void PostProc::dof(float nearDist, float focusDist, float farDist, int blur_steps, float blur_step_x, float blur_step_y, float blur_alpha)
{
	// Rale 12.1.2007
   	glExt.unbindFBO();

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);
	glExt.bindTextureFBO512(glExt.glowTexture512ID);
			
		glBindTexture(GL_TEXTURE_2D, glExt.depthColTex);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	glExt.bindTextureFBO256(glExt.glowTexture256ID);
			
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture512ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	glExt.bindTextureFBO128(glExt.glowTexture128ID);
		glBindTexture(GL_TEXTURE_2D, glExt.glowTexture256ID);
			glBegin(GL_QUADS);
				glTexCoord2i(0, 0);
				glVertex2i(0, 0);
				glTexCoord2i(1, 0);
				glVertex2i(screensizex, 0);
				glTexCoord2i(1, 1);
				glVertex2i(screensizex, screensizey);
				glTexCoord2i(0, 1);
				glVertex2i(0, screensizey);			
			glEnd();
	glExt.unbindFBO();

	// Seuraavaksi blurrataan pikkubufferikuvaa
	for(int i=0; i<blur_steps; i++) {

		shaders.blur2x->bind();
		shaders.blur2x->setUniform1i("tex", 0);  
		shaders.blur2x->setUniform1f("xoff", blur_step_x);
		shaders.blur2x->setUniform1f("alpha", blur_alpha);// blur_brightness

			glExt.bindTextureFBO128(glExt.glowTexture128ID2);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2x->unbind();

		shaders.blur2y->bind();
		shaders.blur2y->setUniform1i("tex", 0);  
		shaders.blur2y->setUniform1f("yoff", blur_step_y);
		shaders.blur2y->setUniform1f("alpha", blur_alpha); //blur_brightness


			glExt.bindTextureFBO128(glExt.glowTexture128ID);
				glBindTexture(GL_TEXTURE_2D, glExt.glowTexture128ID2);
					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   
			glExt.unbindFBO();

		shaders.blur2y->unbind();
	}

	// nyt glowTexture128ID:ssä on blurrattu kuva
	// sheidereillä pitää yhdistää 

	// blendi päälle - että alphakanavat futaa
	glEnable(GL_BLEND);
	//glDisable(GL_BLEND);
	//glBlendFunc(,GL_ONE_);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1,1,1,1); 

	// Piirretään alkuperäinen ja blurrattu yhdessä 

	shaders.dof->bind();		

		shaders.dof->setUniform1f("near",  nearDist);
		shaders.dof->setUniform1f("focus", focusDist);
		shaders.dof->setUniform1f("far",   farDist);

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.depthColTex);
		shaders.dof->setUniform1i("texunit0", 0);

		glActiveTextureARB(GL_TEXTURE1_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.glowTexture128ID);
		shaders.dof->setUniform1i("texunit1", 1);

		glActiveTextureARB(GL_TEXTURE2_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.depthTex);
		shaders.dof->setUniform1i("texunit2", 2);

				 glBegin(GL_QUADS);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 0);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 0);
					glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0, 0);
					glVertex2i(0, 0);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 0);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 0);
					glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 1, 0);
					glVertex2i(screensizex, 0);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 1, 1);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 1, 1);
					glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 1, 1);
					glVertex2i(screensizex, screensizey);
					glMultiTexCoord2fARB(GL_TEXTURE0_ARB, 0, 1);
					glMultiTexCoord2fARB(GL_TEXTURE1_ARB, 0, 1);
					glMultiTexCoord2fARB(GL_TEXTURE2_ARB, 0, 1);
					glVertex2i(0, screensizey);
				 glEnd();   

		shaders.unbind();

			glActiveTextureARB(GL_TEXTURE2);
			glDisable(GL_TEXTURE_2D);

		glActiveTextureARB(GL_TEXTURE1);
		glDisable(GL_TEXTURE_2D);
		

	glActiveTextureARB(GL_TEXTURE0);
	shaders.unbind();


  
	/**/	

	glEnable(GL_TEXTURE_2D);

	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);

	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();
}


void PostProc::coloradjust(float saturate, float brightness, float contrast)
{   	
	glExt.unbindFBO();

	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();;
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

		glUseProgramObjectARB(shaders.color->program);
		glUniform1fARB(glGetUniformLocationARB(shaders.color->program, "saturate"), saturate);  
		glUniform1fARB(glGetUniformLocationARB(shaders.color->program, "contrast"), contrast);  
		glUniform1fARB(glGetUniformLocationARB(shaders.color->program, "brightness"), brightness);  


		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.glowTexture1024ID);
		glUniform1i(glGetUniformLocationARB(shaders.color->program, "tex"), 0);


					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   

		glActiveTextureARB(GL_TEXTURE0);
		glUseProgramObjectARB(0);



	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);

	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();
}

void PostProc::sindistortion(float xfreq, float yfreq, float xphase, float yphase, float xamp, float yamp)
{   	
	glExt.unbindFBO();

#ifdef _FILTER_CHAIN
	glExt.bindTextureFBO1024(glExt.motionBlur1024);
#endif


	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

		glUseProgramObjectARB(shaders.sindistort->program);
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "xfreq"), xfreq);  
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "yfreq"), yfreq);  
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "xphase"), xphase);  
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "yphase"), yphase);
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "xamp"), xamp);  
		glUniform1fARB(glGetUniformLocationARB(shaders.sindistort->program, "yamp"), yamp);  


		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D,glExt.glowTexture1024ID);
		glUniform1i(glGetUniformLocationARB(shaders.sindistort->program, "tex"), 0);


					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   

		glActiveTextureARB(GL_TEXTURE0);
		glUseProgramObjectARB(0);



	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);

	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();
}

void PostProc::applychrome(int chrome_times)
{
	glExt.unbindFBO();


	// Haetaan ruudun koko
	int screensizex = dmsGetWindowWidth();
    int screensizey = dmsGetWindowHeight();
	dmsPerspective2D(screensizex, screensizey);
	glLoadIdentity();

	// Poistetaan syvyystestaus ja blendaus käytöstä
	glDisable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glDepthFunc(0);
	
	glEnable(GL_TEXTURE_2D);

	glColor4f(1,1,1,1);

		glUseProgramObjectARB(shaders.chrome->program);
		glUniform1i(glGetUniformLocationARB(shaders.chrome->program, "times"), chrome_times);  

		glActiveTextureARB(GL_TEXTURE0_ARB);
		glEnable(GL_TEXTURE_2D);


	glBindTexture(GL_TEXTURE_2D,glExt.glowTexture1024ID);
		
	
		glUniform1i(glGetUniformLocationARB(shaders.chrome->program, "tex"), 0);


					 glBegin(GL_QUADS);
						glTexCoord2i(0, 0);
						glVertex2i(0, 0);
						glTexCoord2i(1, 0);
						glVertex2i(screensizex, 0);
						glTexCoord2i(1, 1);
						glVertex2i(screensizex, screensizey);
						glTexCoord2i(0, 1);
						glVertex2i(0, screensizey);
					 glEnd();   

		glActiveTextureARB(GL_TEXTURE0);
		glUseProgramObjectARB(0);

	// Syvyystestaus taas päälle
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(1);

	// Takaisin 3d moodiin 
	dmsPerspective3D();
	glLoadIdentity();
}
