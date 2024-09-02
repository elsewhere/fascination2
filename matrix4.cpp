#include "matrix4.hpp"

Matrix4::Matrix4()
{
	memset(data, 0, 16*sizeof(float));
}

Matrix4::Matrix4(float m0, float m1, float m2, float m3, float m4, float m5, float m6, float m7, float m8, float m9, float m10, float m11, float m12, float m13, float m14, float m15)
{
	data[0]=m0;
	data[1]=m1;
	data[2]=m2;
	data[3]=m3;
	data[4]=m4;
	data[5]=m5;
	data[6]=m6;
	data[7]=m7;
	data[8]=m8;
	data[9]=m9;
	data[10]=m10;
	data[11]=m11;
	data[12]=m12;
	data[13]=m13;
	data[14]=m14;
	data[15]=m15;
}


Matrix4::Matrix4(float value)
{
	for(int i=0; i<16; i++)
		data[i] = value;
}

Matrix4::~Matrix4() {}


void Matrix4::operator = (Matrix4 const &mat)
{
	data[0]=mat.data[0];
	data[1]=mat.data[1];
	data[2]=mat.data[2];
	data[3]=mat.data[3];
	data[4]=mat.data[4];
	data[5]=mat.data[5];
	data[6]=mat.data[6];
	data[7]=mat.data[7];
	data[8]=mat.data[8];
	data[9]=mat.data[9];
	data[10]=mat.data[10];
	data[11]=mat.data[11];
	data[12]=mat.data[12];
	data[13]=mat.data[13];
	data[14]=mat.data[14];
	data[15]=mat.data[15];
}

void Matrix4::operator = (float const &value)
{
	data[0] = value;
	data[1] = value;
	data[2] = value;
	data[3] = value;
	data[4] = value;
	data[5] = value;
	data[6] = value;
	data[7] = value;
	data[8] = value;
	data[9] = value;
	data[10] = value;
	data[11] = value;
	data[12] = value;
	data[13] = value;
	data[14] = value;
	data[15] = value;
}



Matrix4 Matrix4::makeIdentity()
{
	memset(data, 0, 16*sizeof(float));
	data[0]=1.0f;
	data[5]=1.0f;
	data[10]=1.0f;
	data[15]=1.0f;
	
	// identity + transpose??? wtf :P - oh well - cutpasted & results in same matrix ;)
	return Matrix4(	data[ 0], data[ 4], data[ 8], data[12],
			data[ 1], data[ 5], data[ 9], data[13],
			data[ 2], data[ 6], data[10], data[14],
			data[ 3], data[ 7], data[11], data[15]);
}

Matrix4 Matrix4::makeTranspose()
{
	return Matrix4(	data[ 0], data[ 4], data[ 8], data[12],
			data[ 1], data[ 5], data[ 9], data[13],
			data[ 2], data[ 6], data[10], data[14],
			data[ 3], data[ 7], data[11], data[15]);
}


Matrix4 Matrix4::operator+(const Matrix4 & rhs)
{
	return Matrix4(	data[0]+rhs.data[0],
			data[1]+rhs.data[1],
			data[2]+rhs.data[2],
			data[3]+rhs.data[3],
			data[4]+rhs.data[4],
			data[5]+rhs.data[5],
			data[6]+rhs.data[6],
			data[7]+rhs.data[7],
			data[8]+rhs.data[8],
			data[9]+rhs.data[9],
			data[10]+rhs.data[10],
			data[11]+rhs.data[11],
			data[12]+rhs.data[12],
			data[13]+rhs.data[13],
			data[14]+rhs.data[14],
			data[15]+rhs.data[15]);
}

Matrix4 Matrix4::operator-(const Matrix4 & rhs)
{
	return Matrix4(	data[0]-rhs.data[0],
			data[1]-rhs.data[1],
			data[2]-rhs.data[2],
			data[3]-rhs.data[3],
			data[4]-rhs.data[4],
			data[5]-rhs.data[5],
			data[6]-rhs.data[6],
			data[7]-rhs.data[7],
			data[8]-rhs.data[8],
			data[9]-rhs.data[9],
			data[10]-rhs.data[10],
			data[11]-rhs.data[11],
			data[12]-rhs.data[12],
			data[13]-rhs.data[13],
			data[14]-rhs.data[14],
			data[15]-rhs.data[15]);
}

// This was copypasted from unknown source
// Kirjotin sen kerran ja vittu siel oli joku id väärin..
Matrix4 Matrix4::operator*(const Matrix4 & rhs)
{
	//Optimise for matrices in which bottom row is (0, 0, 0, 1) in both matrices
	if(	data[3]==0.0f && data[7]==0.0f && data[11]==0.0f && data[15]==1.0f &&
		rhs.data[3]==0.0f && rhs.data[7]==0.0f &&
		rhs.data[11]==0.0f && rhs.data[15]==1.0f)
	{
		return Matrix4(	data[0]*rhs.data[0]+data[4]*rhs.data[1]+data[8]*rhs.data[2],
							data[1]*rhs.data[0]+data[5]*rhs.data[1]+data[9]*rhs.data[2],
							data[2]*rhs.data[0]+data[6]*rhs.data[1]+data[10]*rhs.data[2],
							0.0f,
							data[0]*rhs.data[4]+data[4]*rhs.data[5]+data[8]*rhs.data[6],
							data[1]*rhs.data[4]+data[5]*rhs.data[5]+data[9]*rhs.data[6],
							data[2]*rhs.data[4]+data[6]*rhs.data[5]+data[10]*rhs.data[6],
							0.0f,
							data[0]*rhs.data[8]+data[4]*rhs.data[9]+data[8]*rhs.data[10],
							data[1]*rhs.data[8]+data[5]*rhs.data[9]+data[9]*rhs.data[10],
							data[2]*rhs.data[8]+data[6]*rhs.data[9]+data[10]*rhs.data[10],
							0.0f,
							data[0]*rhs.data[12]+data[4]*rhs.data[13]+data[8]*rhs.data[14]+data[12],
							data[1]*rhs.data[12]+data[5]*rhs.data[13]+data[9]*rhs.data[14]+data[13],
							data[2]*rhs.data[12]+data[6]*rhs.data[13]+data[10]*rhs.data[14]+data[14],
							1.0f);
	}

	//Optimise for when bottom row of 1st matrix is (0, 0, 0, 1)
	if(	data[3]==0.0f && data[7]==0.0f && data[11]==0.0f && data[15]==1.0f)
	{
		return Matrix4(	data[0]*rhs.data[0]+data[4]*rhs.data[1]+data[8]*rhs.data[2]+data[12]*rhs.data[3],
							data[1]*rhs.data[0]+data[5]*rhs.data[1]+data[9]*rhs.data[2]+data[13]*rhs.data[3],
							data[2]*rhs.data[0]+data[6]*rhs.data[1]+data[10]*rhs.data[2]+data[14]*rhs.data[3],
							rhs.data[3],
							data[0]*rhs.data[4]+data[4]*rhs.data[5]+data[8]*rhs.data[6]+data[12]*rhs.data[7],
							data[1]*rhs.data[4]+data[5]*rhs.data[5]+data[9]*rhs.data[6]+data[13]*rhs.data[7],
							data[2]*rhs.data[4]+data[6]*rhs.data[5]+data[10]*rhs.data[6]+data[14]*rhs.data[7],
							rhs.data[7],
							data[0]*rhs.data[8]+data[4]*rhs.data[9]+data[8]*rhs.data[10]+data[12]*rhs.data[11],
							data[1]*rhs.data[8]+data[5]*rhs.data[9]+data[9]*rhs.data[10]+data[13]*rhs.data[11],
							data[2]*rhs.data[8]+data[6]*rhs.data[9]+data[10]*rhs.data[10]+data[14]*rhs.data[11],
							rhs.data[11],
							data[0]*rhs.data[12]+data[4]*rhs.data[13]+data[8]*rhs.data[14]+data[12]*rhs.data[15],
							data[1]*rhs.data[12]+data[5]*rhs.data[13]+data[9]*rhs.data[14]+data[13]*rhs.data[15],
							data[2]*rhs.data[12]+data[6]*rhs.data[13]+data[10]*rhs.data[14]+data[14]*rhs.data[15],
							rhs.data[15]);
	}

	//Optimise for when bottom row of 2nd matrix is (0, 0, 0, 1)
	if(	rhs.data[3]==0.0f && rhs.data[7]==0.0f &&
		rhs.data[11]==0.0f && rhs.data[15]==1.0f)
	{
		return Matrix4(	data[0]*rhs.data[0]+data[4]*rhs.data[1]+data[8]*rhs.data[2],
							data[1]*rhs.data[0]+data[5]*rhs.data[1]+data[9]*rhs.data[2],
							data[2]*rhs.data[0]+data[6]*rhs.data[1]+data[10]*rhs.data[2],
							data[3]*rhs.data[0]+data[7]*rhs.data[1]+data[11]*rhs.data[2],
							data[0]*rhs.data[4]+data[4]*rhs.data[5]+data[8]*rhs.data[6],
							data[1]*rhs.data[4]+data[5]*rhs.data[5]+data[9]*rhs.data[6],
							data[2]*rhs.data[4]+data[6]*rhs.data[5]+data[10]*rhs.data[6],
							data[3]*rhs.data[4]+data[7]*rhs.data[5]+data[11]*rhs.data[6],
							data[0]*rhs.data[8]+data[4]*rhs.data[9]+data[8]*rhs.data[10],
							data[1]*rhs.data[8]+data[5]*rhs.data[9]+data[9]*rhs.data[10],
							data[2]*rhs.data[8]+data[6]*rhs.data[9]+data[10]*rhs.data[10],
							data[3]*rhs.data[8]+data[7]*rhs.data[9]+data[11]*rhs.data[10],
							data[0]*rhs.data[12]+data[4]*rhs.data[13]+data[8]*rhs.data[14]+data[12],
							data[1]*rhs.data[12]+data[5]*rhs.data[13]+data[9]*rhs.data[14]+data[13],
							data[2]*rhs.data[12]+data[6]*rhs.data[13]+data[10]*rhs.data[14]+data[14],
							data[3]*rhs.data[12]+data[7]*rhs.data[13]+data[11]*rhs.data[14]+data[15]);
	}	
	
	return Matrix4(	data[0]*rhs.data[0]+data[4]*rhs.data[1]+data[8]*rhs.data[2]+data[12]*rhs.data[3],
						data[1]*rhs.data[0]+data[5]*rhs.data[1]+data[9]*rhs.data[2]+data[13]*rhs.data[3],
						data[2]*rhs.data[0]+data[6]*rhs.data[1]+data[10]*rhs.data[2]+data[14]*rhs.data[3],
						data[3]*rhs.data[0]+data[7]*rhs.data[1]+data[11]*rhs.data[2]+data[15]*rhs.data[3],
						data[0]*rhs.data[4]+data[4]*rhs.data[5]+data[8]*rhs.data[6]+data[12]*rhs.data[7],
						data[1]*rhs.data[4]+data[5]*rhs.data[5]+data[9]*rhs.data[6]+data[13]*rhs.data[7],
						data[2]*rhs.data[4]+data[6]*rhs.data[5]+data[10]*rhs.data[6]+data[14]*rhs.data[7],
						data[3]*rhs.data[4]+data[7]*rhs.data[5]+data[11]*rhs.data[6]+data[15]*rhs.data[7],
						data[0]*rhs.data[8]+data[4]*rhs.data[9]+data[8]*rhs.data[10]+data[12]*rhs.data[11],
						data[1]*rhs.data[8]+data[5]*rhs.data[9]+data[9]*rhs.data[10]+data[13]*rhs.data[11],
						data[2]*rhs.data[8]+data[6]*rhs.data[9]+data[10]*rhs.data[10]+data[14]*rhs.data[11],
						data[3]*rhs.data[8]+data[7]*rhs.data[9]+data[11]*rhs.data[10]+data[15]*rhs.data[11],
						data[0]*rhs.data[12]+data[4]*rhs.data[13]+data[8]*rhs.data[14]+data[12]*rhs.data[15],
						data[1]*rhs.data[12]+data[5]*rhs.data[13]+data[9]*rhs.data[14]+data[13]*rhs.data[15],
						data[2]*rhs.data[12]+data[6]*rhs.data[13]+data[10]*rhs.data[14]+data[14]*rhs.data[15],
						data[3]*rhs.data[12]+data[7]*rhs.data[13]+data[11]*rhs.data[14]+data[15]*rhs.data[15]);
}

Matrix4 Matrix4::operator*(const float rhs) 
{
	return Matrix4(	data[0]*rhs,
			data[1]*rhs,
			data[2]*rhs,
			data[3]*rhs,
			data[4]*rhs,
			data[5]*rhs,
			data[6]*rhs,
			data[7]*rhs,
			data[8]*rhs,
			data[9]*rhs,
			data[10]*rhs,
			data[11]*rhs,
			data[12]*rhs,
			data[13]*rhs,
			data[14]*rhs,
			data[15]*rhs);
}

Matrix4 Matrix4::operator/(const float rhs) 
{
	if (rhs==0.0f || rhs==1.0f)
		return (*this);
		
	float temp=1/rhs;

	return (*this)*temp;
}

// blablalba
Matrix4 Matrix4::makeInverseTranspose(void)
{
	Matrix4 result;

	float tmp[12];
	float det;

	//calculate pairs for first 8 elements (cofactors)
	tmp[0] = data[10] * data[15];
	tmp[1] = data[11] * data[14];
	tmp[2] = data[9] * data[15];
	tmp[3] = data[11] * data[13];
	tmp[4] = data[9] * data[14];
	tmp[5] = data[10] * data[13];
	tmp[6] = data[8] * data[15];
	tmp[7] = data[11] * data[12];
	tmp[8] = data[8] * data[14];
	tmp[9] = data[10] * data[12];
	tmp[10] = data[8] * data[13];
	tmp[11] = data[9] * data[12];

	result.data[0]=	 tmp[0]*data[5] + tmp[3]*data[6] + tmp[4]*data[7]
				-tmp[1]*data[5] - tmp[2]*data[6] - tmp[5]*data[7];

	result.data[1]=		tmp[1]*data[4] + tmp[6]*data[6] + tmp[9]*data[7]
				-tmp[0]*data[4] - tmp[7]*data[6] - tmp[8]*data[7];

	result.data[2]=		tmp[2]*data[4] + tmp[7]*data[5] + tmp[10]*data[7]
				-tmp[3]*data[4] - tmp[6]*data[5] - tmp[11]*data[7];

	result.data[3]=		tmp[5]*data[4] + tmp[8]*data[5] + tmp[11]*data[6]
				-tmp[4]*data[4] - tmp[9]*data[5] - tmp[10]*data[6];

	result.data[4]=		tmp[1]*data[1] + tmp[2]*data[2] + tmp[5]*data[3]
				-tmp[0]*data[1] - tmp[3]*data[2] - tmp[4]*data[3];

	result.data[5]=		tmp[0]*data[0] + tmp[7]*data[2] + tmp[8]*data[3]
				-tmp[1]*data[0] - tmp[6]*data[2] - tmp[9]*data[3];

	result.data[6]=		tmp[3]*data[0] + tmp[6]*data[1] + tmp[11]*data[3]
				-tmp[2]*data[0] - tmp[7]*data[1] - tmp[10]*data[3];

	result.data[7] = 		tmp[4]*data[0] + tmp[9]*data[1] + tmp[10]*data[2]
				-tmp[5]*data[0] - tmp[8]*data[1] - tmp[11]*data[2];

	tmp[0] = data[2]*data[7];
	tmp[1] = data[3]*data[6];
	tmp[2] = data[1]*data[7];
	tmp[3] = data[3]*data[5];
	tmp[4] = data[1]*data[6];
	tmp[5] = data[2]*data[5];
	tmp[6] = data[0]*data[7];
	tmp[7] = data[3]*data[4];
	tmp[8] = data[0]*data[6];
	tmp[9] = data[2]*data[4];
	tmp[10] = data[0]*data[5];
	tmp[11] = data[1]*data[4];
	
	result.data[8]=		tmp[0]*data[13] + tmp[3]*data[14] + tmp[4]*data[15]
				-tmp[1]*data[13] - tmp[2]*data[14] - tmp[5]*data[15];
					
	result.data[9]=		tmp[1]*data[12] + tmp[6]*data[14] + tmp[9]*data[15]
				-tmp[0]*data[12] - tmp[7]*data[14] - tmp[8]*data[15];

	result.data[10]=		tmp[2]*data[12] + tmp[7]*data[13] + tmp[10]*data[15]
				-tmp[3]*data[12] - tmp[6]*data[13] - tmp[11]*data[15];

	result.data[11]=		tmp[5]*data[12] + tmp[8]*data[13] + tmp[11]*data[14]
				-tmp[4]*data[12] - tmp[9]*data[13] - tmp[10]*data[14];

	result.data[12]=		tmp[2]*data[10] + tmp[5]*data[11] + tmp[1]*data[9]
				-tmp[4]*data[11] - tmp[0]*data[9] - tmp[3]*data[10];

	result.data[13]=		tmp[8]*data[11] + tmp[0]*data[8] + tmp[7]*data[10]
				-tmp[6]*data[10] - tmp[9]*data[11] - tmp[1]*data[8];

	result.data[14]=		tmp[6]*data[9] + tmp[11]*data[11] + tmp[3]*data[8]
				-tmp[10]*data[11] - tmp[2]*data[8] - tmp[7]*data[9];

	result.data[15]=		tmp[10]*data[10] + tmp[4]*data[8] + tmp[9]*data[9]
				-tmp[8]*data[9] - tmp[11]*data[10] - tmp[5]*data[8];

	// calculate determinant
	det	=	 data[0]*result.data[0]
			+data[1]*result.data[1]
			+data[2]*result.data[2]
			+data[3]*result.data[3];

	if(det==0.0f)
	{
		Matrix4 id;
		return id;
	}
	
	result=result/det;

	return result;
}
