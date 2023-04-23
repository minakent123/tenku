#include "core/threading/thread.h"

#include <process.h>

namespace tenku {

namespace {

const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push, 8)

typedef struct tagTHREADNAME_INFO
{
    DWORD dwType;      // Must be 0x1000.
    LPCSTR szName;     // Pointer to name (in user addr space).
    DWORD dwThreadID;  // Thread ID (-1=caller thread).
    DWORD dwFlags;     // Reserved for future use, must be zero.
} THREADNAME_INFO;

#pragma pack(pop)

void SetThreadName(DWORD dwThreadID, const std::string& threadName)
{
    THREADNAME_INFO info;
    info.dwType = 0x1000;
    info.szName = !threadName.empty() ? threadName.c_str() : nullptr;
    info.dwThreadID = dwThreadID;
    info.dwFlags = 0;
#pragma warning(push)
#pragma warning(disable : 6320 6322)
    __try {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), reinterpret_cast<ULONG_PTR*>(&info));
    } __except (EXCEPTION_EXECUTE_HANDLER) {
    }
#pragma warning(pop)
}

}  // namespace

Thread::Thread()
{}

Thread::~Thread()
{
    Join();
}

void Thread::Sleep(uint32_t millisec)
{
    ::Sleep(millisec);
}

bool Thread::Start()
{
    assert(m_thread == 0);
    uint32_t threadId = 0;
    m_thread = reinterpret_cast<HANDLE>(_beginthreadex(nullptr, StackSize, ThreadMain, this, CREATE_SUSPENDED, &threadId));
    if (m_thread == 0) {
        return false;
    }
    m_isAlive = true;
    SetThreadPriority(m_thread, static_cast<int32_t>(m_priority));
    SetThreadAffinityMask(m_thread, static_cast<DWORD_PTR>(m_affinityMask));
    SetThreadName(threadId, m_name);
    ResumeThread(m_thread);
    return true;
}

void Thread::Stop()
{
    m_isStopped = true;
}

void Thread::Join()
{
    if (m_thread != 0) {
        WaitForSingleObject(m_thread, INFINITE);
        CloseHandle(m_thread);
        m_thread = 0;
        m_isAlive = false;
    }
}

void Thread::SetName(const std::string& name)
{
    m_name = name;
    if (IsAlive()) {
        SetThreadName(static_cast<DWORD>(::GetThreadId(m_thread)), m_name);
    }
}

void Thread::SetPriority(ThreadPriority priority)
{
    m_priority = priority;
    if (IsAlive()) {
        SetThreadPriority(m_thread, static_cast<int32_t>(priority));
    }
}

void Thread::SetAffinityMask(uint64_t affinityMask)
{
    m_affinityMask = affinityMask;
    if (IsAlive()) {
        SetThreadAffinityMask(m_thread, static_cast<DWORD_PTR>(affinityMask));
    }
}

void Thread::PreRun()
{}

void Thread::Run()
{
    while (!IsStopped()) {
        RunInternal();
    }
}

void Thread::PostRun()
{}

uint32_t __stdcall Thread::ThreadMain(void* userData)
{
    Thread* thread = static_cast<Thread*>(userData);
    thread->PreRun();
    thread->Run();
    thread->PostRun();
    thread->m_isAlive = false;
    _endthreadex(0);
    return 0;
}

}  // namespace tenku
