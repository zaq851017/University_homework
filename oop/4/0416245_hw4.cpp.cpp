//! Homework #4

#include <iostream>
#include <stdexcept>

using namespace std;

///////////////////////////////////////////////////////
// IMPLEMENT THE AUTO_ARRAY CLASS BELOW THIS LINE !! //
///////////////////////////////////////////////////////

template <typename T>
class auto_array
{
    private:
		int idx;
		int size;
		T* ptr;

    public:
        auto_array(int x,int y)
        {
            idx=x;
            size=y;
            ptr=new T[0];
        }
        ~auto_array()
        {
            cout << "Array #"<<idx<<" has been automatically deleted.\n";
            delete [] ptr;
        }
        T& operator [] (int i)
        {
            if(i<0||i>(size-1))
            {
                throw out_of_range("Exception: out of range!");
            }
            else{ return ptr[i];}

        }

};

////////////////////////////////////////////////////
// YOU CANNOT MODIFY ANY CODE BELOW THIS LINE !!  //
////////////////////////////////////////////////////

int main ()
{
	//////////////////////////////////////////////////////////////////////////////
	// Test 1                                                                   //
	//////////////////////////////////////////////////////////////////////////////

	// Auto_array #1
	// auto_array(int idx, int size)
	// idx  = user-specified identifier for auto_array objects
	// size = array size
	auto_array<int> x(1, 10);
	for (int i = 0 ; i < 10 ; i++)
	{
		x[i] = i * i;
		cout << x[i] << " ";
	}
	cout << endl;

	//////////////////////////////////////////////////////////////////////////////
	// Test 2                                                                   //
	//////////////////////////////////////////////////////////////////////////////

	// Error test
	// You need to use exception handling mechanism to print out "Exception: out of range!"
	try
	{
		cout << x[20] << endl;
	}
	catch (out_of_range &e)
	{
		cout << e.what() << endl;
	}

	//////////////////////////////////////////////////////////////////////////////
	// Test 3                                                                   //
	//////////////////////////////////////////////////////////////////////////////

	// Auto_array #2
	for(int iter=0; iter<3; iter++)
	{
		auto_array<int> y(2, 5);
		for (int i = 0 ; i < 5 ; i++)
		{
			y[i] = i * i;
			cout << y[i] << " ";
		}
		cout << endl;

		// You need to print "Array #idx has been automatically deleted." after release the auto_array variables
	}

	//////////////////////////////////////////////////////////////////////////////
	// Test 4                                                                   //
	//////////////////////////////////////////////////////////////////////////////

	// Auto_array #3
	int usr_sz;
	cout << "Give me array size: ";
	cin >> usr_sz;
	auto_array<double> z(3, usr_sz);
	for (int i = 0 ; i < usr_sz ; i++)
	{
		z[i] = i + 10.5;
		cout << z[i] << " ";
	}
	cout << endl;

	//////////////////////////////////////////////////////////////////////////////
	// Test 5                                                                   //
	//////////////////////////////////////////////////////////////////////////////

	// You need to print "Array #idx has been automatically deleted." after release the auto_array variables

	return 0;
}
