#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 실습 1
// Inventory b = a; -> 복사 연산자
// Inventory c = std::move(a); -> 이동 연산자
// b = std::move(c); -> 복사 대입 연산자

// 실습 2 - 이동 생성자 완성
class Data
{
private:
	int* ptr;

public:
	Data(int value)
		: ptr(new int(value))
	{

	}

	Data(const Data&) = delete;
	Data& operator=(const Data&) = delete;

	Data(Data&& other) noexcept
	{
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	~Data()
	{
		delete ptr;
	}
};

// 실습 3 - 이동 대입 연산자 구현

Data& operator=(Data&& other) noexcept
{
	if (this != &other)
	{
		this.ptr = nullptr;
		ptr = other.ptr;
		other.ptr = nullptr;
	}

	return *this;
}

// rull of five
//class Inventory
//{
//public:
//	~Inventory();
//
//	Inventory(const Inventory& other);
//
//	Inventory& operator=(const Inventory& other);
//
//	Inventory(Inventory&& other) noexcept;
//
//	Inventory& operator=(Inventory&& other) noexcept;
//};

// 핵심 문법 정리
//#include <utility>
//
//// 복사 생성자
//ClassName(const ClassName& other);
//
//// 이동 생성자
//ClassName(ClassName&& other) noexcept;
//
//// 복사 대입 연산자
//ClassName& operator=(const ClassName& other);
//
//// 이동 대입 연산자
//ClassName& operator=(ClassName&& other) noexcept;
//
//// 이동 가능한 표현식으로 변환
//std::move(object);
//
//// 현재 객체 자신을 반환
//return *this;