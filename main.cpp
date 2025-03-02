#pragma comment(lib,"Winmm.lib")

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "GameManager.hpp"

// 테스트용 이벤트 타입 정의
enum class TestEventType
{
	Test1,
	Test2,
	Test3
};

// 테스트용 데이터 구조체
struct TestData
{
	int value;
	std::string message;
};

int main()
{
	GameManager gameManager;
	gameManager.Initialize();
	gameManager.Run();


	return 0;
}
