#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.hpp"
#include <chrono>
#include <thread>

#include "Define.h"
#include "Event.h"

namespace psh
{
	enum class InputEvent
	{
		KeyPressed,
		MousePressed
	};
}

constexpr uint32 kMIN_UPDATE_TIME = 10;

class GameManager
{
public:
	GameManager();

	void Initialize();

	void Run();

	uint32 GetServerTime() const;

	template <typename... Args>
	EventSystem::EventHandle<Args...> GetEvent(const psh::InputEvent& key)
	{
		return m_eventManager.GetEvent<Args...>(key);
	}

private:
	uint32 m_serverTime{};
	uint32 m_prevServerTime{};

	sf::RenderWindow m_window;
	std::vector<std::shared_ptr<GameObject>> m_gameObjects;
	std::chrono::high_resolution_clock::time_point m_lastFrameTime;

	EventSystem::EventManager<psh::InputEvent> m_eventManager;
};
