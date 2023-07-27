#include "OpenSandBox.h"

#include "OpenSandBox\Tools\Time\Clock.h"

void Utils::Clock::Initialize()
{
	m_deltaTime = 0.0f;

	m_currentTime = std::chrono::steady_clock::now();
	m_lastTime = m_currentTime;

	isInitialized = true;
}

void Utils::Clock::Update()
{
	m_currentTime = std::chrono::steady_clock::now();
	m_elapsedTime = m_currentTime - m_lastTime;

	m_lastTime = m_currentTime;

	if (isInitialized)
	{
		m_deltaTime = m_elapsedTime.count() > 0.1 ? 0.1f : static_cast<float>(m_elapsedTime.count());

		m_timeSinceStart += m_deltaTime * m_timeScale;
	}
	else
	{
		Initialize();
	}
}

float Utils::Clock::GetFrameRate() const
{
	return 1.0f / (m_deltaTime);
}

float Utils::Clock::GetDeltaTime() const
{
	return m_deltaTime * m_timeScale;
}
