#ifndef _MATRIX33_H_
#define _MATRIX33_H_
#include "0416245_vector3.h"
class matrix33 
{  
public:
	vector3 col[3];
	matrix33() {};
	
	// constructor with initializing float values
	matrix33(const matrix33 &m);
	
	// constructor with initializing vector3
	matrix33(const vector3 &v1,const vector3 &v2,const vector3 &v3);
	public:
	vector3 &operator [] (unsigned int index);
	const vector3 &operator [] (unsigned int index) const;
	
	matrix33 &operator =  (const matrix33 &m);
	matrix33 &operator += (const matrix33 &m);
	matrix33 &operator -= (const matrix33 &m);
	matrix33 &operator *= (const matrix33 &m);
	matrix33 &operator *= (float f);
	matrix33 &operator /= (float f);
	friend bool operator == (const matrix33 &a, const matrix33 &b);
	friend bool operator != (const matrix33 &a, const matrix33 &b);
	friend matrix33 operator + (const matrix33 &a, const matrix33 &b);
	friend matrix33 operator - (const matrix33 &a, const matrix33 &b);
	friend matrix33 operator * (const matrix33 &a, const matrix33 &b);
	friend matrix33 operator * (const matrix33 &v, float f);
	friend vector3  operator * (const matrix33 &m,const vector3 &v);
	friend matrix33 operator * (float f, const matrix33 &v);
	friend matrix33 operator / (const matrix33 &m, float f);
	public:
	void printMatrix();
	matrix33 invert();
	float determinant(); 
	matrix33 identity();
	matrix33 transport();
	
	
};

#endif
