#include <iostream>
#include <vector>
#include <array>

void fun1(int x) noexcept/*(true)*/
{
	if (x > 10)
	{
		throw std::exception("fun1 exception");
	}
}

void fun2(int x) noexcept(false)
{
	if (x > 10)
	{
		throw std::exception("fun2 exception");
	}
}

class DataContainerArray
{
	std::array<int, 5> arr{ 1, 2, 3, 4, 5 };
};

class DataContainerVector
{
	std::vector<int> v{ 1, 2, 3, 4, 5 };
};

/*
template <typename T>
T copy(const T& src) noexcept(noexcept(T(src)))
{
	return src;
}
*/

template <typename T>
// T copy(const T& src) noexcept(std::is_nothrow_copy_constructible<T>::value)
T copy(const T& src) noexcept(std::is_nothrow_copy_constructible_v<T>)
{
	return src;
}

template <typename T>
T copy2(const T& src) noexcept(std::is_fundamental_v<T>)
{
	return src;
}

struct NoExceptExamples
{
	auto f1() const noexcept -> int;
	void f1() noexcept
	{
		auto lambda = []() noexcept {return 100; };
		std::cout << lambda() << std::endl;
	}

	~NoExceptExamples() = default; // jest domyslnie noexcept
};

int main()
{
	try {
		// fun1(11); 

	    // fun2(11);
		
		DataContainerArray dc1;
		DataContainerVector dc2;

		std::cout << noexcept(copy(dc1)) << std::endl;
		std::cout << noexcept(copy(dc2)) << std::endl;
		
	}
	catch (const std::exception & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}