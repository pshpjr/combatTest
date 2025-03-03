#pragma once
namespace psh
{
	//템플릿 디버깅 위한 함수
	template <typename... Ts>
	void PrintArgs()
	{
		((std::cout << typeid(Ts).name() << ", "), ...);
		std::cout << "\n";
	}
}
