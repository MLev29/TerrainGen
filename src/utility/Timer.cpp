#include "utility/Timer.h"

#include <glfw/glfw3.h>

src::Time src::g_time;

src::Time::Time(void)
    : m_deltaTime(0.0f), m_totalTime(0.0f), m_lastTime(0.0f)
{
}

void src::Time::Update()
{
    constexpr float updateTime = 1.0f / 60.0f;

    m_totalTime = static_cast<float>(glfwGetTime());

    m_deltaTime = m_totalTime - m_lastTime;

    if (m_deltaTime > updateTime)
        m_deltaTime = updateTime;

    m_lastTime = m_totalTime;
}

void src::Time::Reset(void)
{
    m_totalTime = m_lastTime = m_deltaTime = 0.f;
}

float src::Time::GetDeltaTime(void) const
{
    return m_deltaTime;
}

float src::Time::GetTotalTime(void) const
{
    return m_totalTime;
}