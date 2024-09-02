//--------------------------------------------------------------------------------------------
//  Headers
//--------------------------------------------------------------------------------------------

#include "Matrix4.hpp"

//--------------------------------------------------------------------------------------------
//  Use our library namespace: TRACTION_DEMOTRACTOR
//--------------------------------------------------------------------------------------------

using namespace TRACTION_DEMOTRACTOR;

//--------------------------------------------------------------------------------------------
//  Class code
//--------------------------------------------------------------------------------------------

Matrix4::Matrix4()
{
	data[0][0]=0;
	data[0][1]=0;
	data[0][2]=0;
	data[0][3]=0;
	data[1][0]=0;
	data[1][1]=0;
	data[1][2]=0;
	data[1][3]=0;
	data[2][0]=0;
	data[2][1]=0;
	data[2][2]=0;
	data[2][3]=0;
	data[3][0]=0;
	data[3][1]=0;
	data[3][2]=0;
	data[3][3]=0;
}

Matrix4::Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, 
			   float m9, float m10, float m11, float m12, float m13, float m14, float m15)
{
	data[0][0]=m0;
	data[0][1]=m1;
	data[0][2]=m2;
	data[0][3]=m3;
	data[1][0]=m4;
	data[1][1]=m5;
	data[1][2]=m6;
	data[1][3]=m7;
	data[2][0]=m8;
	data[2][1]=m9;
	data[2][2]=m10;
	data[2][3]=m11;
	data[3][0]=m12;
	data[3][1]=m13;
	data[3][2]=m14;
	data[3][3]=m15;
}

Matrix4::Matrix4(float value)
{
	data[0][0] = value;
	data[0][1] = value;
	data[0][2] = value;
	data[0][3] = value;
	data[1][0] = value;
	data[1][1] = value;
	data[1][2] = value;
	data[1][3] = value;
	data[2][0] = value;
	data[2][1] = value;
	data[2][2] = value;
	data[2][3] = value;
	data[3][0] = value;
	data[3][1] = value;
	data[3][2] = value;
	data[3][3] = value;
}


Matrix4::~Matrix4()
{

}

Matrix4 Matrix4::makeIdentity()
{
	data[0][0]=1;
	data[0][1]=0;
	data[0][2]=0;
	data[0][3]=0;
	data[1][0]=0;
	data[1][1]=1;
	data[1][2]=0;
	data[1][3]=0;
	data[2][0]=0;
	data[2][1]=0;
	data[2][2]=1;
	data[2][3]=0;
	data[3][0]=0;
	data[3][1]=0;
	data[3][2]=0;
	data[3][3]=1;

	return Matrix4(data[0][0], data[0][1], data[0][2], data[0][3], 
					data[1][0], data[1][1], data[1][2], data[1][3], 
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]); 
}

Matrix4 Matrix4::makeTranspose()
{
	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

	t0 = data[0][0];
	t1 = data[0][1];
	t2 = data[0][2];
	t3 = data[0][3];
	t4 = data[1][0];
	t5 = data[1][1];
	t6 = data[1][2];
	t7 = data[1][3];
	t8 = data[2][0];
	t9 = data[2][1];
	t10 = data[2][2];
	t11 = data[2][3];
	t12 = data[3][0];
	t13 = data[3][1];
	t14 = data[3][2];
	t15 = data[3][3];

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

void Matrix4::operator = (Matrix4 const &mat)
{
	data[0][0]=mat.data[0][0];
	data[0][1]=mat.data[0][1];
	data[0][2]=mat.data[0][2];
	data[0][3]=mat.data[0][3];
	data[1][0]=mat.data[1][0];
	data[1][1]=mat.data[1][1];
	data[1][2]=mat.data[1][2];
	data[1][3]=mat.data[1][3];
	data[2][0]=mat.data[2][0];
	data[2][1]=mat.data[2][1];
	data[2][2]=mat.data[2][2];
	data[2][3]=mat.data[2][3];
	data[3][0]=mat.data[3][0];
	data[3][1]=mat.data[3][1];
	data[3][2]=mat.data[3][2];
	data[3][3]=mat.data[3][3];
}

void Matrix4::operator = (float const &value)
{
	data[0][0] = value;
	data[0][1] = value;
	data[0][2] = value;
	data[0][3] = value;
	data[1][0] = value;
	data[1][1] = value;
	data[1][2] = value;
	data[1][3] = value;
	data[2][0] = value;
	data[2][1] = value;
	data[2][2] = value;
	data[2][3] = value;
	data[3][0] = value;
	data[3][1] = value;
	data[3][2] = value;
	data[3][3] = value;
}

Matrix4 Matrix4::operator + (Matrix4 const &mat)
{
	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

	t0 = data[0][0] + mat.data[0][0];
	t1 = data[0][1] + mat.data[0][1];
	t2 = data[0][2] + mat.data[0][2];
	t3 = data[0][3] + mat.data[0][3];

	t4 = data[1][0] + mat.data[1][0];
	t5 = data[1][1] + mat.data[1][1];
	t6 = data[1][2] + mat.data[1][2];
	t7 = data[1][3] + mat.data[1][3];

	t8 = data[2][0] + mat.data[2][0];
	t9 = data[2][1] + mat.data[2][1];
	t10 = data[2][2] + mat.data[2][2];
	t11 = data[2][3] + mat.data[2][3];

	t12 = data[3][0] + mat.data[3][0];
	t13 = data[3][1] + mat.data[3][1];
	t14 = data[3][2] + mat.data[3][2];
	t15 = data[3][3] + mat.data[3][3];

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

Matrix4 Matrix4::operator += (Matrix4 const &mat)
{
	data[0][0]+=mat.data[0][0];
	data[0][1]+=mat.data[0][1];
	data[0][2]+=mat.data[0][2];
	data[0][3]+=mat.data[0][3];
	data[1][0]+=mat.data[1][0];
	data[1][1]+=mat.data[1][1];
	data[1][2]+=mat.data[1][2];
	data[1][3]+=mat.data[1][3];
	data[2][0]+=mat.data[2][0];
	data[2][1]+=mat.data[2][1];
	data[2][2]+=mat.data[2][2];
	data[2][3]+=mat.data[2][3];
	data[3][0]+=mat.data[3][0];
	data[3][1]+=mat.data[3][1];
	data[3][2]+=mat.data[3][2];
	data[3][3]+=mat.data[3][3];

	return Matrix4(data[0][0], data[0][1], data[0][2], data[0][3], 
					data[1][0], data[1][1], data[1][2], data[1][3], 
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]); 
	 
}

Matrix4 Matrix4::operator - (Matrix4 const &mat)
{
	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

	t0 = data[0][0] - mat.data[0][0];
	t1 = data[0][1] - mat.data[0][1];
	t2 = data[0][2] - mat.data[0][2];
	t3 = data[0][3] - mat.data[0][3];
	t4 = data[1][0] - mat.data[1][0];
	t5 = data[1][1] - mat.data[1][1];
	t6 = data[1][2] - mat.data[1][2];
	t7 = data[1][3] - mat.data[1][3];
	t8 = data[2][0] - mat.data[2][0];
	t9 = data[2][1] - mat.data[2][1];
	t10 = data[2][2] - mat.data[2][2];
	t11 = data[2][3] - mat.data[2][3];
	t12 = data[3][0] - mat.data[3][0];
	t13 = data[3][1] - mat.data[3][1];
	t14 = data[3][2] - mat.data[3][2];
	t15 = data[3][3] - mat.data[3][3];

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

Matrix4 Matrix4::operator -= (Matrix4 const &mat)
{
	data[0][0]-=mat.data[0][0];
	data[0][1]-=mat.data[0][1];
	data[0][2]-=mat.data[0][2];
	data[0][3]-=mat.data[0][3];
	data[1][0]-=mat.data[1][0];
	data[1][1]-=mat.data[1][1];
	data[1][2]-=mat.data[1][2];
	data[1][3]-=mat.data[1][3];
	data[2][0]-=mat.data[2][0];
	data[2][1]-=mat.data[2][1];
	data[2][2]-=mat.data[2][2];
	data[2][3]-=mat.data[2][3];
	data[3][0]-=mat.data[3][0];
	data[3][1]-=mat.data[3][1];
	data[3][2]-=mat.data[3][2];
	data[3][3]-=mat.data[3][3];

	return Matrix4(data[0][0], data[0][1], data[0][2], data[0][3], 
					data[1][0], data[1][1], data[1][2], data[1][3], 
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]); 

}

Matrix4 Matrix4::operator * (Matrix4 const &mat)
{
	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

		t0 = data[0][0] * mat.data[0][0] + data[0][1] * mat.data[1][0] + data[0][2] * mat.data[2][0] + data[0][3] * mat.data[3][0];
		t1 = data[0][0] * mat.data[0][1] + data[0][1] * mat.data[1][1] + data[0][2] * mat.data[2][1] + data[0][3] * mat.data[3][1];
		t2 = data[0][0] * mat.data[0][2] + data[0][1] * mat.data[1][2] + data[0][2] * mat.data[2][2] + data[0][3] * mat.data[3][2];
		t3 = data[0][0] * mat.data[0][3] + data[0][1] * mat.data[1][3] + data[0][2] * mat.data[2][3] + data[0][3] * mat.data[3][3];
		 
		t4 = data[1][0] * mat.data[0][0] + data[1][1] * mat.data[1][0] + data[1][2] * mat.data[2][0] + data[1][3] * mat.data[3][0];
		t5 = data[1][0] * mat.data[0][1] + data[1][1] * mat.data[1][1] + data[1][2] * mat.data[2][1] + data[1][3] * mat.data[3][1];
		t6 = data[1][0] * mat.data[0][2] + data[1][1] * mat.data[1][2] + data[1][2] * mat.data[2][2] + data[1][3] * mat.data[3][2];
		t7 = data[1][0] * mat.data[0][3] + data[1][1] * mat.data[1][3] + data[1][2] * mat.data[2][3] + data[1][3] * mat.data[3][3];
		 
		t8 = data[2][0] * mat.data[0][0] + data[2][1] * mat.data[1][0] + data[2][2] * mat.data[2][0] + data[2][3] * mat.data[3][0];
		t9 = data[2][0] * mat.data[0][1] + data[2][1] * mat.data[1][1] + data[2][2] * mat.data[2][1] + data[2][3] * mat.data[3][1];
		t10 = data[2][0] * mat.data[0][2] + data[2][1] * mat.data[1][2] + data[2][2] * mat.data[2][2] + data[2][3] * mat.data[3][2];
		t11 = data[2][0] * mat.data[0][3] + data[2][1] * mat.data[1][3] + data[2][2] * mat.data[2][3] + data[2][3] * mat.data[3][3];
		 
		t12 = data[3][0] * mat.data[0][0] + data[3][1] * mat.data[1][0] + data[3][2] * mat.data[2][0] + data[3][3] * mat.data[3][0];
		t13 = data[3][0] * mat.data[0][1] + data[3][1] * mat.data[1][1] + data[3][2] * mat.data[2][1] + data[3][3] * mat.data[3][1];
		t14 = data[3][0] * mat.data[0][2] + data[3][1] * mat.data[1][2] + data[3][2] * mat.data[2][2] + data[3][3] * mat.data[3][2];
		t15 = data[3][0] * mat.data[0][3] + data[3][1] * mat.data[1][3] + data[3][2] * mat.data[2][3] + data[3][3] * mat.data[3][3];

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

Matrix4 Matrix4::operator *= (Matrix4 const &mat)
{

	return Matrix4(
		data[0][0] * mat.data[0][0] + data[0][1] * mat.data[1][0] + data[0][2] * mat.data[2][0] + data[0][3] * mat.data[3][0],
		data[0][0] * mat.data[0][1] + data[0][1] * mat.data[1][1] + data[0][2] * mat.data[2][1] + data[0][3] * mat.data[3][1],
		data[0][0] * mat.data[0][2] + data[0][1] * mat.data[1][2] + data[0][2] * mat.data[2][2] + data[0][3] * mat.data[3][2],
		data[0][0] * mat.data[0][3] + data[0][1] * mat.data[1][3] + data[0][2] * mat.data[2][3] + data[0][3] * mat.data[3][3],
		 
		data[1][0] * mat.data[0][0] + data[1][1] * mat.data[1][0] + data[1][2] * mat.data[2][0] + data[1][3] * mat.data[3][0],
		data[1][0] * mat.data[0][1] + data[1][1] * mat.data[1][1] + data[1][2] * mat.data[2][1] + data[1][3] * mat.data[3][1],
		data[1][0] * mat.data[0][2] + data[1][1] * mat.data[1][2] + data[1][2] * mat.data[2][2] + data[1][3] * mat.data[3][2],
		data[1][0] * mat.data[0][3] + data[1][1] * mat.data[1][3] + data[1][2] * mat.data[2][3] + data[1][3] * mat.data[3][3],
		 
		data[2][0] * mat.data[0][0] + data[2][1] * mat.data[1][0] + data[2][2] * mat.data[2][0] + data[2][3] * mat.data[3][0],
		data[2][0] * mat.data[0][1] + data[2][1] * mat.data[1][1] + data[2][2] * mat.data[2][1] + data[2][3] * mat.data[3][1],
		data[2][0] * mat.data[0][2] + data[2][1] * mat.data[1][2] + data[2][2] * mat.data[2][2] + data[2][3] * mat.data[3][2],
		data[2][0] * mat.data[0][3] + data[2][1] * mat.data[1][3] + data[2][2] * mat.data[2][3] + data[2][3] * mat.data[3][3],
		 
		data[3][0] * mat.data[0][0] + data[3][1] * mat.data[1][0] + data[3][2] * mat.data[2][0] + data[3][3] * mat.data[3][0],
		data[3][0] * mat.data[0][1] + data[3][1] * mat.data[1][1] + data[3][2] * mat.data[2][1] + data[3][3] * mat.data[3][1],
		data[3][0] * mat.data[0][2] + data[3][1] * mat.data[1][2] + data[3][2] * mat.data[2][2] + data[3][3] * mat.data[3][2],
		data[3][0] * mat.data[0][3] + data[3][1] * mat.data[1][3] + data[3][2] * mat.data[2][3] + data[3][3] * mat.data[3][3] 
	 );

}

Matrix4 Matrix4::operator * (float const &value)
{
	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

	t0 = data[0][0] * value;
	t1 = data[0][1] * value;
	t2 = data[0][2] * value;
	t3 = data[0][3] * value;
	t4 = data[1][0] * value;
	t5 = data[1][1] * value;
	t6 = data[1][2] * value;
	t7 = data[1][3] * value;
	t8 = data[2][0] * value;
	t9 = data[2][1] * value;
	t10 = data[2][2] * value;
	t11 = data[2][3] * value;
	t12 = data[3][0] * value;
	t13 = data[3][1] * value;
	t14 = data[3][2] * value;
	t15 = data[3][3] * value;

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}

Matrix4 Matrix4::operator *= (float const &value)
{
	data[0][0] *= value;
	data[0][1] *= value;
	data[0][2] *= value;
	data[0][3] *= value;
	data[1][0] *= value;
	data[1][1] *= value;
	data[1][2] *= value;
	data[1][3] *= value;
	data[2][0] *= value;
	data[2][1] *= value;
	data[2][2] *= value;
	data[2][3] *= value;
	data[3][0] *= value;
	data[3][1] *= value;
	data[3][2] *= value;
	data[3][3] *= value;

	return Matrix4(data[0][0], data[0][1], data[0][2], data[0][3], 
					data[1][0], data[1][1], data[1][2], data[1][3], 
					data[2][0], data[2][1], data[2][2], data[2][3],
					data[3][0], data[3][1], data[3][2], data[3][3]); 
}

bool Matrix4::operator == (Matrix4 const &mat)
{
	if (data[0][0] == mat.data[0][0] &&
		data[0][1] == mat.data[0][1] &&
		data[0][2] == mat.data[0][2] &&
		data[0][3] == mat.data[0][3] &&
		data[1][0] == mat.data[1][0] &&
		data[1][1] == mat.data[1][1] &&
		data[1][2] == mat.data[1][2] &&
		data[1][3] == mat.data[1][3] &&
		data[2][0] == mat.data[2][0] &&
		data[2][1] == mat.data[2][1] &&
		data[2][2] == mat.data[2][2] &&
		data[2][3] == mat.data[2][3] && 
		data[3][0] == mat.data[3][0] &&
		data[3][1] == mat.data[3][1] &&
		data[3][2] == mat.data[3][2] &&
		data[3][3] == mat.data[3][3] )

		return true;
	else return false;
}

void Matrix4::getGL(float *array)
{
	array[ 0] = data[0][0];
	array[ 1] = data[1][0];
	array[ 2] = data[2][0];
	array[ 3] = data[3][0];
	array[ 4] = data[0][1];
	array[ 5] = data[1][1];
	array[ 6] = data[2][1];
	array[ 7] = data[3][1];
	array[ 8] = data[0][2];
	array[ 9] = data[1][2];
	array[10] = data[2][2];
	array[11] = data[3][2];
	array[12] = data[0][3];
	array[13] = data[1][3];
	array[14] = data[2][3];
	array[15] = data[3][3];
}

// create projection matrix [cut+paste]
Matrix4 Matrix4::makeProjection(float fovy, float ar, float zNear, float zFar)
{
	const float PII = 3.14159f;
	float fmn = zFar - zNear;
	float angle = fovy * 0.5f * PII / 180.0f;
	float ca = cosf(angle);
	float sa = sinf(angle);
	float f;
	if(sa == 0.0f)
		f = 0.0f;
	else
		f = ca / sa;


	float t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13,t14,t15;

	// first row:
	if(ar != 0.0) {
		t0 = f / ar;
		t1 = 0.0f;
		t2 = 0.0f;
		t3 = 0.0f;
	}
	else
		//data[0][0] = data[0][1] = data[0][2] = data[0][3] = 0.0;
		t0=t1=t2=t3=0;

	// second row:
	t4 = 0.0;
	t5 = f;
	t6 = 0.0;
	t7 = 0.0;

	// third row:
	if(fmn != 0.0) {
		float fmn_inv = 1.0f / fmn;
		t8  = 0.0f;
		t9  = 0.0f;
		t10 = -(zFar+zNear) * fmn_inv;
		t11 = 2.0f * zFar * zNear * fmn_inv;
	}
	else
		t8=t9=t10=t11 = 0.0f;

	t12 = t13 = t15 = 0.0f;
	t14 = -1.0f;

	return Matrix4(t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15);
}