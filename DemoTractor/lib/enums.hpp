#ifndef _ENUMS_HPP_
#define _ENUMS_HPP_

//--------------------------------------------------------------------------------------------
//  This code belongs to our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

namespace TRACTION_DEMOTRACTOR
{

	// "special case"-koodi
	#ifndef DUMMY
		#define DUMMY -1
	#endif

	enum myGLEnumerators
	{
		MY_BLEND = 0,
		MY_TEXTURE_1D = 1,
		MY_TEXTURE_2D = 2,
		MY_DEPTH_TEST = 3,
		MY_LIGHTING = 4,
		MY_LIGHT0 = 5,
		MY_LIGHT1 = 6,
		MY_LIGHT2 = 7,
		MY_LIGHT3 = 8,
		MY_LIGHT4 = 9,
		MY_LIGHT5 = 10,
		MY_LIGHT6 = 11,
		MY_LIGHT7 = 12,
		MY_NORMALIZE = 13,
		MY_CULL_FACE = 14,
		MY_TEXTURE_CUBE_MAP_EXT = 15,
		MY_TEXTURE_GEN_S = 16,
		MY_TEXTURE_GEN_T = 17,
		MY_TEXTURE_GEN_R = 18,
		MY_FOG = 19,
		MY_LINE_SMOOTH = 20,
		MY_POINT_SMOOTH = 21,
		MY_DEPTH_MASK = 22,
		MY_ALPHA_TEST = 23,
	};

}

#endif