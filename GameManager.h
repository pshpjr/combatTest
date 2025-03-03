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
		void Render();
		void HandleInput();
		void Update(MsTime diff);

		void Run();

		uint32 GetServerTime() const;

		template <typename... Args>
		EventSystem::EventHandle<Args...> GetEvent(const InputEvent& key)
		{
			return m_eventManager.GetEvent<Args...>(key);
		}

		void UpdateFrameStats(MsTime frameTime);

	private:
		// Frame rate tracking
		float m_fps{0.f};
		MsTime m_frameTimeAccumulator{0};
		MsTime m_averageFrameTime{0};
		MsTime m_minFrameTime{std::numeric_limits<MsTime>::max()};
		MsTime m_maxFrameTime{0};
		int m_frameCount{0};
		uint32 m_nextUpdateTime{0};
		static constexpr int FPS_UPDATE_INTERVAL = 1000;

		uint32 m_serverTime{};
		uint32 m_prevServerTime{};

		sf::RenderWindow m_window;
		std::vector<std::shared_ptr<GameObject>> m_gameObjects;

		EventSystem::EventManager<InputEvent> m_eventManager;
	};
}
