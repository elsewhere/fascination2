//////////////////////////////////////////////////////////////////////
// shader.h: place your shader classes here
//////////////////////////////////////////////////////////////////////

#include "shader.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

//////////////////////////////////////////////
// ShaderHolder class 
//////////////////////////////////////////////

void ShaderHolder::init() {

		
			static const char *emptyVertex = {
					"varying vec2 Tex_coord;"\
					"void main(void) "\
					"{"\
					"   gl_Position = ftransform();"\
					"   gl_TexCoord[0] = gl_MultiTexCoord0;"\
					"}"	
			};

			// *** BlurX

			static const char *blurxVertex = {
					"varying vec2 pos0;"\
					"varying vec2 pos1;"\
					"varying vec2 pos2;"\
					"varying vec2 pos3;"\
					"varying vec2 pos4;"\
					"uniform float xoff;"\
					"void main(void) "\
					"{"\
					"   vec2 DX = vec2(xoff,0.0);"\
					"   vec2 DX2 = vec2(2.0*xoff,0.0);"\
		            "   pos0 = gl_MultiTexCoord0.st-DX2;"\
					"   pos1 = gl_MultiTexCoord0.st-DX;"\
					"   pos2 = gl_MultiTexCoord0.st;"\
					"   pos3 = gl_MultiTexCoord0.st+DX;"\
					"   pos4 = gl_MultiTexCoord0.st+DX2;"\
					"   gl_Position = ftransform();"\
					"}"	
			};

			// *** BlurY

			static const char *bluryVertex = {
					"varying vec2 pos0;"\
					"varying vec2 pos1;"\
					"varying vec2 pos2;"\
					"varying vec2 pos3;"\
					"varying vec2 pos4;"\
					"uniform float yoff;"\
					"void main(void) "\
					"{"\
					"   vec2 DX = vec2(0.0, yoff);"\
					"   vec2 DX2 = vec2(0.0, 2.0*yoff);"\
		            "   pos0 = gl_MultiTexCoord0.st-DX2;"\
					"   pos1 = gl_MultiTexCoord0.st-DX;"\
					"   pos2 = gl_MultiTexCoord0.st;"\
					"   pos3 = gl_MultiTexCoord0.st+DX;"\
					"   pos4 = gl_MultiTexCoord0.st+DX2;"\
					"   gl_Position = ftransform();"\
					"}"	
			};

			// *** BlurFragment

			static const char *blurFragment = {
              "uniform sampler2D tex;"\
			  "varying vec2 pos0;"\
			  "varying vec2 pos1;"\
			  "varying vec2 pos2;"\
			  "varying vec2 pos3;"\
			  "varying vec2 pos4;"\
              "uniform float alpha;"\
              "void main()"\
              "{"\

              "   vec4 col = vec4(0,0,0,0);"\
              "   col+=texture2D(tex, pos0)*0.1;"\
              "   col+=texture2D(tex, pos1)*0.25;"\
              "   col+=texture2D(tex, pos2)*0.5;"\
              "   col+=texture2D(tex, pos3)*0.25;"\
              "   col+=texture2D(tex, pos4)*0.1;"\
              "   gl_FragColor = col*alpha;"\
              "}"
			};

			static const char *blur2Fragment = {
              "uniform sampler2D tex;"\
			  "varying vec2 pos0;"\
			  "varying vec2 pos1;"\
			  "varying vec2 pos2;"\
			  "varying vec2 pos3;"\
			  "varying vec2 pos4;"\
              "uniform float alpha;"\
              "void main()"\
              "{"\
              "   vec4 col = vec4(0,0,0,0);"\
              "   col+=texture2D(tex, pos0)*0.1;"\
              "   col+=texture2D(tex, pos1)*0.2;"\
              "   col+=texture2D(tex, pos2)*0.4;"\
              "   col+=texture2D(tex, pos3)*0.2;"\
              "   col+=texture2D(tex, pos4)*0.1;"\
              "   gl_FragColor = vec4(col.rgb, 1)*alpha;"\
              "}"
			};

			// *** glow combine

			static const char *glowcVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   gl_Position = ftransform();"\
				"}"
			};


			static const char *glowcFragment = {
				"uniform sampler2D texunit0;"\
				"uniform sampler2D texunit1;"\
				"uniform float glow_amount;"\
				"varying vec2 coord;"\
				"void main()"\
				"{"\
				"	vec4 norm = texture2D(texunit0, coord);"\
				"	vec4 glow = texture2D(texunit1, coord)*glow_amount;"\
				"	gl_FragColor = norm+glow;"\
				"}"
			};

            // *** kristalli


			static const char *kristalliVertex= {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
                "uniform float liuku;"\

				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   coord2 = coord + gl_MultiTexCoord1.xy * liuku;"\
				"   gl_Position = ftransform();"\
				"}"
			};

            static const char *kristalliFragment = {
                "uniform sampler2D texunit0;"\
                "uniform sampler2D texunit1;"\
                "uniform float alpha;"\
                "varying vec2 coord;"\
                "varying vec2 coord2;"\
                "void main()"\
                "{"\
                "   vec4 col = texture2D(texunit0, coord);"\
                "   vec4 col2 = texture2D(texunit1, coord2);"\
                "   col = col * 0.2 + col2 * 0.8;"\
                "   col *= alpha; "\
                "   gl_FragColor = col;"\
                "}"
            };



            // *** displacement

			static const char *displaceVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   coord2 = gl_MultiTexCoord1.xy;"\
				"   gl_Position = ftransform();"\
				"}"
			};

            static const char *displaceFragment = {
                "uniform sampler2D texunit0;"\
                "uniform sampler2D texunit1;"\
                "uniform float displace_amount;"\
                "uniform float alpha;"\
                "varying vec2 coord;"\
                "varying vec2 coord2;"\
                "void main()"\
                "{"\
                "   vec2 offs = texture2D(texunit1, coord2).xy;"\
                "   vec4 col = texture2D(texunit0, coord+offs*displace_amount);"\
                "   col *= alpha; "\
                "   gl_FragColor = col;"\
                "}"
            };

            // *** displacement

			static const char *synkkataustaVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   coord2 = gl_MultiTexCoord1.xy;"\
				"   gl_Position = ftransform();"\
				"}"
			};

            static const char *synkkataustaFragment = {
                "uniform sampler2D texunit0;"\
                "uniform sampler2D texunit1;"\
                "uniform float displace_amountx;"\
				"uniform float displace_amounty;"\
                "uniform float alpha;"\
                "varying vec2 coord;"\
                "varying vec2 coord2;"\
                "void main()"\
                "{"\
                "   vec2 offs = (texture2D(texunit1, coord2).xy) * vec2(displace_amountx, displace_amounty);"\
                "   vec4 col = texture2D(texunit0, coord+offs);"\
                "   col *= alpha; "\
                "   gl_FragColor = col;"\
                "}"
            };

            // *** sivuttaintausta

			static const char *sivuttaintaustaVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
                "varying vec2 coord3;"\
				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   coord2 = gl_MultiTexCoord1.xy;"\
				"   coord3 = gl_MultiTexCoord2.xy;"\
				"   gl_Position = ftransform();"\
				"}"
			};

            static const char *sivuttaintaustaFragment = {
                "uniform sampler2D texunit0;"\
                "uniform sampler2D texunit1;"\
                "uniform sampler2D texunit2;"\
                "uniform float displace_amount;"\
                "uniform float alpha;"\
                "uniform float fadepaske;"\
				"varying vec2 coord;"\
                "varying vec2 coord2;"\
                "varying vec2 coord3;"\
                "void main()"\
                "{"\
                "   vec2 offs = texture2D(texunit1, coord2).xy;"\
                "   vec4 col = texture2D(texunit0, coord+sin(offs)*displace_amount);"\
                "   vec4 valo = texture2D(texunit2, coord3);"\
                "   col *= alpha; "\
                "   col *= valo;"\
                "   col.x *= 5.0;"\
                "   col.y *= 5.0;"\
                "   col.z *= 5.0;"\
                "   gl_FragColor = col*fadepaske;"\
                "}"
            };

            // *** invert

			static const char *invertVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   gl_Position = ftransform();"\
				"}"
			};

            static const char *invertFragment = {
                "uniform sampler2D texunit0;"\
                "uniform float invert_amount ;"\
                "uniform float alpha;"\
                "varying vec2 coord;"\
                "void main()"\
                "{"\
                "   vec4 col = texture2D(texunit0, coord);"\
                "   col.x = col.x * (1.0-invert_amount) + (1.0-col.x) * invert_amount; "\
                "   col.y = col.y * (1.0-invert_amount) + (1.0-col.y) * invert_amount; "\
                "   col.z = col.z * (1.0-invert_amount) + (1.0-col.z) * invert_amount; "\
                "   col *= alpha; "\
                "   gl_FragColor = col;"\
                "}"
            };


			// *** darken 

			static const char *darkenVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   gl_Position = ftransform();"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"}"
			};

			static const char *darkenFragment = {
				"uniform sampler2D tex;"\
				"uniform float alpha;"\
				"varying vec2 coord;"\
				"void main()		"\
				"{"\
				"   vec4 c = texture2D(tex, coord); "\
				"	gl_FragColor = c*c*alpha; "\
				"}"
			};

			// *** blackwhite

			static const char *bwVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   gl_Position = ftransform();"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"}"
			};

			static const char *bwFragment = {
				"uniform sampler2D tex;"\
				"uniform float threshold;"\
				"varying vec2 coord;"\
				"void main()		"\
				"{"\
				"   vec4 c = texture2D(tex, coord); "\
				"   if( (c.x+c.y+c.z)/3.0 < threshold ) "\
				"	 gl_FragColor = vec4(0,0,0,1); "\
				"	else "\
				"	 gl_FragColor = vec4(1,1,1,1); "\
				"}"
			};

			// *** edge detetion stuff

			// http://en.wikipedia.org/wiki/Sobel
			// tätä voi optata siirtämällä positiot vertexshaderille
			const char *edgeFragment = {
				"	uniform sampler2D tex;"\
				"	const float off = 1.0 / 512.0;"\
				"	void main()"\
				"	{"\
				/* naapurimatriisi */
				"	vec4 s00 = texture2D(tex, gl_TexCoord[0].xy + vec2(-off, -off));"\
				"	vec4 s01 = texture2D(tex, gl_TexCoord[0].xy + vec2( 0, -off));"\
				"	vec4 s02 = texture2D(tex, gl_TexCoord[0].xy + vec2( off, -off));"\
				"	vec4 s10 = texture2D(tex, gl_TexCoord[0].xy + vec2(-off, 0));"\
				"	vec4 s12 = texture2D(tex, gl_TexCoord[0].xy + vec2( off, 0));"\
				"	vec4 s20 = texture2D(tex, gl_TexCoord[0].xy + vec2(-off, off));"\
				"	vec4 s21 = texture2D(tex, gl_TexCoord[0].xy + vec2( 0, off));"\
				"	vec4 s22 = texture2D(tex, gl_TexCoord[0].xy + vec2( off, off));"\
				/* sobel filtteriarvoja */
				"	vec4 sobelX = s00 + 2.0 * s10 + s20 - s02 - 2.0 * s12 - s22;"\
				"	vec4 sobelY = s00 + 2.0 * s01 + s02 - s20 - 2.0 * s21 - s22;"\
				"	vec4 edgeSqr = vec4(sobelX * sobelX +  sobelY * sobelY);"\
				/* grayscale */
				"	float val = (edgeSqr.x+edgeSqr.y+edgeSqr.z)/1.0;"\
				"	gl_FragColor = vec4(val,val,val,0);"
				/* alpha ?? */
				"}"

			};

			//lighting

			static const char *lightpointFragment = {
				"varying vec4 diffuse,ambientGlobal, ambient;"\
				"varying vec3 normal,lightDir,halfVector;"\
				"varying vec4 epos;"\
				"varying float dist;"\
				"varying vec2 coord;"\
				"uniform sampler2D tex;"\
				"vec4 light0 ()"\
				" {"\
				" vec4 color;"\
				" vec3 L = normalize(gl_LightSource[0].position.xyz - epos.xyz); "\
				" vec3 E = normalize(-epos.xyz);"\
				" vec3 R = normalize(-reflect(L,normal)); "\
				" float dist = length(L);"\
				" float atten = 1.0 / (gl_LightSource[0].constantAttenuation +"\
				"               gl_LightSource[0].linearAttenuation * dist +"\
				"               gl_LightSource[0].quadraticAttenuation * dist * dist);"\
				" vec4 Iamb = gl_LightSource[0].ambient*gl_FrontMaterial.ambient;"\
				" vec4 Idiff = (gl_LightSource[0].diffuse * max(dot(normal,L), 0.0))*gl_FrontMaterial.diffuse;"\
				" vec4 Ispec = gl_FrontMaterial.specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);"\
				" "\
				" color = gl_FrontMaterial.emission+Iamb+atten*(gl_FrontMaterial.ambient + Idiff + Ispec);"\
				" return color;"\
				" }"\
				" void main (void)"\
				" {"\
				" gl_FragColor = (light0())*texture2D(tex, coord);"\
				" }"
			};
			
			static const char *lightpointVertex = {
				"varying vec4 diffuse,ambientGlobal,ambient;"\
				"varying vec3 normal,lightDir,halfVector;"\
				"varying vec4 epos;"\
				"varying float dist;"\
				"varying vec2 coord;"\
				"void main()"\
				"{   "\
				"   vec3 aux;"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   normal = normalize(gl_NormalMatrix * gl_Normal);"\
				/*"   //lightpos&dist"\*/
				"   epos = gl_ModelViewMatrix * gl_Vertex;"\
				"   aux = vec3(gl_LightSource[0].position-epos);"\
				"   lightDir = normalize(aux);"\
				"   dist = length(aux);"\
				/*"   //halfvector"\*/
				"   halfVector = normalize(gl_LightSource[0].halfVector.xyz);"\
				"   diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;"\
				"   ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;"\
				"   ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;"\
				"   gl_Position = ftransform();"\
				"}"
			};



			static const char *lightambientpointFragment = {
				"varying vec4 diffuse,ambientGlobal, ambient;"\
				"varying vec3 normal,lightDir,halfVector;"\
				"varying vec4 epos;"\
				"varying float dist;"\
				"vec4 light0 ()"\
				" {"\
				" vec4 color;"\
				" vec3 L = normalize(gl_LightSource[0].position.xyz - epos.xyz); "\
				" vec3 E = normalize(-epos.xyz);"\
				" vec3 R = normalize(-reflect(L,normal)); "\
				" float dist = length(L);"\
				" float atten = 1.0 / (gl_LightSource[0].constantAttenuation +"\
				"               gl_LightSource[0].linearAttenuation * dist +"\
				"               gl_LightSource[0].quadraticAttenuation * dist * dist);"\
				" vec4 Iamb = gl_LightSource[0].ambient*gl_FrontMaterial.ambient;"\
				" vec4 Idiff = (gl_LightSource[0].diffuse * max(dot(normal,L), 0.0))*gl_FrontMaterial.diffuse;"\
				" vec4 Ispec = gl_FrontMaterial.specular * pow(max(dot(R,E),0.0),0.3*gl_FrontMaterial.shininess);"\
				" "\
				" color = gl_FrontMaterial.emission+Iamb+atten*(gl_FrontMaterial.ambient + Idiff + Ispec);"\
				" return color;"\
				" }"\
				" void main (void)"\
				" {"\
				" gl_FragColor = (light0())*ambientGlobal;"\
				" }"
			};
			
			static const char *lightambientpointVertex = {
				"varying vec4 diffuse,ambientGlobal,ambient;"\
				"varying vec3 normal,lightDir,halfVector;"\
				"varying vec4 epos;"\
				"varying float dist;"\
				"void main()"\
				"{   "\
				"   vec3 aux;"\
				"   normal = normalize(gl_NormalMatrix * gl_Normal);"\
				/*"   //lightpos&dist"\*/
				"   epos = gl_ModelViewMatrix * gl_Vertex;"\
				"   aux = vec3(gl_LightSource[0].position-epos);"\
				"   lightDir = normalize(aux);"\
				"   dist = length(aux);"\
				/*"   //halfvector"\*/
				"   halfVector = normalize(gl_LightSource[0].halfVector.xyz);"\
				"   diffuse = gl_FrontMaterial.diffuse * gl_LightSource[0].diffuse;"\
				"   ambient = gl_FrontMaterial.ambient * gl_LightSource[0].ambient;"\
				"   ambientGlobal = gl_LightModel.ambient * gl_FrontMaterial.ambient;"\
				"   gl_Position = ftransform();"\
				"}"
			};

			// *** gradient fade from image
			// 

			
			static const char *gradientfadeVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   gl_Position = ftransform();"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"}"
			};

			static const char *gradientfadeFragment = {
				"uniform sampler2D tex;"\
				"uniform sampler2D gradient;"\
				"uniform float value;"\
				"uniform float value2;"\
				"varying vec2 coord;"\
				"void main()		"\
				"{"\
				"   vec4 actc = texture2D(tex, coord); "\
				"   vec4 gradientcolor = texture2D(gradient, coord); "\
				"   vec4 empty = vec4(1,1,1,0);"\
				"	float liuku = smoothstep(value, value2, gradientcolor.r);"\
				"	gl_FragColor = mix(actc, empty, liuku);"\
				"}"
			};
			
			/*
			static const char *gradientfadeVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"void main(void) "\
				"{"\
				"   gl_Position = ftransform();"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"   coord2 = gl_MultiTexCoord1.xy;"\
				"}"
			};

			static const char *gradientfadeFragment = {
				"uniform sampler2D tex;"\
				"uniform sampler2D gradient;"\
				"uniform float value;"\
				"uniform float value2;"\
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"void main()		"\
				"{"\
				"   float v1 = value;"\
				"   float v2 = value2;"\
				"   if(v2 < v1) v2 = v1; "\
				"   vec4 actc = texture2D(tex, coord); "\
				"   vec4 gradientcolor = texture2D(gradient, coord2); "\
				"   vec4 empty = vec4(1,1,1,0);"\
				"	float liuku = smoothstep(v1, v2, gradientcolor.r);"\
				"	gl_FragColor = mix(actc, empty, liuku);"\
				"}"
			};*/

			// *** depth of field blur 
			// 

			static const char *dofVertex = {
				"varying vec2 coord;"\
				"void main(void) "\
				"{"\
				"   gl_Position = ftransform();"\
				"   coord = gl_MultiTexCoord0.xy;"\
				"}"
			};

			static const char *dofFragment = {
				/*normal image*/
				"uniform sampler2D texunit0;"\
				/*blurred image*/
				"uniform sampler2D texunit1;"\
				/*depth values*/
				"uniform sampler2D texunit2;"\
				"uniform float near;"\
				"uniform float focus;"\
				"uniform float far;"\
				"varying vec2 coord;"\
				"void main()"\
				"{"\
				"	float f;"\
				"	float depth = texture2D(texunit2, coord).r;"\
				"	if(depth < focus)"\
				"	{"\
				"		f = 1.0 - clamp((depth - near) / (focus - near), 0.0, 1.0); "\
				"	} else {"\
				"		f = clamp((depth - focus) / (far - focus), 0.0, 1.0); "\
				"	}"\
				"	vec4 norm = texture2D(texunit0, coord) * (1.0 - f);"\
				"	vec4 blurred = texture2D(texunit1, coord) * f;"\
				"   gl_FragColor = blurred+norm;"\
				"}"
			};












			static const char *kappaleVertex = {
                    "uniform float wobble;"\
                    "uniform vec3 lightDir;"\
                    "varying vec4 fragmentvalo;"\
					"void main(void) "\
					"{"\
                    "   vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"\
                    "   vec3 valo = normalize(vec3(lightDir));"\
                    "   float l = max(dot(normal, valo), 0.0);"\
                    "   float l2 = pow(l, 3.0)*0.5;"\
                    "   fragmentvalo = gl_Color * l + vec4(1,1,1,0)*l2;"\
                    "   vec4 vert = (gl_Vertex + (0.05+0.4*cos(length(gl_Vertex)*5.0+wobble*251.0)*cos(wobble*46.0 + gl_Vertex.y*2.0))*vec4(gl_Normal,0));"\
                    "   vec4 position = (gl_ModelViewProjectionMatrix * vert);"\
					"   gl_Position = position;"\
					"   gl_TexCoord[0] = gl_MultiTexCoord0;"\
					"}"	
			};

            static const char *kappaleFragment = {
				"varying vec4 fragmentvalo;"\
                "void main(void) "\
                "{"\
                "   gl_FragColor = fragmentvalo;"\
                "}"\
            };













			// *** Jytky effun shader
			//

			static const char *jytkyVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"varying vec4 lcolor;"\
				"uniform vec3 lightDir;"\
				"uniform float pos;"\
				"varying vec4 shadowTexCoord;"\
				"void main(void) "\
				"{"\
				"   vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"\
				"   vec3 lDir = normalize(vec3(lightDir));"\
				"   float NdotL = max(dot(normal, lDir), 0.0);"\
				/*"   vec4 diffuse = vec4(0.57, 0.57, 0.57, 1);"\*/
				"   vec4 diffuse = vec4(1,1,1,1);"\
				/*scale texture*/
				"   coord  = gl_MultiTexCoord0.xy*4.0;"\
				"   coord2 = gl_MultiTexCoord0.xy*2.0;"\
				"	lcolor = diffuse * NdotL ;"\
				"   float aalto = sin(pos * gl_Vertex.y * 1.075 + 1.0);"\
				"   vec4 position = gl_ModelViewProjectionMatrix * (gl_Vertex + aalto * 2.0 * vec4(gl_Normal, 0));"\
				/*"   gl_Position = ftransform();"\*/
				"	gl_Position = position;"\
				"	shadowTexCoord = gl_TextureMatrix[0] * gl_ModelViewMatrix * gl_Vertex;"\
				"}"
			};

			static const char *jytkyFragment = {
				"uniform float alpha;"\
				/*caustics*/
				"uniform sampler2D texunit0;"\
				/*normal tex*/
				"uniform sampler2D texunit1;"\
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"varying vec4 lcolor;"\
				"uniform sampler2DShadow shadowMap;"\
				"varying vec4 shadowTexCoord;"\
				"void main()"\
				"{"\
				"	vec4 col  = texture2D(texunit0, coord); "\
				"	vec4 col2 = texture2D(texunit1, coord2); "\
				"   vec4 final = vec4(alpha, alpha, alpha ,alpha) * lcolor * min(vec4(1,1,1,1), (col2*col.r)*5.0);"\
				"   float shadow = max(0.3, shadow2DProj(shadowMap, shadowTexCoord).r);"\
				"   gl_FragColor =  shadow * vec4(final.rgb, 1.0);"\
				"}"
			};


			// *** Kitaratunneli
			//
/*
			static const char *kitaratunneliVertex = {
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"varying vec4 lcolor;"\
				"uniform vec3 lightDir;"\
				"uniform float pos;"\
				"void main(void) "\
				"{"\
				"   vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"\
				"   vec3 lDir = normalize(vec3(lightDir));"\
				"   float NdotL = max(dot(normal, lDir), 0.0);"\
				"   vec4 diffuse = vec4(1,1,1,1);"\
				"   coord  = gl_MultiTexCoord0.xy*4.0;"\
				"   coord2 = gl_MultiTexCoord0.xy*2.0;"\
				"	lcolor = diffuse * NdotL ;"\
				"   float aalto = sin(pos * gl_Vertex.y * 1.075 + 1.0);"\
				"   vec4 position = gl_ModelViewProjectionMatrix * (gl_Vertex + aalto * 4.0 * vec4(gl_Normal, 0));"\
				"	gl_Position = position;"\
				"}"
			};

			static const char *kitaratunneliFragment = {
				"uniform float alpha;"\
				"varying vec2 coord;"\
				"varying vec2 coord2;"\
				"varying vec4 lcolor;"\
				"varying vec4 shadowTexCoord;"\
				"void main()"\
				"{"\
				"	vec4 col  = texture2D(texunit0, coord); "\
				"	vec4 col2 = texture2D(texunit1, coord2); "\
				"   vec4 final = vec4(alpha, alpha, alpha ,alpha) * lcolor * min(vec4(1,1,1,1), (col2*col.r)*5.0);"\
				"   gl_FragColor =  vec4(final.rgb, 1.0);"\
				"}"
			};
*/
			// *** Gradient fade ja valaistus [alun kuu]
			// 

			static const char *lightfadeVertex = {
				"varying vec2 coord;"\
				/* lighting color adj */
				"varying vec4 lcolor;"\
				/* gl_color*/
				"varying vec4 rcolor;"\
				"uniform vec3 lightDir;"\
				"void main(void) "\
				"{"\
				"   rcolor = gl_Color;"\
				"   vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"\
				"   vec3 lDir = normalize(vec3(lightDir));"\
				"   float NdotL = max(dot(normal, lDir), 0.0);"\
				/*"   vec4 diffuse = vec4(0.57, 0.57, 0.57, 1);"\*/
				"   vec4 diffuse = vec4(1,1,1,1);"\
				/*scale texture*/
				"   coord  = gl_MultiTexCoord0.xy;"\
				"	lcolor = min(vec4(1,1,1,1), vec4(0.1,0.1,0.1,1) + diffuse * NdotL);"\
				"   gl_Position = ftransform();"\
				"}"
			};

			static const char *lightfadeFragment = {
				"uniform sampler2D tex;"\
				"uniform sampler2D gradient;"\
				"uniform float value;"\
				"uniform float value2;"\
				"varying vec2 coord;"\
				"varying vec4 lcolor;"\
				/* gl_color */
				"varying vec4 rcolor;"\
				"void main()		"\
				"{"\
				"   float v1 = value;"\
				"   float v2 = value2;"\
				"   if(v2 < v1) v2 = v1; "\
				"   vec4 actc = texture2D(tex, coord); "\
				"   vec4 gradientcolor = texture2D(gradient, coord); "\
				"   vec4 empty = vec4(0,0,0,1);"\
				"	float liuku = smoothstep(v1, v2, gradientcolor.r);"\
				"   if(gradientcolor.r==0.0) discard;"\
				"   if(liuku>0.99) discard;"\
				"	gl_FragColor = lcolor*mix(actc, empty, liuku);"\
				"}"
			};

			// *** Sini distortti
			// 
		static const char *sindistortFragment = {
			"uniform sampler2D tex;"\
			/*taajuudet*/
			"uniform float xfreq;"\
			"uniform float yfreq;"\
			/*vaihe josta effu alkaa*/
			"uniform float xphase;"\
			"uniform float yphase;"\
			/*amplitudi*/
			"uniform float xamp;"\
			"uniform float yamp;"\
			"void main()"\
			"{"\
			"	float xdiv = 3.14159 * xfreq;"\
			"	float ydiv = 3.14159 * yfreq;"\
			"   float a = yphase+gl_TexCoord[0].x+sin(gl_TexCoord[0].y*xdiv)*xamp;"\
			/*"   if(a<0.0) a+=1.0; else if(a>1.0) a-=1.0;"\ */
			"   float b = xphase+gl_TexCoord[0].y+sin(gl_TexCoord[0].x*ydiv)*yamp;"\
			/*"   if(b<0.0) b+=1.0; else if(b>1.0) b-=1.0;"\*/
			"	gl_FragColor = texture2D(tex, vec2(a,b));"\
			"   if(b<0.0 || b>1.0 || a<0.0 || b>1.0) gl_FragColor = vec4(1,1,1,0);"\
			"}"\
		};

			// *** Chrome sheideri
			// 
		static const char *chromeFragment ={
			"uniform sampler2D tex;"\
			/*vahvuus*/
			"uniform int times;"\
			"void main()"\
			"{"\
			" vec4 col = texture2D(tex, gl_TexCoord[0].xy);"\
			" col.r = max(abs(sin( (3.14159*1.0*col.r)/(1.0/float(times)*1.0) )),0.55);"\
			" col.g = abs(sin( (3.14159*1.0*col.g)/(1.0/float(times)*1.0) ));"\
			" col.b = abs(sin( (3.14159*1.0*col.b)/(1.0/float(times)*1.0) ));"\
			" gl_FragColor = col;"\
			"}"\
		};

			// *** Saturate/Brightness/Contrast
			// 
		static const char *colorFragment = {
			"uniform sampler2D tex;"\
			"const vec3 c_ch = vec3(1.0,1.0,1.0);"\
			"uniform float saturate;"\
			"uniform float brightness;"\
			"uniform float contrast;"\
			"void main()"\
			"{"\
			"	vec3 color = texture2D(tex, gl_TexCoord[0].xy).rgb;"\
			"	float x = sqrt(dot(color,color));"\
			"	color.r = pow(color.r+0.01,saturate);"\
			"	color.g = pow(color.g+0.01,saturate);"\
			"	color.b = pow(color.b+0.01,saturate);"\
			/* TODO: Check what exactly is happening here.. */
			"	gl_FragColor.xyz = clamp(0.866 + contrast*(x-0.866),0.05, 1.73)*normalize(color*c_ch)*brightness;"\
			"}"
		};

			// *** Env map reflection
			//
		static const char *envReflVertex = {
			"varying vec3 Normal;"\
			"varying vec3 EyeDir;"\
			"varying float LightIntensity;"\
			"uniform vec3 lightPos;"\
			"void main (void)"\
			"{"\
			"    gl_Position    = ftransform();"\
			"    Normal         = normalize(gl_NormalMatrix * gl_Normal);"\
			"    vec4 pos       = gl_ModelViewMatrix * gl_Vertex;"\
			"    EyeDir         = pos.xyz;"\
			"    LightIntensity = max(dot(normalize(lightPos - EyeDir), Normal), 0.0);"\
			"}"\
		};

		static const char *envReflFragment = {
			"const vec3 Xunitvec = vec3(1.0, 0.0, 0.0);"\
			"const vec3 Yunitvec = vec3(0.0, 1.0, 0.0);"\
			"uniform vec3 color;"\
			"uniform float mixRatio;"\
			"uniform sampler2D envMap;"\
			"varying vec3 Normal;"\
			"varying vec3 EyeDir;"\
			"varying float LightIntensity;"\
			"void main (void)"\
			"{    "\
			"    vec3 reflectDir = reflect(EyeDir, Normal);"\
			"    vec2 index;"\
			"    index.y = dot(normalize(reflectDir), Yunitvec);"\
			"    reflectDir.y = 0.0;"\
			"    index.x = dot(normalize(reflectDir), Xunitvec) * 0.5;"\
			"    if (reflectDir.z >= 0.0){"\
			"        index = (index + 1.0) * 0.5;"\
			"    } else {"\
			"        index.t = (index.t + 1.0) * 0.5;"\
			"        index.s = (-index.s) * 0.5 + 1.0;"\
			"    }"\
			"    vec3 envColor = vec3 (texture2D(envMap, index));"\
			"    vec3 base = LightIntensity * color;"\
			"    envColor = mix(envColor, base, mixRatio);"\
			"    gl_FragColor = vec4(envColor, 1.0);"\
			"}"\
		};

			// *** Shadow mapping
			//
		static const char *shadowMapVertex = {
			"varying vec4 shadowCoord;"\
			"void main (void)"\
			"{"\
			"   gl_Position = ftransform();"\
			/* shadow texture coordinates generation */
			"   shadowCoord = gl_TextureMatrix[0] * gl_ModelViewMatrix * gl_Vertex;"\
			"}"\
		};

		static const char *shadowMapFragment = {
			"uniform sampler2DShadow shadowMap;"\
			"varying vec4 shadowCoord;"\
			"void main(void)"\
			"{"\
			/* pick 1|0 from projected shadow map */
			"   gl_FragColor = shadow2DProj(shadowMap, shadowCoord).r * gl_Color;"\
			"}"\
		};

			// *** Shadow mapping with texture
			//
		static const char *shadowMapTexVertex = {
			"varying vec4 shadowCoord;"\
			"varying vec2 texCoord;"\
			"void main (void)"\
			"{"\
			"   gl_Position = ftransform();"\
			"   texCoord = gl_MultiTexCoord0.xy;"\
			/* shadow texture coordinates generation */
			"   shadowCoord = gl_TextureMatrix[0] * gl_ModelViewMatrix * gl_Vertex;"\
			"}"\
		};

		static const char *shadowMapTexFragment = {
			"varying vec2 texCoord;"\
			"uniform sampler2D texture0;"\
			"varying vec4 shadowCoord;"\
			"uniform sampler2DShadow shadowMap;"\
			"void main(void)"\
			"{"\
			/* pick 1|0 from projected shadow map */
			"	vec4 color = gl_Color;"\
			"   gl_FragColor = shadow2DProj(shadowMap, shadowCoord).r * texture2D(texture0, texCoord) * color;"\
			"}"\
		};
	
			// *** Lightrays
			//
		static const char *lightrayVertex = {
			"varying vec4 shadowCoord;"\
			"void main (void)"\
			"{"\
			/* shadow texture coordinates generation */
			"   shadowCoord = gl_TextureMatrix[0] * gl_ModelViewMatrix * gl_Vertex;"\
			"   gl_Position = ftransform();"\
			"}"\
		};

		static const char *lightrayFragment = {
			"uniform sampler2D caustic;"\
			"uniform sampler2DShadow shadowMap;"\
			"varying vec4 shadowCoord;"\
			"void main(void)"\
			"{"\
			/* pick 1|0 from projected shadow map */
			/*"  gl_FragColor = texture2DProj(caustic, shadowCoord*14.0) * shadow2DProj(shadowMap, shadowCoord).r * vec4(0.1065, 0.1065, 0.090565, 1);"\*/
			"  gl_FragColor = texture2DProj(caustic, shadowCoord*24.0) * shadow2DProj(shadowMap, shadowCoord).r * vec4(0.102065, 0.102065, 0.1020790565, 1);"\
			"}"\
		};

			// *** Vesieffu
			// [orange bookin pohjat]
			// Ylemmässä fade out
		static const char *waterReflVertex = {
			"varying vec4 waterTex0;"\
			"varying vec4 waterTex1;"\
			"varying vec4 waterTex2;"\
			"varying vec4 waterTex3;"\
			"varying vec4 waterTex4;"\
			"varying vec2 texCoord;"\
			"uniform vec4 viewpos, lightpos;"\
			"uniform float time, time2;"\
			""\
			"void main(void)"\
			"{"\
			"vec4 mpos, temp;"\
			/*Our planes normal is y = 1 -> TNB are easy to get*/
			"vec4 tangent = vec4(1.0, 0.0, 0.0, 0.0);"\
			"vec4 norm = vec4(0.0, 1.0, 0.0, 0.0);"\
			"vec4 binormal = vec4(0.0, 0.0, 1.0, 0.0);"\
			""\
			"mat4 mvp = gl_ModelViewProjectionMatrix;"\
			"mat4 mtx = gl_TextureMatrix[0];"\
			""\
			/*proj*/
			"temp = viewpos - gl_Vertex;"\
			"waterTex4.x = dot(temp, tangent);"\
			"waterTex4.y = dot(temp, binormal);"\
			"waterTex4.z = dot(temp, norm);"\
			"waterTex4.w = 0.0;"\
			""\
			/*light*/
			"temp = lightpos - gl_Vertex;"\
			"waterTex0.x = dot(temp, tangent);"\
			"waterTex0.y = dot(temp, binormal);"\
			"waterTex0.z = dot(temp, norm);"\
			"waterTex0.w = 0.0;"\
			""\
			"mpos = mvp * gl_Vertex;"\
			""\
			"vec4 t1 = vec4(0.0, -time, 0.0,0.0);"\
			"vec4 t2 = vec4(0.0, -time2, 0.0,0.0);"\
			""\
			"texCoord = gl_MultiTexCoord1.xy;"\
			"waterTex1 = gl_MultiTexCoord1 + t1;"\
			"waterTex2 = gl_MultiTexCoord2 + t2;"\
			""\
			"waterTex3 = mpos;"\
			""\
			"gl_Position = ftransform();"\
			"}"\
		};

		static const char *waterReflFragment = {
			
			"uniform sampler2D water_normalmap;"\
			"uniform sampler2D water_reflection;"\
			"uniform sampler2D water_refraction;"\
			"uniform sampler2D water_dudvmap;"\
			"uniform sampler2D water_depthmap;"\
			"uniform sampler2D water_envmap;"\
			"uniform vec4 waterColor;"\
			"uniform float fade;"\
			"varying vec2 texCoord;"\
			""\
			"varying vec4 waterTex0;/*lightpos*/"\
			"varying vec4 waterTex1;/*moving texcoords*/"\
			"varying vec4 waterTex2;/*moving texcoords*/"\
			"varying vec4 waterTex3;/*for projection*/"\
			"varying vec4 waterTex4;/*viewts*/"\
			""\
			"void main(void)"\
			"{"\
			"const vec4 sca = vec4(0.005, 0.005, 0.005, 0.005);"\
			"const vec4 sca2 = vec4(0.02, 0.02, 0.02, 0.02);"\
			"const vec4 tscale = vec4(0.25, 0.25, 0.25, 0.25);"\
			"const vec4 two = vec4(2.0, 2.0, 2.0, 1.0);"\
			"const vec4 mone = vec4(-1.0, -1.0, -1.0, 1.0);"\
			""\
			"const vec4 ofive = vec4(0.5,0.5,0.5,1.0);"\
			""\
			"const float exponent = 64.0;"\
			""\
			/*dudvdist*/
			"vec4 lightTS = normalize(waterTex0);"\
			"vec4 viewt = normalize(waterTex4);"\
			"vec4 disdis = texture2D(water_dudvmap, vec2(waterTex2 * tscale));"\
			"vec4 dist = texture2D(water_dudvmap, vec2(waterTex1 + disdis*sca2));"\
			"vec4 fdist = dist;"\
			"fdist = fdist * two + mone;"\
			"fdist = normalize(fdist);"\
			"fdist *= sca;"\
			""\
			/*load normalmap*/
			"vec4 nmap = texture2D(water_normalmap, vec2(waterTex1 + disdis*sca2));"\
			"nmap = (nmap-ofive) * two;"\
			"vec4 vNorm = nmap;"\
			"vNorm = normalize(nmap);"\
			""\
			/*proj. texcoords*/
			"vec4 tmp = vec4(1.0 / waterTex3.w);"\
			"vec4 temp = tmp;"\
			""\
			"vec4 projCoord = waterTex3 * tmp;"\
			"projCoord += vec4(1.0);"\
			"projCoord *= vec4(0.5);"\
			"tmp = projCoord + fdist;"\
			"tmp = clamp(tmp, 0.001, 0.999);"\
			""\
			/*reflection,refraction and depth texture*/
			"vec4 refTex = texture2D(water_reflection, vec2(tmp));"\
			"vec4 refl = refTex;"\
			"vec4 refr = texture2D(water_refraction, vec2(tmp));"\
			"vec4 wdepth = texture2D(water_depthmap, vec2(tmp));"\
			""\
			"wdepth = vec4(pow(wdepth.x, 4.0));"\
			"vec4 invdepth = 1.0 - wdepth;"\
			""\
			/*calculate specular highlight*/
			"vec4 vRef = normalize(reflect(-lightTS, vNorm));"\
			"float stemp =max(0.0, dot(viewt, vRef) );"\
			"stemp = pow(stemp, exponent);"\
			"vec4 specular = vec4(stemp);"\
			""\
			/*calculate fresnel and inverted fresnel*/
			"vec4 invfres = vec4( dot(vNorm, viewt) );"\
			"vec4 fres = vec4(1.0) -invfres ;"\
			""\
			/*calculate reflection and refraction*/
			"refr *= invfres;"\
			"refr *= invdepth;"\
			"temp = waterColor * wdepth * invfres;"\
			"refr += temp;"\
			"refl *= fres;"\
			""\
			/*add reflection and refraction*/
			"tmp = refr + refl;"\
			""\
			"gl_FragColor = vec4(tmp + fade*specular) * texture2D(water_envmap, texCoord).r;"\
			"}"\
		};


			// *** Vesieffu2
			//
		static const char *waterRefl2Vertex = {
			"varying vec4 waterTex0;"\
			"varying vec4 waterTex1;"\
			"varying vec4 waterTex2;"\
			"varying vec4 waterTex3;"\
			"varying vec4 waterTex4;"\
			"uniform vec4 viewpos, lightpos;"\
			"varying vec2 texCoord;"\
			"uniform float time, time2;"\
			""\
			"void main(void)"\
			"{"\
			"vec4 mpos, temp;"\
			/*Our planes normal is y = 1 -> TNB are easy to get*/
			"vec4 tangent = vec4(1.0, 0.0, 0.0, 0.0);"\
			"vec4 norm = vec4(0.0, 1.0, 0.0, 0.0);"\
			"vec4 binormal = vec4(0.0, 0.0, 1.0, 0.0);"\
			""\
			"mat4 mvp = gl_ModelViewProjectionMatrix;"\
			"mat4 mtx = gl_TextureMatrix[0];"\
			""\
			/*proj*/
			"temp = viewpos - gl_Vertex;"\
			"waterTex4.x = dot(temp, tangent);"\
			"waterTex4.y = dot(temp, binormal);"\
			"waterTex4.z = dot(temp, norm);"\
			"waterTex4.w = 0.0;"\
			""\
			/*light*/
			"temp = lightpos - gl_Vertex;"\
			"waterTex0.x = dot(temp, tangent);"\
			"waterTex0.y = dot(temp, binormal);"\
			"waterTex0.z = dot(temp, norm);"\
			"waterTex0.w = 0.0;"\
			""\
			"mpos = mvp * gl_Vertex;"\
			""\
			"vec4 t1 = vec4(0.0, -time, 0.0,0.0);"\
			"vec4 t2 = vec4(0.0, -time2, 0.0,0.0);"\
			""\
			"texCoord = gl_MultiTexCoord5.xy;"\
			"waterTex1 = gl_MultiTexCoord1 + t1;"\
			"waterTex2 = gl_MultiTexCoord2 + t2;"\
			""\
			"waterTex3 = mpos;"\
			""\
			"gl_Position = ftransform();"\
			"}"\
		};

		static const char *waterRefl2Fragment = {
			
			"uniform sampler2D water_normalmap;"\
			"uniform sampler2D water_reflection;"\
			"uniform sampler2D water_refraction;"\
			"uniform sampler2D water_dudvmap;"\
			"uniform sampler2D water_depthmap;"\
			"uniform sampler2D water_envmap;"\
			"varying vec2 texCoord;"\
			"uniform vec4 waterColor;"\
			"uniform float fade;"\
			""\
			"varying vec4 waterTex0;/*lightpos*/"\
			"varying vec4 waterTex1;/*moving texcoords*/"\
			"varying vec4 waterTex2;/*moving texcoords*/"\
			"varying vec4 waterTex3;/*for projection*/"\
			"varying vec4 waterTex4;/*viewts*/"\
			""\
			"void main(void)"\
			"{"\
			"const vec4 sca = vec4(0.005, 0.005, 0.005, 0.005);"\
			"const vec4 sca2 = vec4(0.02, 0.02, 0.02, 0.02);"\
			"const vec4 tscale = vec4(0.25, 0.25, 0.25, 0.25);"\
			"const vec4 two = vec4(2.0, 2.0, 2.0, 1.0);"\
			"const vec4 mone = vec4(-1.0, -1.0, -1.0, 1.0);"\
			""\
			"const vec4 ofive = vec4(0.5,0.5,0.5,1.0);"\
			""\
			"const float exponent = 64.0;"\
			""\
			/*dudvdist*/
			"vec4 lightTS = normalize(waterTex0);"\
			"vec4 viewt = normalize(waterTex4);"\
			"vec4 disdis = texture2D(water_dudvmap, vec2(waterTex2 * tscale));"\
			"vec4 dist = texture2D(water_dudvmap, vec2(waterTex1 + disdis*sca2));"\
			"vec4 fdist = dist;"\
			"fdist = fdist * two + mone;"\
			"fdist = normalize(fdist);"\
			"fdist *= sca;"\
			""\
			/*load normalmap*/
			"vec4 nmap = texture2D(water_normalmap, vec2(waterTex1 + disdis*sca2));"\
			"nmap = (nmap-ofive) * two;"\
			"vec4 vNorm = nmap;"\
			"vNorm = normalize(nmap);"\
			""\
			/*proj. texcoords*/
			"vec4 tmp = vec4(1.0 / waterTex3.w);"\
			"vec4 temp = tmp;"\
			""\
			"vec4 projCoord = waterTex3 * tmp;"\
			"projCoord += vec4(1.0);"\
			"projCoord *= vec4(0.5);"\
			"tmp = projCoord + fdist;"\
			"tmp = clamp(tmp, 0.001, 0.999);"\
			""\
			/*reflection,refraction and depth texture*/
			"vec4 refTex = texture2D(water_reflection, vec2(tmp));"\
			"vec4 refl = refTex;"\
			"vec4 refr = texture2D(water_refraction, vec2(tmp));"\
			"vec4 wdepth = texture2D(water_depthmap, vec2(tmp));"\
			""\
			"wdepth = vec4(pow(wdepth.x, 4.0));"\
			"vec4 invdepth = 1.0 - wdepth;"\
			""\
			/*calculate specular highlight*/
			"vec4 vRef = normalize(reflect(-lightTS, vNorm));"\
			"float stemp =max(0.0, dot(viewt, vRef) );"\
			"stemp = pow(stemp, exponent);"\
			"vec4 specular = vec4(stemp);"\
			""\
			/*calculate fresnel and inverted fresnel*/
			"vec4 invfres = vec4( dot(vNorm, viewt) );"\
			"vec4 fres = vec4(1.0) -invfres ;"\
			""\
			/*calculate reflection and refraction*/
			"refr *= invfres;"\
			"refr *= invdepth;"\
			"temp = waterColor * wdepth * invfres;"\
			"refr += temp;"\
			"refl *= fres;"\
			""\
			/*add reflection and refraction*/
			"tmp = refr + refl;"\
			""\
			"gl_FragColor = tmp + fade*specular * texture2D(water_envmap, texCoord).r;"\
			"}"\
		};


			// *** Floor
			//
		static const char *floor1Vertex = {
			"varying vec2 coord0;"\
			"varying vec2 coord1;"\
			"void main (void)"\
			"{"\
			"   gl_Position = ftransform();"\
			"   coord0 = gl_MultiTexCoord0.xy;"\
			"   coord1 = gl_MultiTexCoord0.xy;"\
			"}"\
		};

		static const char *floor1Fragment = {
			"uniform sampler2D tex0;"\
			"uniform sampler2D tex1;"\
			"varying vec2 coord0;"\
			"varying vec2 coord1;"\
			"void main(void)"\
			"{"\
			" vec4 col = texture2D(tex0, coord0) * texture2D(tex1, coord1).r; "\
			" gl_FragColor = col; "\
			"}"\
		};

			// *** Floor
			//
		static const char *synkkaVertex = {
			"varying vec2 coord0;"\
			"varying vec4 lcolor;"\
			"uniform float scale;"\
			"uniform float time;"\
			"uniform vec3 lightDir;"\
			"void main (void)"\
			"{"\
			"   vec4 diffuse = vec4(1,1,1,1);"\
			"   vec3 normal = normalize(gl_NormalMatrix * gl_Normal);"\
			"   vec3 lDir = normalize(vec3(lightDir));"\
			"   float NdotL = max(dot(normal, lDir), 0.0);"\
			"	lcolor = diffuse * NdotL ;"\
			"   coord0 = gl_MultiTexCoord0.xy;"\
			"   float aalto = sin(scale * gl_Vertex.y * 0.075);"\
			/*"   float aalto2 = sin(time * 15.0 * gl_Vertex.z);"\*/
			"   vec4 position = gl_ModelViewProjectionMatrix * (gl_Vertex +  aalto * 4.0 * vec4(gl_Normal * scale, 0));"\
			"   gl_Position = position;"\
			"}"\
		};


		static const char *synkkaFragment = {
			"varying vec2 coord0;"\
			"varying vec4 lcolor;"\
			"uniform sampler2D tex0;"\
			"uniform sampler2D tex1;"\
			"uniform sampler2D tex2;"\
			"uniform float fade;"\
			"uniform float time;"\
			"void main(void)"\
			"{"\
			" vec2 offset = sin(time * 0.075)*(texture2D(tex1, coord0).xy - vec2(0.5, 0.5));"\
			" vec4 col = texture2D(tex0, coord0);"\
			" col *= 0.45 + 0.55*lcolor;"\
			" float mod = (0.45 + 0.55 * texture2D(tex2, coord0+offset).r);"\
			" gl_FragColor = vec4(col.rgb, 1.0)/** mod*/; "\
			"}"\
		};


        // *** cubemapping

        static const char *cubereflectVertex = {
            "varying vec3 reflectVector; "\
            "void main()"\
            "{"\
            "   vec3 ecposition = vec3(gl_ModelViewMatrix * gl_Vertex);"\
            "   vec3 eyedir = ecposition - vec3(0.0, 0.0, 0.0);"\
            "   vec3 normal = normalize(gl_NormalMatrix * gl_Normal); "\
            "   reflectVector = reflect(eyedir, normal);"\
            "   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex; "\
            "}"
        };

        static const char *cubereflectFragment = {
            "varying vec3 reflectVector; "\
            "uniform samplerCube cubemap; "\
            "void main()"\
            "{"\
            "   vec4 col = textureCube(cubemap, reflectVector);"\
            "   gl_FragColor = col;"\
            "}"
        };

		// ---------------------------------------------------------------
		// Soft shadows tutorial
		// http://www.gamedev.net/reference/articles/article2193.asp
		// ---------------------------------------------------------------



	dmsMsg("ShaderHolder::init() : Initializing shaders\n");

	//kitaratunneli = new Shader();
	//kitaratunneli->init("kitaratunneli", kitaratunneliFragment, kitaratunneliVertex);

	kristalli = new Shader();
	kristalli->init("kristalli", kristalliFragment, kristalliVertex);

   	cubereflect = new Shader();
	cubereflect->init("cubereflect", cubereflectFragment, cubereflectVertex);

	kappale = new Shader();
	kappale->init("kappale", kappaleFragment, kappaleVertex);

	synkkatausta = new Shader();
	synkkatausta->init("synkkatausta", synkkataustaFragment, synkkataustaVertex);

	synkka = new Shader();
	synkka->init("synkka", synkkaFragment, synkkaVertex);

	floor1 = new Shader();
	floor1->init("floor1", floor1Fragment, floor1Vertex);

	waterReflect2 = new Shader();
	waterReflect2->init("waterRefl2", waterRefl2Fragment, waterRefl2Vertex);

	waterReflect = new Shader();
	waterReflect->init("waterRefl", waterReflFragment, waterReflVertex);

	lightray = new Shader();
	lightray->init("lightray", lightrayFragment, lightrayVertex);

	shadowMapTex = new Shader();
	shadowMapTex->init("shadowmap + tex", shadowMapTexFragment, shadowMapTexVertex);

	shadowMap = new Shader();
	shadowMap->init("shadowmap.", shadowMapFragment, shadowMapVertex);

	envrefl = new Shader();
	envrefl->init("env map reflection", envReflFragment, envReflVertex);

	color = new Shader();
	color->init("color", colorFragment, emptyVertex);

	sindistort = new Shader();
	sindistort->init("sindistort", sindistortFragment, emptyVertex);

	chrome = new Shader();
	chrome->init("chrome", chromeFragment, emptyVertex);

	lightfade = new Shader();
	lightfade->init("light+fade", lightfadeFragment, lightfadeVertex);

	jytky = new Shader();
	jytky->init("jytky", jytkyFragment, jytkyVertex);

	blurx = new Shader();
	blurx->init("blurx", blurFragment, blurxVertex);

	blury = new Shader();
	blury->init("blury", blurFragment, bluryVertex);

	blur2x = new Shader();
	blur2x->init("blur2x", blur2Fragment, blurxVertex);

	blur2y = new Shader();
	blur2y->init("blur2y", blur2Fragment, bluryVertex);

	darken = new Shader();
	darken->init("darken",darkenFragment, darkenVertex);

	glowc = new Shader();
	glowc->init("glowc", glowcFragment, glowcVertex);

	edge = new Shader();
	edge->init("lap", edgeFragment, emptyVertex);

	displace = new Shader();
	displace->init("displace", displaceFragment, displaceVertex);

	sivuttaintausta = new Shader();
	sivuttaintausta->init("displace", sivuttaintaustaFragment, sivuttaintaustaVertex);

	invert = new Shader();
	invert->init("invert", invertFragment, invertVertex);

    blackwhite = new Shader();
	blackwhite->init("blackwhite", bwFragment, bwVertex);

//	lightdir = new Shader();
//	lightdir->init("lightdir", lightFragment, lightVertex);

	lightpoint = new Shader();
	lightpoint->init("lightpoint", lightpointFragment, lightpointVertex);

	lightambientpoint = new Shader();
	lightambientpoint->init("lightambientpoint", lightambientpointFragment, lightambientpointVertex);

	gradientfade = new Shader();
	gradientfade->init("gradientfade", gradientfadeFragment, gradientfadeVertex);

	dof = new Shader();
	dof->init("depthoffield", dofFragment, dofVertex);

	// varmistetana ettei ole sheideriä aktiivisena
	this->unbind();

	init_ok = true;

	dmsMsg("ShaderHolder::init() : Shaders created\n");
}

void ShaderHolder::deinit() {

	if(!init_ok) return;

	kristalli->deinit();
	delete kristalli;

	synkkatausta->deinit();
	delete synkkatausta;

	synkka->deinit();
	delete synkka;

	floor1->deinit();
	delete floor1;

	waterReflect2->deinit();
	delete waterReflect2;

	waterReflect->deinit();
	delete waterReflect;

	lightray->deinit();
	delete lightray;

	shadowMapTex->deinit();
	delete shadowMapTex;

	shadowMap->deinit();
	delete shadowMap;

	envrefl->deinit();
	delete envrefl;

	sindistort->deinit();
	delete sindistort;
	
	chrome->deinit();
	delete chrome;

	lightfade->deinit();
	delete lightfade;

	jytky->deinit();
	delete jytky;

	blurx->deinit();
	delete blurx;

	blury->deinit();
	delete blury;

	darken->deinit();
	delete darken;

	glowc->deinit();
	delete glowc;

	edge->deinit();
	delete edge;

	blackwhite->deinit();
	delete blackwhite;

	lightpoint->deinit();
	delete lightpoint;

	lightambientpoint->deinit();
	delete lightambientpoint;

	gradientfade->deinit();
	delete gradientfade;

	invert->deinit();
	delete invert;
	
	dof->deinit();
	delete dof;

	dmsMsg("ShaderHolder::deinit() : Shaders released\n");
}

//////////////////////////////////////////////
// Shader class 
//////////////////////////////////////////////
void Shader::init(const char *name_, const char *frag, const char *vert) {

	this->name = name_;

	vertex = glCreateShaderObjectARB(GL_VERTEX_SHADER_ARB);
	glShaderSourceARB(this->vertex, 1, &vert,NULL);
	glCompileShaderARB(this->vertex);
	debugShader(vertex, name_);

	fragment = glCreateShaderObjectARB(GL_FRAGMENT_SHADER_ARB);
	glShaderSourceARB(this->fragment, 1, &frag,NULL);
	glCompileShaderARB(this->fragment);
	debugShader(fragment, name_);

	program = glCreateProgramObjectARB();
	glAttachObjectARB(this->program,vertex);
	glAttachObjectARB(this->program,fragment);
	glLinkProgramARB(this->program);
	debugShader(this->program, name_);

	glUseProgramObjectARB(program);
}

void Shader::initFromFile(const char *name_, char *fragFile, char *vertFile) {
  
	char fr[10000], vr[10000];

	this->loadFromFile(fragFile, fr);
	this->loadFromFile(vertFile, vr);

    // load vertex program
   if (vertFile!=0)
   if (vr == 0)
   { 
	  
	   memset(vr,' ',10000);
	  char buf[100];
	  sprintf(buf, "error: couldn't load vertex shader! [%s from %s] \n", name_, vertFile);
	  MessageBox(dmsGetHWND(), buf, name_, MB_OK|MB_TOPMOST);     
      dmsMsg("Error: couldn't load vertex shader [%s from %s]\n", name_, vertFile);
   }

  
  // Load fragment program
  if (fragFile!=0)
  if (fr == 0)
  {
	  memset(fr,' ',10000);
      dmsMsg("Error: couldn't load fragment shader [%s from %s]\n", name_, fragFile);
	  char buf[100];
	  sprintf(buf, "Error: couldn't load vertex shader! [%s from %s]\n", name_, fragFile);
	  MessageBox(dmsGetHWND(), buf, name_, MB_OK|MB_TOPMOST);

  }
	init(name_ , fr, vr);
}

bool Shader::loadFromFile(char *filename, char* buffer) {

	std::fstream f;
	f.open(filename, std::ios::in|std::ios::binary);

	if (!f.is_open() || !f.good())
	{
		MessageBox(dmsGetHWND(), filename, "Failed to load file", MB_OK|MB_TOPMOST);
		dmsMsg("ERROR: Failed to load %s\n", filename);
		return false;
	}

	// clear old list
	char chunk_char=' ';
	std::string text;

	while (f.good())
	{
			f.read(&chunk_char, sizeof(char));
			text.append(1,chunk_char);
	}

	strncpy(buffer, text.c_str(), 10000);

	f.close();

	return true;
}

void Shader::deinit() {
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteProgram(program);
}

void Shader::bind() {
		glUseProgramObjectARB(this->program);
}

void Shader::unbind() {
		glUseProgramObjectARB(0);
}

////////////////////////////////////////////////////////////////
// PARAMETER PASSING 
////////////////////////////////////////////////////////////////

bool Shader::setUniform1f(char* varname, GLfloat v0)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform1fARB(loc, v0);
    
    return true;
}

bool Shader::setUniform2f(char* varname, GLfloat v0, GLfloat v1)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform2fARB(loc, v0, v1);
    
    return true;
}

bool Shader::setUniform3f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2)
{
    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform3fARB(loc, v0, v1, v2);

    return true;
}

bool Shader::setUniform4f(char* varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform4fARB(loc, v0, v1, v2, v3);

    return true;
}

bool Shader::setUniform1i(char* varname, GLint v0)
{ 


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform1iARB(loc, v0);
    
    return true;
}
bool Shader::setUniform2i(char* varname, GLint v0, GLint v1)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform2i(loc, v0, v1);


    return true;
}

bool Shader::setUniform3i(char* varname, GLint v0, GLint v1, GLint v2)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform3i(loc, v0, v1, v2);

    return true;
}
bool Shader::setUniform4i(char* varname, GLint v0, GLint v1, GLint v2, GLint v3)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform4i(loc, v0, v1, v2, v3);

    return true;
}

bool Shader::setUniform1fv(char* varname, GLsizei count, GLfloat *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform1fv(loc, count, value);

    return true;
}
bool Shader::setUniform2fv(char* varname, GLsizei count, GLfloat *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform2fv(loc, count, value);

    return true;
}

bool Shader::setUniform3fv(char* varname, GLsizei count, GLfloat *value)
{

    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform3fv(loc, count, value);

    return true;
}

bool Shader::setUniform4fv(char* varname, GLsizei count, GLfloat *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform4fv(loc, count, value);

    return true;
}

bool Shader::setUniform1iv(char* varname, GLsizei count, GLint *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform1iv(loc, count, value);

    return true;
}

bool Shader::setUniform2iv(char* varname, GLsizei count, GLint *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform2iv(loc, count, value);

    return true;
}

bool Shader::setUniform3iv(char* varname, GLsizei count, GLint *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform3iv(loc, count, value);

    return true;
}

bool Shader::setUniform4iv(char* varname, GLsizei count, GLint *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniform4iv(loc, count, value);

    return true;
}

bool Shader::setUniformMatrix2fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniformMatrix2fv(loc, count, transpose, value);

    return true;
}

bool Shader::setUniformMatrix3fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value)
{


    
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniformMatrix3fv(loc, count, transpose, value);

    return true;
}

bool Shader::setUniformMatrix4fv(char* varname, GLsizei count, GLboolean transpose, GLfloat *value)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
    
    glUniformMatrix4fv(loc, count, transpose, value);

    return true;
}

GLint Shader::GetUniLoc(const GLcharARB *name)
{
	GLint loc;

	loc = glGetUniformLocationARB(this->program, name);
	if (loc == -1) 
	{
        dmsMsg("Error: can't find uniform variable %s from %s\n", name, this->name);

	}
	return loc;
}

void Shader::GetUniformfv(char* name, GLfloat* values)
{
    GLint loc;

	loc = glGetUniformLocationARB(this->program, name);
	if (loc == -1) 
	{
		dmsMsg("Error: can't find uniform variable %s \n", name);
	}
	glGetUniformfvARB(this->program, loc, values);
	
}

void Shader::GetUniformiv(char* name, GLint* values)
{
    GLint loc;

	loc = glGetUniformLocationARB(this->program, name);
	if (loc == -1) 
	{
        dmsMsg("Error: can't find uniform variable %s \n", name);
	}
	
	glGetUniformivARB(this->program, loc, values);

}

bool Shader::setVertexAttrib1f(char *varname, GLfloat v0)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
   glVertexAttrib1f(loc, v0);

   return true;
}

bool Shader::setVertexAttrib2f(char *varname, GLfloat v0, GLfloat v1)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable
   glVertexAttrib2f(loc, v0, v1);
   
   return true;
}

bool Shader::setVertexAttrib3f(char *varname, GLfloat v0, GLfloat v1, GLfloat v2)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable   
    glVertexAttrib3f(loc, v0, v1, v2);
    
    return true;
}

bool Shader::setVertexAttrib4f(char *varname, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    GLint loc = GetUniLoc(varname);
    if (loc==-1) return false;  // can't find variable

   glVertexAttrib4f(loc, v0, v1, v2, v3);
   
   return true;
}

////////////////////////////////////////////////////////////
// Debug global
////////////////////////////////////////////////////////////

void debugShader(GLuint obj, const char *name)
{
	int infologLength = 0;
	char infoLog[1024];
 
	if (glIsShader(obj))  {
		glGetShaderInfoLog(obj, 1024, &infologLength, infoLog);
		if(infologLength>0) MessageBox(dmsGetHWND(), infoLog, name, MB_OK|MB_TOPMOST);		
	}  else  {
		glGetProgramInfoLog(obj, 1024, &infologLength, infoLog);

	}	
		
}	

////////////////////////////////////////////////////////////
// ShaderHolder
////////////////////////////////////////////////////////////

void ShaderHolder::unbind() {
		glUseProgramObjectARB(0);
}