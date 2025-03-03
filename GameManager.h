#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "GameObject.h"
#include <chrono>
#include <thread>

#include "Define.h"
#include "Event.h"

namespace psh
{
	enum class InputEvent : uint8
	{
		KeyPressed,
		MousePressed
	};

	constexpr uint32 kMIN_UPDATE_TIME = 10;

	class GameManager
	{
	public:
		GameManager();

		void Initialize();

		void Run();

		uint32 GetServerTime() const;

		template <typename... Args>
		EventSystem::EventHandle<Args...> GetEvent(const InputEvent& key)
		{
			return m_eventManager.GetEvent<Args...>(key);
		}

	private:
		uint32 m_serverTime{};
		uint32 m_prevServerTime{};

		sf::RenderWindow m_window;
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;
		std::chrono::high_resolution_clock::time_point m_lastFrameTime;

		EventSystem::EventManager<InputEvent> m_eventManager;
	};
}
