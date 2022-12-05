#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <numeric>

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

//////////////////
template <typename T>
bool RootMatch(T input, const Equation<T>& eq)
{
	if (eq.k1 == input)
	{
		return true;
	}

	if (eq.k2 == input)
	{
		return true;
	}

	return false;
}

template <typename T>
bool IfRootMatch(T input, const std::vector<Equation<T>>& arr)
{
	for (size_t i = 0; i < arr.size(); i++)
	{
		if (RootMatch(input, arr[i]))
		{
			return true;
		}
	}

	return false;
}



/////////////////
template <typename T>
std::vector<T> UniqueRoots(const std::vector<Equation<T>>& arr)
{
	std::vector<T> ResultArray;
	ResultArray.resize(0);

	for (size_t i = 0; i < arr.size(); i++)//through input array
	{
		bool repeat_root1 = false;
		bool repeat_root2 = false;
		for (size_t j = 0; j < ResultArray.size(); j++)//through result array
		{
			if (arr[i].k1 == ResultArray[j]) 
			{
				repeat_root1 = true;
			}
		}

		if (!repeat_root1)
		{
			ResultArray.push_back(arr[i].k1);
		}

		for (size_t j = 0; j < ResultArray.size(); j++)//through result array
		{
			if (arr[i].k2 == ResultArray[j])
			{
				repeat_root2 = true;
			}
		}

		if (!repeat_root2)
		{
			ResultArray.push_back(arr[i].k2);
		}
	}

	return ResultArray;

}


int main(void)
{
	Equation<double> EquDouble(1, -9, 20);
	Equation<float> EquFloat(1, 3, -10);
	std::cout << "templpate example: " << std::endl;

	std::cout << EquDouble;
	std::cout << EquFloat;


/////////////////////////////////////////////////////////////


	std::vector<Equation<double>> EquationDoubleArray;

	Equation<double> EquDouble1(1, -9, 20);
	Equation<double> EquDouble2(1, -8, 15);
	Equation<double> EquDouble3(1, -3, 2);
	Equation<double> EquDouble4(1, -12, 36);
	Equation<double> EquDouble5(1, -10, 16);

	EquationDoubleArray.push_back(EquDouble1);
	EquationDoubleArray.push_back(EquDouble2);
	EquationDoubleArray.push_back(EquDouble3);
	EquationDoubleArray.push_back(EquDouble4);
	EquationDoubleArray.push_back(EquDouble5);


	std::vector<Equation<float>> EquationFloatArray;

	Equation<float> EquFloat1(1, -9, 20);
	Equation<float> EquFloat2(1, -8, 15);
	Equation<float> EquFloat3(1, -3, 2);
	Equation<float> EquFloat4(1, -12, 36);
	Equation<float> EquFloat5(1, -10, 16);

	EquationFloatArray.push_back(EquFloat1);
	EquationFloatArray.push_back(EquFloat2);
	EquationFloatArray.push_back(EquFloat3);
	EquationFloatArray.push_back(EquFloat4);
	EquationFloatArray.push_back(EquFloat5);

////////////////////////////////////////////////////////////////

	std::cout << "copy test" << std::endl;

	std::copy(EquationDoubleArray.begin(), EquationDoubleArray.end(),
		std::ostream_iterator<Equation<double>>(std::cout, " "));


////////////////////////Root Match (no Lambda, no <algorithm>//////////////////////////////////////

	std::cout << "	ROOT MATCH TEST" << std::endl;

	if (IfRootMatch(7.0, EquationDoubleArray))
	{
		std::cout << "Match found!" << std::endl;
	}
	else
	{
		std::cout << "NO match found!" << std::endl;
	}

	if (IfRootMatch(5.0f, EquationFloatArray))
	{
		std::cout << "Match found!" << std::endl;
	}
	else
	{
		std::cout << "NO match found!" << std::endl;
	}

/////////////////////   Lambda-function 1   //////////////////////////////////////	

	std::cout << "	Lambda-function 1 TEST" << std::endl;

	//cin >> v;
	double v = 5.0;
	auto L_RootMatch = [v](const Equation<double>& eq)
	{
		return ((eq.k1 == v) || (eq.k2 == v));
	};

	auto RootMatchResult = std::find_if(EquationDoubleArray.begin(), EquationDoubleArray.end(), L_RootMatch);

	if (RootMatchResult != EquationDoubleArray.end())
	{
		std::cout << "Match found!" << std::endl;
	}
	else
	{
		std::cout << "NO match found!" << std::endl;
	}

/////////////////////   Lambda-function 2   ///////////////////////////////////////

	std::cout << "	Lambda-function 2 TEST" << std::endl;

	//cin >> v;

	//double v;
	v = 6.0;

	auto L_ifRootisLess = [v](int amount, const Equation<double>& eq)
	{		
		if (eq.k1 < v)
		{
			amount++;
		}

		if (eq.k2 < v)
		{
			amount++;
		}

		return amount;		
	};

	auto AmountResult = std::accumulate(EquationDoubleArray.begin(), EquationDoubleArray.end(), 0, L_ifRootisLess);

	std::cout << "Total amount of roots, that are (less than assigned value) : " << AmountResult << std::endl;
	//std::cout << "	END OF PROGRAMM" << std::endl;

///////////////////////////////////////////////////////////////////////////////

	std::cout << "	Unique roots TEST" << std::endl;

	std::vector<double> UniqueRootsArrayTest;
	UniqueRootsArrayTest.resize(0);

	UniqueRootsArrayTest = UniqueRoots<double>(EquationDoubleArray);

	for (size_t i = 0; i < UniqueRootsArrayTest.size(); i++)
	{
		std::cout << "unique root #" << i << " = " << UniqueRootsArrayTest[i] << std::endl;
	}



	return 0;
}
