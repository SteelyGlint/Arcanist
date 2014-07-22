#include <iostream>
#include <typeinfo>
#include <limits>
#define HEADER_ONLY
#include "Vector.hpp"

#include <type_traits>

using namespace std;

template<typename T>
void print_info(T t);

template<typename T>
void print_info(Vector2D<T> vec)
{
	cout << "Vector<" << typeid(T).name() << "> = " << vec.x << 'x' <<vec.y << endl;
};


template<typename T>
void print_info(T val)
{
	cout << "Value " << typeid(T).name() << " = " << val << endl;
}

int main(int argc, char *argv[])
{
	Vector2D<int> d{1,1};
	int i_val = 3;
	float f_val = 3.0;
	double d_val = 9.0;

	print_info(d);
	print_info(i_val);
	print_info(d * i_val);
	print_info(d += i_val);

	print_info(d);
	print_info(f_val);
	print_info(Vector2D<float>(d * f_val));

	Vector2D<double> d2{2.63,6.34};
	print_info(d2);
	print_info(d2+=d);


	Vector2D<float> d3{9.63,12.34};
	print_info(d3);
	print_info(d2 - d3);

	print_info(d2*0);

	Vector2D<int> v_int{4,5};

	print_info(v_int);
	print_info(v_int.length());
}
