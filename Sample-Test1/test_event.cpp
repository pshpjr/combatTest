#pragma once
#include "pch.h"

#include "../Event.h"


TEST(EventTest, SingleCall)

{
	EventSystem::Event<> handler;

	bool firstCalled = false;


	handler.Subscribe([&firstCalled]()

	{
		firstCalled = true;
	});


	handler.Notify();


	ASSERT_TRUE(firstCalled);
}


TEST(EventTest, multiCall)

{
	EventSystem::Event<> handler;

	int called = 0;


	handler.Subscribe([&called]()

	{
		called++;
	});


	handler.Notify();

	handler.Notify();


	ASSERT_EQ(called, 2);
}


TEST(EventTest, emptyCall)

{
	EventSystem::Event<> handler;

	int called = 0;


	handler.Notify();


	ASSERT_EQ(called, 0);
}


TEST(EventTest, callAfterDel)

{
	EventSystem::Event<> handler;

	int called = 0;


	auto id = handler.Subscribe([&called]()

	{
		called++;
	});

	handler.Notify();

	handler.Unsubscribe(id);

	handler.Notify();


	ASSERT_EQ(called, 1);
}


TEST(EventTest, multiListener1)

{
	EventSystem::Event<> handler;

	int called1 = 0;

	int called2 = 0;


	auto id1 = handler.Subscribe([&called1]()

	{
		called1++;
	});

	auto id2 = handler.Subscribe([&called2]()

	{
		called2++;
	});


	handler.Notify();

	handler.Notify();


	ASSERT_EQ(called1, 2);

	ASSERT_EQ(called2, 2);
}


TEST(EventTest, multiListener2)

{
	EventSystem::Event<> handler;

	int called1 = 0;

	int called2 = 0;


	auto id1 = handler.Subscribe([&called1]()

	{
		called1++;
	});

	auto id2 = handler.Subscribe([&called2]()

	{
		called2++;
	});


	handler.Notify();

	handler.Unsubscribe(id1);

	handler.Notify();


	ASSERT_EQ(called1, 1);

	ASSERT_EQ(called2, 2);
}


TEST(EventTest, multiListener3)

{
	EventSystem::Event<> handler;

	int called1 = 0;

	int called2 = 0;


	auto id1 = handler.Subscribe([&called1]()

	{
		called1++;
	});

	auto id2 = handler.Subscribe([&called2]()

	{
		called2++;
	});

	handler.Unsubscribe(id1);

	handler.Notify();

	handler.Notify();


	ASSERT_EQ(called1, 0);

	ASSERT_EQ(called2, 2);
}
