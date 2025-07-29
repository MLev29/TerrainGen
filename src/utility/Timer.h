#pragma once

namespace src
{
    class Time
    {
    public:
        Time(void);
        ~Time(void) = default;

        void Update();
        void Reset(void);

        float GetDeltaTime(void) const;
        float GetTotalTime(void) const;

    private:
        float m_deltaTime;
        float m_totalTime;
        float m_lastTime;
    };

    extern Time g_time;
}