#pragma once
#include "pch.h"

#include "../Event.h"

#include <string>


TEST(EventWithArgsTest, SingleIntArg)

{
	EventSystem::Event<int> handler;

	int receivedValue = 0;


	handler.Subscribe([&receivedValue](int value)

	{
		receivedValue = value;
	});


	handler.Notify(42);


	ASSERT_EQ(receivedValue, 42);
}


TEST(EventWithArgsTest, MultipleArgs)

{
	EventSystem::Event<int, std::string> handler;

	int receivedInt = 0;

	std::string receivedString;


	handler.Subscribe([&receivedInt, &receivedString](int value, const std::string& text)

	{
		receivedInt = value;

		receivedString = text;
	});


	handler.Notify(123, "Hello World");


	ASSERT_EQ(receivedInt, 123);

	ASSERT_EQ(receivedString, "Hello World");
}


TEST(EventWithArgsTest, MultipleListenersWithArgs)

{
	EventSystem::Event<int> handler;

	int sum = 0;

	int product = 1;


	handler.Subscribe([&sum](int value)

	{
		sum += value;
	});


	handler.Subscribe([&product](int value)

	{
		product *= value;
	});


	handler.Notify(3);

	handler.Notify(4);


	ASSERT_EQ(sum, 7); // 3 + 4

	ASSERT_EQ(product, 12); // 3 * 4
}


TEST(EventWithArgsTest, UnsubscribeWithArgs)

{
	EventSystem::Event<int, int> handler;

	int sum1 = 0;

	int sum2 = 0;


	auto id1 = handler.Subscribe([&sum1](int a, int b)

	{
		sum1 = a + b;
	});


	auto id2 = handler.Subscribe([&sum2](int a, int b)

	{
		sum2 = a + b + 10;
	});


	handler.Notify(5, 3);

	ASSERT_EQ(sum1, 8);

	ASSERT_EQ(sum2, 18);


	handler.Unsubscribe(id1);

	handler.Notify(2, 2);

	ASSERT_EQ(sum1, 8); // 변경되지 않음

	ASSERT_EQ(sum2, 14); // 2 + 2 + 10
}


TEST(EventWithArgsTest, ComplexTypes)

{
	struct TestData

	{
		int id;

		std::string name;


		bool operator==(const TestData& other) const

		{
			return id == other.id && name == other.name;
		}
	};


	EventSystem::Event<TestData, bool> handler;

	TestData receivedData{0, ""};

	bool receivedFlag = false;


	handler.Subscribe([&receivedData, &receivedFlag](const TestData& data, bool flag)

	{
		receivedData = data;

		receivedFlag = flag;
	});


	TestData testData{42, "Test"};

	handler.Notify(testData, true);


	ASSERT_EQ(receivedData, testData);

	ASSERT_TRUE(receivedFlag);
}


TEST(EventWithArgsTest, ReferenceArgs)

{
	EventSystem::Event<int&> handler;


	handler.Subscribe([](int& value)

	{
		value *= 2;
	});


	int testValue = 5;

	handler.Notify(testValue);


	ASSERT_EQ(testValue, 10); // 값이 콜백 내에서 수정됨
}


TEST(EventWithArgsTest, MoveOnlyTypes)
{
	EventSystem::Event<std::unique_ptr<int>> handler;
	int resultValue = 0;
	handler.Subscribe([&resultValue](std::unique_ptr<int> ptr)
	{
		*ptr = 42;

		resultValue = *ptr;
	});

	auto ptr = std::make_unique<int>(10);

	handler.Notify(std::move(ptr));

	ASSERT_EQ(resultValue, 42);
	ASSERT_EQ(ptr, nullptr);
}
