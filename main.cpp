#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	vector<int> numbers = { 40, 10, 80, 30, 60 };

	// 1. 람다 함수 sort
	sort(numbers.begin(), numbers.end(),
		[](int a, int b) {
			return a > b;
		}
	);

	// 2. find_if

	vector<int> hp = { 100, 80, 30, 150 };
	auto it = find_if(hp.begin(), hp.end(),
		[](int value)
		{
			return value < 50;
		}
	);

	// 3. remove_if
	vector<int> monsters = { 100, 0, 50, 0, 80 };
	monsters.erase(
		remove_if(monsters.begin(), monsters.end(),
			[](int value)
			{
				return value == 0;
			}
		),
		monsters.end()
	);

	// 핵심 문법

#include <algorithm>

// 1. 오름차순
	sort(v.begin(), v.end());

	// 2. 내림차순
	sort(v.begin(), v.end(),
		[](int a, int b)
		{
			return a > b;
		}
	);

	// 3. 람다 함수
	//auto Add = [](int a, int b)
	//	{
	//		return a + b;
	//	};

	//// 4. 람다 캡처
	//[x]   // x를 값으로 캡처
	//	[&x]  // x를 참조로 캡처
	//[=]   // 사용한 외부 지역 변수를 값으로 캡처
	//[&]   // 사용한 외부 지역 변수를 참조로 캡처

	//// 5. 조건 검색
	//auto it = find_if(v.begin(), v.end(), 조건);

	//// 6. 조건에 맞는 개수
	//auto count = count_if(v.begin(), v.end(), 조건);

	//// 7. 조건에 맞는 원소 삭제
	//v.erase(
	//	remove_if(v.begin(), v.end(), 조건),
	//	v.end()
	//);