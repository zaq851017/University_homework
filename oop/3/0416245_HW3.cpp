#include<iostream>
#include<string>
#include<string.h>
using namespace std;
template<class T>
void sortNumber(T A[],int n)
{
    T temp;
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-1;j++)
        {
            if(A[j]>A[j+1])
            {
                temp=A[j];
                A[j]=A[j+1];
                A[j+1]=temp;
            }
        }
    }

}
class HugeInteger
{
public:
	HugeInteger();
	friend ostream &operator<<( ostream& , const HugeInteger &);
	HugeInteger(char * );
	void setValue( char *);
 	HugeInteger& operator =  (const HugeInteger &);
 	bool operator > ( const HugeInteger &);
private:
	char *val;
};

ostream &operator<< (ostream & output , const HugeInteger & huge)
{
	output << huge.val;
	return output;
}
HugeInteger& HugeInteger::operator =  (const HugeInteger &H)
{
	this->val=H.val;
	return *this;
}

HugeInteger::HugeInteger()
{
    this->val=0;
}
HugeInteger::HugeInteger( char *input)
{
    setValue(input);
}

void HugeInteger::setValue( char *input)
{
	this->val=input;
}

bool HugeInteger::operator > ( const HugeInteger &H)
{
	string str1,str2;
	str1=this->val;
	str2=H.val;

	if (strlen(this->val)>strlen(H.val))return true;
	else if(strlen(this->val)<strlen(H.val)) return false ;
	else if(str1>str2)return true;
	else return false;
}
int main()
{
	// integer
	int val[10] = {11 , 32 , 5 , 8 , 2 , 10 , 23 , 87 , 12 , 2};
	sortNumber(val , 10);

	for (int i = 0 ; i < 10 ; i++)
		cout << val[i] << " ";

	cout << endl;

	// Huge integer
	HugeInteger huge[6] = {"12087" , "1389" , "99783" , "870843" , "3338765" , "93673"};
	sortNumber(huge , 6);

	for (int i = 0 ; i < 6 ; i++)
		cout << huge[i] << " ";

	cout << endl;
	return 0;
	// other unknown fundamental types, will be given by TA after your codes are uploaded

}
