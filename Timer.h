#pragma once
#include <chrono>
#include <iostream>

namespace Timer
{
    class Timer
    {
        std::chrono::time_point<std::chrono::steady_clock> start, end;
        std::chrono::duration<float> duration;
        const char* mName;
    public:
        Timer() = delete;
        Timer(const char* name)
        {
            start = std::chrono::steady_clock::now();
            mName = name;
        }
        ~Timer()
        {
            end = std::chrono::steady_clock::now();
            duration = end - start;
            float ms = duration.count()*1000.0f;
            std:: cout <<"Function " << mName << " cost " << ms << " ms\n";
        }
    };
}

#define TIMING 1
#if TIMING
#define TIMER() Timer::Timer timer##__LINE__(__FUNCTION__)
#define TIMER_PROCESS(name) Timer::Timer timer##__LINE__(name)
#else
#define TIMER() 
#define TIMER(name)
#endif