#pragma once

#include <windows.h>

#include "core/macros.h"

namespace tenku {

class Event final
{
    NOT_COPYABLE_OR_MOVABLE(Event);

public:
    Event(bool manualReset = false, bool initialState = false);
    ~Event();

    void Wait();
    void Signal();
    void Reset();

private:
    HANDLE m_event;
};

}  // namespace tenku
