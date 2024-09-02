#ifndef _POSTPROC_HPP_
#define _POSTPROC_HPP_

#include "externs.hpp"

extern class PostProc filter;

class PostProc
{
public:

	// Call this before rendering stuff that needs postprocession
	void init(bool clear=true);

    

    //

	// Call this when you want render the glow the screen [darken_alpha -1 = no darken at all] [disabledir; 0 = none, 1 = disable vertical 2 = disable horizontal]
	void glow(int blur_steps=5, float blur_step_x=0.006f, float blur_step_y=0.006f, float blur_brightness=1.0f, float darken_alpha=-1.0f, float glow_amount=1.0f, int disable_dir=0);

	// Renders blurred scene with given parameters
	void blur(int blur_steps=5, float blur_step_x=0.006f, float blur_step_y=0.006f);

	// Renders edgedetection filter
	void edge(int blur_steps=3, float blur_step_x=0.002f, float blur_step_y=0.002f, float blur_alpha=1.0f);

	// Draws overlay on top of everything
	void drawOverlay(GLuint &texid);

	// Distort image with sin function
	void applychrome(int chrome_times=5);

	// Adjust colors
	void coloradjust(float saturate=1.0f, float brightness=1.0f, float contrast=1.0f);

	// Displace horizontally
	void displacement(int displace_texture_id, float displace_amount=0.5f, float alpha=1.0f);

	// Distort image with sin function
	void sindistortion(float xfreq=100, float yfreq=100, float xphase=0.0f, float yphase=0.0f, float xamp=0.01f, float yamp=0.01f);

	// Motionblur
	void initMotionBlur(int frames_delay=60);
	void motionBlur();

	// Call this before rendering stuff that needs DOF post procession
	void initDOF(bool clear=true);

	// near & far = edge of full blur, focus = no blur
	void dof(float nearDist=0.980f, float focusDist=0.9850f, float farDist=1.0f, 
		int blur_steps=2, float blur_step_x=0.0001f, float blur_step_y=0.0001f, float blur_alpha=1.0f);


protected:
};


#endif