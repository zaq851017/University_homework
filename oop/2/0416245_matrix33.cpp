#include "0416245_matrix33.h"
#include<iostream>
using namespace std;

matrix33 matrix33::transport()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			float temp;
    		temp=col[i][j];
    		col[i][j]=col[j][i];
    		col[j][i]=temp;
		}
	}	
	return *this;
} 

matrix33::matrix33(const matrix33 &m)
{
	for(int i=0;i<3;i++)
	col[i]=m.col[i];
}

matrix33::matrix33(const vector3 &v1,const vector3 &v2,const vector3 &v3)
{
	col[0]=v1;
	col[1]=v2;
	col[2]=v3;
}

vector3 &matrix33::operator [] (unsigned int index)
{
	return col[index];	
}

const vector3 &matrix33::operator [] (unsigned int index) const
{
	return col[index];
}

matrix33 &matrix33::operator =  (const matrix33 &m)
{
	for(int i=0;i<3;i++)
	col[i]=m.col[i];
	return *this;
}

matrix33 &matrix33::operator +=  (const matrix33 &m)
{
	for(int k=0;k<3;k++)
	col[k]+=m.col[k];
	return *this;
}

matrix33 &matrix33::operator -=  (const matrix33 &m)
{
	for(int k=0;k<3;k++)
	col[k]-=m.col[k];
	return *this;
}

matrix33 &matrix33::operator *= (const matrix33 &m)
{
	matrix33 MUL;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
			MUL.col[i][j]=0;
	}
	for(int i=0;i<3;i++) 
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				MUL.col[i][j]+=(m.col[i][k])*(this->col[k][j]);
			}
		}
	}
	(*this)=MUL;
	return *this;
}

matrix33 &matrix33::operator *= (float f)
{
	for(int i=0;i<3;i++)	col[i]*=f;
	return *this;
}

matrix33 &matrix33::operator /= (float f)
{
	for(int i=0;i<3;i++)	col[i]/=f;
	return *this;
}

bool  operator == (const matrix33 &a, const matrix33 &b)
{
	if(a.col[0]==b.col[0]&&a.col[1]==b.col[1]&&a.col[2]==b.col[2])
		return true;
	else 
		return false;	
}

bool  operator != (const matrix33 &a, const matrix33 &b)
{
	if(a.col[0]!=b.col[0]||a.col[1]!=b.col[1]||a.col[2]!=b.col[2])
		return true;
	else 
		return false;	
}

matrix33 operator + (const matrix33 &a, const matrix33 &b)
{
	return matrix33(a.col[0]+b.col[0],a.col[1]+b.col[1],a.col[2]+b.col[2]);
}

matrix33 operator - (const matrix33 &a, const matrix33 &b)
{
	return matrix33(a.col[0]-b.col[0],a.col[1]-b.col[1],a.col[2]-b.col[2]);
}

matrix33 operator * (const matrix33 &v, float f)
{
	return matrix33(v.col[0]*f,v.col[1]*f,v.col[2]*f);
}

matrix33  operator * (const matrix33 &a, const matrix33 &b)
{
	matrix33 MUL;
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		MUL.col[i][j]=0;
	}
	for(int i=0;i<3;i++)
	{
	for(int j=0;j<3;j++)
	{
		for(int k=0;k<3;k++)
		{
		MUL.col[i][j]+=a.col[k][j]*b.col[i][k];
		}
	}
	}
	return matrix33(MUL.col[0],MUL.col[1],MUL.col[2]);
}

vector3 operator * (const matrix33 &m,const vector3 &v)
{
	vector3 v1;
	v1.x=v.x*m.col[0][0]+v.y*m.col[1][0]+v.z*m.col[2][0];
	v1.y=v.x*m.col[1][0]+v.y*m.col[1][1]+v.z*m.col[1][2];
	v1.z=v.x*m.col[2][0]+v.y*m.col[2][1]+v.z*m.col[2][2];
	return vector3(v1.x,v1.y,v1.z);
}

matrix33 operator / (const matrix33 &m, float f)
{
	return matrix33(m.col[0]/f,m.col[1]/f,m.col[2]/f);
}

float matrix33::determinant()
{
	float Result1=0.0,Result2=0.0,Result=0.0;
	Result1=(col[0][0]*col[1][1]*col[2][2])+(col[0][1]*col[1][2]*col[2][0])+(col[0][2]*col[1][0]*col[2][1]);
	Result2=(col[0][2]*col[1][1]*col[2][0])+(col[2][2]*col[0][1]*col[1][0])+(col[0][0]*col[2][1]*col[1][2]);
	Result=Result1-Result2;
	return Result;
}

matrix33 matrix33::invert()
{
	float detA=0.0;
	matrix33 INVERT;
	detA=this->determinant();
	INVERT.col[0][0]=((col[1][1]*col[2][2])-(col[1][2]*col[2][1]))/detA;
	INVERT.col[1][0]=(-(col[1][0]*col[2][2])+(col[2][0]*col[1][2]))/detA;
	INVERT.col[2][0]=((col[1][0]*col[2][1])-(col[2][0]*col[1][1]))/detA;
	INVERT.col[0][1]=(-(col[0][1]*col[2][2])+(col[2][1]*col[0][2]))/detA;
	INVERT.col[1][1]=((col[0][0]*col[2][2])-(col[2][0]*col[0][2]))/detA;
	INVERT.col[2][1]=(-(col[0][0]*col[2][1])+(col[2][0]*col[0][1]))/detA;
	INVERT.col[0][2]=((col[0][1]*col[1][2])-(col[1][1]*col[0][2]))/detA;
	INVERT.col[1][2]=(-(col[0][0]*col[1][2])+(col[1][0]*col[0][2]))/detA;
	INVERT.col[2][2]=((col[0][0]*col[1][1])-(col[1][0]*col[0][1]))/detA;
	return matrix33(INVERT.col[0],INVERT.col[1],INVERT.col[2]);
}

matrix33 matrix33::identity()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(i==j)
			col[i][j]=1;
			else
			col[i][j]=0;
		}
	}
	return *this;
} 

void matrix33::printMatrix()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		cout<<col[j][i]<<" ";
		cout<<endl; 
	}
}
