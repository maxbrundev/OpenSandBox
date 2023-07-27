#pragma once

#include "OpenSandBox/API/Export.h"

#include <chrono>

namespace Utils
{
	class API_OPENSANDBOX Clock
	{
	public:
		void Update();

		float GetFrameRate() const;
		float GetDeltaTime() const;

	private:
		void Initialize();

	private:
		bool isInitialized = false;

		std::chrono::steady_clock::time_point m_currentTime;
		std::chrono::steady_clock::time_point m_lastTime;
		std::chrono::duration<double> m_elapsedTime;

		float m_timeScale = 1.0f;
		float m_deltaTime = 0.0f;
		float m_timeSinceStart = 0.0f;

	};
}