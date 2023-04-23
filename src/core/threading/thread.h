#pragma once

#include <atomic>
#include <string>
#include <windows.h>

#include "core/threading/event.h"

namespace tenku {

enum class ThreadPriority
{
    TimeCritical = THREAD_PRIORITY_TIME_CRITICAL,
    Highest = THREAD_PRIORITY_HIGHEST,
    AboveNormal = THREAD_PRIORITY_ABOVE_NORMAL,
    Normal = THREAD_PRIORITY_NORMAL,
    BelowNormal = THREAD_PRIORITY_BELOW_NORMAL,
    Lowest = THREAD_PRIORITY_LOWEST,
    Idle = THREAD_PRIORITY_IDLE,
};

class Thread
{
    NOT_COPYABLE_OR_MOVABLE(Thread);

public:
    static void Sleep(uint32_t millisec);

public:
    Thread();
    virtual ~Thread();

    bool Start();
    void Stop();
    void Join();
    bool IsAlive() const { return m_isAlive; }
    void SetName(const std::string& name);
    void SetPriority(ThreadPriority priority);
    void SetAffinityMask(uint64_t affinityMask);

protected:
    void Run();
    void PreRun();
    virtual void RunInternal() = 0;
    void PostRun();
    bool IsStopped() const { return m_isStopped; }

private:
    static const uint32_t StackSize = 1 * 1024 * 1024;

private:
    static uint32_t __stdcall ThreadMain(void* userData);

private:
    HANDLE m_thread{};
    ThreadPriority m_priority{ThreadPriority::Normal};
    uint64_t m_affinityMask{};
    std::atomic_bool m_isAlive{};
    std::atomic_bool m_isStopped{};
    std::string m_name{};
};

}  // namespace tenku
