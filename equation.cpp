#include <iostream>
#include <math.h>
#include <vector>

template <class Type>
class Equation
{
public:

	const Type a = 0;
	const Type b = 0;
	const Type c = 0;
	Type k1 = 0;
	Type k2 = 0;

	Equation(Type aa, Type bb, Type cc)
		: a(aa), b(bb), c(cc)
	{
		if ((b * b - 4 * a * c) < 0)
		{
			k1 = std::nan("1");
			k1 = std::nan("1");
		}
		else
		{
			k1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
			k2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		}
	}

	friend std::ostream& operator<< (std::ostream& strm, const Equation& eq)
	{
		std::cout << "(" << eq.a << ") * x^2 + (" << eq.b << ") * x + (" << eq.c << ") = 0" << std::endl;
		std::cout << "k1 = " << eq.k1 << std::endl;
		std::cout << "k2 = " << eq.k2 << std::endl << std::endl;
		return strm;
	}

	void Check(const Type num) const
	{
		if (num == k1)
		{
			std::cout << "k1 matches!" << std::endl;
		}
		else if (num == k2)
		{
			std::cout << "k2 matches!" << std::endl;
		}
		else
		{
			std::cout << "no matches!" << std::endl;
		}
	}
};


int main(void)
{
	Equation<double> EquDouble(1, -9, 20);
	Equation<float> EquFloat(1, 3, -10);
	std::cout << "templpate example: " << std::endl;

	std::cout << EquDouble;
	std::cout << EquFloat;

	std::vector<Equation<double>> EquationArray;

	Equation<double> EquDouble1(1, -9, 20);
	Equation<double> EquDouble2(1, -8, 15);
	Equation<double> EquDouble3(1, -3, 2);
	Equation<double> EquDouble4(1, -12, 36);
	Equation<double> EquDouble5(1, -10, 16);

	EquationArray.push_back(EquDouble1);
	EquationArray.push_back(EquDouble2);
	EquationArray.push_back(EquDouble3);
	EquationArray.push_back(EquDouble4);
	EquationArray.push_back(EquDouble5);

////////////////////////////////////////////////////////////////

	std::cout << "copy test" << std::endl;

	std::copy(EquationArray.begin(), EquationArray.end(),
		std::ostream_iterator<Equation<double>>(std::cout, " "));

	return 0;
}
