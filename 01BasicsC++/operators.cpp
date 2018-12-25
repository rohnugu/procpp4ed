#include <iostream>

using namespace std;

int main()
{
	int someInteger = 256;
	short someShort;
	long someLong;
	float someFloat;
	double someDouble;

	someInteger++;
	cout << "someInteger++; " << someInteger << endl;
	someInteger *= 2;
	cout << "someInteger * 2; " << someInteger << endl;
	someShort = static_cast<short>(someInteger);
	cout << "someShort = static_cast<short>(someInteger); " << someShort << endl;
	someLong = someShort * 10000;
	cout << "someLong = someShort * 10000; " << someLong << endl;
	someFloat = someLong + 0.785f;
	cout << "someFloat = someLong + 0.785f; " << someFloat << endl;
	someDouble = static_cast<double>(someFloat) / 100000;
	cout << "someDouble = static_cast<double>(someFloat) / 100000; " << someDouble << endl;
	cout << someDouble << endl;
	
	return 0;
}
