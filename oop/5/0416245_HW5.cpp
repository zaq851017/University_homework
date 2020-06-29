#include<iostream>
#include<algorithm>
#include<fstream>
#include<math.h>
#include<list>
#include<vector>
#include<iterator>

using namespace std;
class vector3
{
    public:
	vector3(float inX, float inY, float inZ);
	vector3(const vector3 &v);
	vector3               &operator =  (const vector3 &v);
	vector3               &operator += (const vector3 &v);
	vector3               &operator /= (float f);
	friend bool           operator == (const vector3 &a, const vector3 &b);
	friend bool           operator != (const vector3 &a, const vector3 &b);
    void set(float xIn, float yIn, float zIn);
    void print() const;
    float x, y, z;
    vector3()
	{
	    x=0;
        y=0;
        z=0;
    };
};
vector3::vector3(float inputX, float inputY, float inputZ)
{
	x=inputX;
	y=inputY;
	z=inputZ;
}
vector3::vector3(const vector3 &vec)
{
	x=vec.x;
	y=vec.y;
	z=vec.z;
}
	vector3 &vector3::operator =  (const vector3 &v)
	{
		x=v.x;
		y=v.y;
		z=v.z;
		return *this;
	}
	vector3 &vector3::operator += (const vector3 &v)
	{
		x+=v.x;
		y+=v.y;
		z+=v.z;
		return *this;
	}
	vector3 &vector3::operator /= (float f)
	{
			x/=f;
			y/=f;
			z/=f;
			return *this;
	}
	bool operator == (const vector3 &a, const vector3 &b)
	{
	if(a.x==b.x&&a.y==b.y&&a.z==b.z)
    {
        return true;
    }
	else
	return false;
	}
	bool operator != (const vector3 &a, const vector3 &b)
	{
		return !(&a==&b);
	}
	 void vector3::set(float xIn, float yIn, float zIn)
	 {
	 	x=xIn;
	 	y=yIn;
	 	z=zIn;
	 }
	 void vector3::print() const
	 {
	 	cout<<"("<<x<<" , "<<y<<" , "<<z<<")";
	 }
class vector2
{
	public:
	vector2(float inx,float iny);
	vector2       &operator += (const vector2 &v);
	vector2       &operator -= (const vector2 &v);
    vector2       &operator /= (float f);
    vector2       &operator =  (const vector2 &v);
    void set(float xIn, float yIn);
    void set(float xIn, float yIn,float zIn);
    void print();
    float x,y,z;
	vector2() {x=0;y=0;z=0;};

};
void vector2::set(float xInput, float yInput,float zInput)
{
		x=xInput;
		y=yInput;
		zInput=0;
}
vector2::vector2(float xInput, float yInput)
{
	x=xInput;
	y=yInput;
}
bool operator != (const vector2 &a, const vector2 &b)
	{
		if(a.x!=b.x||a.y!=b.y)
		return true;
		else
		return false;
	}
vector2 operator / (const vector2 &vec, float f)
	{
		return vector2(vec.x/f,vec.y/f);
	}
	vector2 &vector2::operator =  (const vector2 &vec)
	{
		x=vec.x;
		y=vec.y;
		return *this;
	}
	vector2 &vector2::operator += (const vector2 &vec)
	{
		x=x+vec.x;
		y=y+vec.y;
		return *this;
	}
	vector2 &vector2::operator -= (const vector2 &vec)
	{
			x=x-vec.x;
			y=y-vec.y;
			return *this;
	}
	vector2 operator + (const vector2 &a, const vector2 &b)
	{
		return vector2((a.x+b.x),(a.y+b.y));
	}
vector2 &vector2::operator /= (float f)
    {
			x=(x/f);
			y=(y/f);
			return *this;
	}
	 void vector2::set(float xInput,float yInput)
	 {
	 	x=xInput;
	 	y=yInput;
	 }
	 void vector2::print()
	 {
	 	cout<<"("<<x<<" , "<<y<<")";
	 }

template<typename t,typename t1>
void GetCenter(t begin,t end,t1 &r)
{
	cout<<"The center of the list is ";
	float n=0;
	t i;t1 ave;
	for(i=begin;i!=end;i++)
	{
		++n;
        ave+=*i;
	}
    ave/=n;
    r=ave;
    r.print();
}
template<typename t,typename t1>
void BoundingBox(t x1,t x2,t1 &small,t1 &big)
{
	float a=(*x1).x,b=(*x1).y,c=(*x1).z;
	float a1=(*x1).x,b1=(*x1).y,c1=(*x1).z;
		for(t i=x1;i!=x2;i++)
		{
			if((*i).x<a)
			a=(*i).x;
			if((*i).x>a1)
			a1=(*i).x;
			if((*i).y<b)
			b=(*i).y;
			if((*i).y>b1)
			b1=(*i).y;
			if((*i).z<c)
			c=(*i).z;
			if((*i).z>c1)
			c1=(*i).z;
		}
	small.set(a,b,c);
	big.set(a1,b1,c1);
	cout<<endl<<"The bounding box of the list is";
		small.print();cout<<" - ";big.print();
}
template<class t>
void printdata(t s,t e)
{
    for(t i= s; i!= e; i++)
    {
        (*i).print();
        cout<<endl;
    }

}

int main()
{
	list<vector2> x1;
	list<vector3> x2;
	vector<vector2> v1;
	vector<vector3> v2;
	vector2 v;
	vector3 l3;
	fstream fin;
	char line[20];
    fin.open("input.txt",ios::in);
    if(!fin)
    {
    	cout<<"Error opening file";
    	return -1;// error <---
	}
    float x,y,z=0;int ist=0;
    while(fin.getline(line,sizeof(line),'\n')){
    	int p=0;
        if(line[0] =='(')
        {

            for(int i=1;line[i]!=')';i++)
            {
            	if(line[i]>=48&&line[i]<=57)
            	{
            		if(p==0)
                    {
                        x=line[i]-48;
                    }

            		else if(p==1)
                    {
                        y=line[i]-48;
                    }

            		else if(p==2)
                    {
                        z=line[i]-48;
                    }
            		p++;
				}
			}
			switch(ist)
			{
			    case 0:
				v.set(x,y);
                x1.push_back(v);
                break;
                case 1:
				l3.set(x,y,z);
				x2.push_back(l3);
				break;
                case 2:
				v.set(x,y);
                v1.push_back(v);
                break;
                case 3:
                l3.set(x,y,z);
				v2.push_back(l3);
				break;
			}

        }
        else
        {
            ist++;
        }
    }
	vector2 r2 , b2;
	vector3 r3 , b3;
    printdata(x1.begin() , x1.end());
    cout<<"\n";
	GetCenter(x1.begin() , x1.end() , r2);
	BoundingBox(x1.begin() , x1.end() , r2 , b2);
    cout<<"\n"<<"\n";
    printdata(x2.begin() , x2.end());
    cout<<"\n";
	GetCenter(x2.begin() , x2.end() , r3);
	BoundingBox(x2.begin() , x2.end() , r3 , b3);
    cout<<"\n"<<"\n";
    printdata(v1.begin() , v1.end());
    cout<<"\n";
	GetCenter(v1.begin() , v1.end() , r2);
	BoundingBox(v1.begin() , v1.end() , r2 , b2);
    cout<<"\n"<<"\n";
    printdata(v2.begin() , v2.end());
    cout<<"\n";
	GetCenter(v2.begin() , v2.end() , r3);
	BoundingBox(v2.begin() , v2.end() , r3 , b3);
    cout<<"\n";
}
