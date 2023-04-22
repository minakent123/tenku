#pragma once

#include <atomic>

#include "core/macros.h"

namespace tenku {

class SpinLock final
{
    NOT_COPYABLE_OR_MOVABLE(SpinLock);

public:
    SpinLock();
    ~SpinLock();

    void Lock();
    bool TryLock();
    void Unlock();

private:
    std::atomic_flag m_state{};
};

}  // namespace tenku
