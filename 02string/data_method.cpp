// gcc -std=c++17 -o data_method data_method.cpp -lstdc++
// gcc -std=c++14 -o data_method data_method.cpp -lstdc++ 에서는 에러

#include <string>
#include <iostream>

int main()
{
	std::string str = "hello";
	char *p = str.data();
	p[0] = 'H';
	std::cout << str << '\n'; // Hello

	return 0;
}
