#include "pch.h"
#include "../Event.h"
#include "../EventTypes.h"

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

TEST(EventManagerTest, AddAndNotifyCallback)
{
	EventSystem::EventManager<TestEventType> eventManager;

	// 테스트 변수
	int callbackValue = 0;

	// 콜백 추가
	auto event = eventManager.GetOrCreateEvent<int>(TestEventType::Test1);

	event.Subscribe([&callbackValue](int value)
	{
		callbackValue = value;
	});

	// 이벤트 트리거
	eventManager.Notify(TestEventType::Test1, 42);

	// 콜백이 호출되었는지 확인
	EXPECT_EQ(callbackValue, 42);
}


TEST(EventManagerTest, MultipleCallbacks)
{
	EventSystem::EventManager<TestEventType> eventManager;

	int sum = 0;

	auto event = eventManager.GetOrCreateEvent<int>(TestEventType::Test1);

	event.Subscribe([&](int value)
	{
		sum = value;
	});

	event.Subscribe([&sum](int value)
	{
		sum += value * 2;
	});

	// 이벤트 트리거
	eventManager.Notify(TestEventType::Test1, 10);

	// 두 콜백이 모두 호출되었는지 확인 (10 + 10*2 = 30)
	EXPECT_EQ(sum, 30);
}

TEST(EventManagerTest, RemoveCallback)
{
	EventSystem::EventManager<TestEventType> eventManager;

	int callbackValue = 0;

	auto event = eventManager.GetOrCreateEvent<int>(TestEventType::Test1);

	auto id = event.Subscribe([&callbackValue](int value)
	{
		callbackValue = value;
	});

	// 콜백 제거
	event.Unsubscribe(id);

	// 이벤트 트리거
	eventManager.Notify(TestEventType::Test1, 42);

	// 콜백이 제거되었으므로 값이 변경되지 않아야 함
	EXPECT_EQ(callbackValue, 0);
}

TEST(EventManagerTest, MultipleEventTypes)
{
	EventSystem::EventManager<TestEventType> eventManager;

	int value1 = 0;
	int value2 = 0;

	auto event1 = eventManager.GetOrCreateEvent<int>(TestEventType::Test1);

	event1.Subscribe([&value1](int val)
	{
		value1 = val;
	});

	auto event2 = eventManager.GetOrCreateEvent<int>(TestEventType::Test2);

	event2.Subscribe([&value2](int val)
	{
		value2 = val * 2;
	});
	// 각 이벤트 트리거
	eventManager.Notify(TestEventType::Test1, 10);
	eventManager.Notify(TestEventType::Test2, 20);

	// 각 콜백이 올바르게 호출되었는지 확인
	EXPECT_EQ(value1, 10);
	EXPECT_EQ(value2, 40);
}

TEST(EventManagerTest, ComplexParameters)
{
	// 복잡한 파라미터를 가진 이벤트 매니저
	EventSystem::EventManager<TestEventType> complexEventManager;

	TestData receivedData;
	int receivedCode = 0;

	// 콜백 추가
	auto event = complexEventManager.GetOrCreateEvent<const TestData&, int>(TestEventType::Test3);
	event.Subscribe([&receivedData, &receivedCode](const TestData& data, int code)
	{
		receivedData = data;
		receivedCode = code;
	});

	// 테스트 데이터 생성
	TestData testData{100, "Test Message"};

	// 이벤트 트리거
	complexEventManager.Notify(TestEventType::Test3, testData, 200);

	// 결과 확인
	EXPECT_EQ(receivedData.value, 100);
	EXPECT_EQ(receivedData.message, "Test Message");
	EXPECT_EQ(receivedCode, 200);
}
