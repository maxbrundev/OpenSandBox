#include "OpenSandBox.h"

#include "OpenSandBox/Tools/Utils/Lerper.h"

#include "OpenSandBox/Tools/Utils/Maths.h"

OpenSandBox::Utils::Lerper::Lerper(float p_value, float p_lerpTime) : m_currentValue(p_value), m_value(p_value), m_lerpTime(p_lerpTime)
{
}

float OpenSandBox::Utils::Lerper::Update(float p_deltaTime)
{
	if (m_currentTime < m_lerpTime)
	{
		m_currentValue = Maths::Lerp(m_value, m_target, m_currentTime / m_lerpTime);

		m_currentTime += 1.0f * p_deltaTime;
	}
	else
	{
		m_currentValue = m_target;
		m_isDone = true;
	}

	return m_currentValue;
}

void OpenSandBox::Utils::Lerper::SetValue(float p_value)
{
	m_value = p_value;
}

void OpenSandBox::Utils::Lerper::SetTarget(float p_value)
{
	m_target = p_value;
}

void OpenSandBox::Utils::Lerper::Reset()
{
	m_currentTime = 0.0f;

	m_isDone = false;
}

void OpenSandBox::Utils::Lerper::Reverse()
{
	m_currentTime = 0.0f;

	m_target = m_initialValue;
	m_value  = m_currentValue;

	m_isDone = false;
}

void OpenSandBox::Utils::Lerper::ReverseInfinitely()
{
	m_currentTime = 0.0f;

	m_target = m_value;
	m_value  = m_currentValue;

	m_isDone = false;
}

bool OpenSandBox::Utils::Lerper::IsDone() const
{
	return m_isDone;
}
