//-------------------------------------------------------
//	Headers
//-------------------------------------------------------

#ifdef _DEBUG
	#include <stdlib.h>
	#include "mmgr.h"
#endif

#include <math.h>
#include "spline.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

SplineSystem::SplineSystem()
{
	currentKey = NULL;
}

SplineSystem::~SplineSystem()
{
	currentKey = NULL;
	keys.freeList();
}

// Loop keys
Vector3 SplineSystem::calculateHermiteTangent( Node <SplineKey> *key, int sel )
{
	Node <SplineKey> *key_1 = NULL;
	Node <SplineKey> *key1 = NULL;
	Vector3 g1, g2, g3, tangent;

	if( key->next == NULL ) key = keys.getHead();
	key_1 = key->previous;
	key1 = key->next;

	if( key == keys.getHead() )
	{
//		dmsMsg( "Hep\n" );
		key_1 = keys.getTail()->previous;
	}

	if( key == keys.getTail()->previous )
	{
//		dmsMsg( "Hop\n" );
		key1 = keys.getHead();
	}

//	dmsMsg( "%d %d %d\n", key_1->a->frame, key->a->frame, key1->a->frame );

	if( !key_1 || !key || !key1 )
	{
		return Vector3( 0.0f, 0.0f, 0.0f );
	}

	//g1 = (pn - p(n-1))*(1+B),
	//g2 = (p(n+1) - pn)*(1-B),
	//g3 = g2 - g1,
	g1 = ( ( key->a->v - key_1->a->v ) ) * ( 1.0f + key->a->bias );
	g2 = ( ( key1->a->v - key->a->v ) ) * ( 1.0f - key->a->bias );
	g3 = g2 - g1;

//	dmsMsg( "\n%f %f %f\n", g1.x, g1.y, g1.z );
//	dmsMsg( "%f %f %f\n", g2.x, g2.y, g2.z );
//	dmsMsg( "%f %f %f\n", g3.x, g3.y, g3.z );

	//tangent case a: an = (g1 + g3*(0.5 + 0.5*C))*(1-T), sel == 0
	//tangent case b: bn = (g1 + g3*(0.5 - 0.5*C))*(1-T), sel == 1
	tangent = ( sel == 0 ) ? ( g1 + g3 * ( 0.5f + 0.5f * key->a->continuity ) ) * ( 1.0f - key->a->tension ) : ( g1 + g3 * ( 0.5f - 0.5f * key->a->continuity ) ) * ( 1.0f - key->a->tension );

	return tangent;
}

void SplineSystem::addKey( unsigned int frame, Vector3 v, float b, float c, float t )
{
	SplineKey *k = NULL;

	k = new SplineKey;
	k->bias = b;
	k->continuity = c;
	k->tension = t;
	k->frame = frame;
	k->v = v;
	keys.addTail( k );

	currentKey = keys.getHead();
}

void SplineSystem::update( unsigned int frame )
{
	if( currentKey == NULL || frame == 0 )
	{
//		dmsMsg( "Animation start\n" );
		currentKey = keys.getHead();
	}

	if( currentKey )
	{
//		dmsMsg( "Frame: %d\n", currentKey->a->frame );

		if( currentKey != keys.getTail() )
		{
			if( frame >= currentKey->next->a->frame )
			{
//				dmsMsg( "Frame vaihtuu\n" );
				currentKey = currentKey->next;
			}
		}
		else
		{
			currentKey = keys.getHead();
		}
	}
}

void SplineSystem::updateKey( unsigned int i, Vector3 v )
{
	Node <SplineKey> *node = keys.get( i );

	if( node )
	{
		node->a->v += v;
	}
}

Vector3 SplineSystem::getValue( float position )
{	
	Node <SplineKey> *k1 = NULL;
	Vector3 result;

//	dmsMsg( "Position: %d\n", ( unsigned int )position );
	currentKey = keys.get( ( unsigned int )position );

	if( currentKey ) k1 = currentKey->next;

	if( currentKey && k1 )
	{
//		dmsMsg( "getValue\n" );
		Vector3 tangent_in, tangent_out;

		//float t = float( frame - currentKey->a->frame ) / float ( k1->a->frame - currentKey->a->frame );
		t = position - ( unsigned int )position;
		float term1 = 2 * t*t*t - 3 * t*t + 1;
		float term2 = t*t*t - 2 * t*t + t;
		float term3 = -2 * t*t*t + 3 * t*t;
		float term4 = t*t*t - t*t;

//		dmsMsg( "T1: %f, T2: %f, T3: %f, T4: %f\n", term1, term2, term3, term4 );

		tangent_in = calculateHermiteTangent( currentKey, 0 );
		tangent_out = calculateHermiteTangent( k1, 1 );

//		dmsMsg( "%f %f %f\n", tangent_in.x, tangent_in.y, tangent_in.z );
//		dmsMsg( "%f %f %f\n", tangent_out.x, tangent_out.y, tangent_out.z );

		if( currentKey == keys.getTail()->previous )
		{
			result = ( currentKey->a->v * term1 ) + ( tangent_in * term2 ) + ( keys.getHead()->a->v * term3 ) + ( tangent_out * term4 );
		}
		else
		{
			result = ( currentKey->a->v * term1 ) + ( tangent_in * term2 ) + ( k1->a->v * term3 ) + ( tangent_out * term4 );
		}
		
//		dmsMsg( "getValue valmis: %f %f %f\n", result.x, result.y ,result.z );
	}
	
	return result;
}

SplineKey *SplineSystem::getKey( unsigned int i )
{
	Node <SplineKey> *node = NULL;

	node = keys.get( i );

	return node->a;
}