#include "core/threading/event.h"

namespace tenku {

Event::Event(bool manualReset, bool initialState)
    : m_event(CreateEvent(nullptr, manualReset, initialState, nullptr))
{}

Event::~Event()
{
    CloseHandle(m_event);
}

void Event::Wait()
{
    WaitForSingleObject(m_event, INFINITE);
}

void Event::Signal()
{
    SetEvent(m_event);
}

void Event::Reset()
{
    ResetEvent(m_event);
}

}  // namespace tenku
