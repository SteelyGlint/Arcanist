#include <iostream>
#include <typeinfo>
#include <limits>
#include "Vector.hpp"

#include <type_traits>

static_assert( std::is_arithmetic<int>::value, "yes?");

using namespace std;

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

int main()
{
	Vector2D<int> d{1,1};
	float i_val = 3.03;

	print_info(d);
	print_info(i_val);
	print_info(d * i_val);
	print_info(d += i_val);


	Vector2D<double> d2{2.63,6.34};
	print_info(d2);
	print_info(d+d2);


	Vector2D<float> d3{9.63,12.34};
	print_info(d3);
	print_info(d3 -= d2);

	print_info(d2*0);

	Vector2D<int> v_int{4,5};

	print_info(v_int);
	print_info(v_int.length());
}
