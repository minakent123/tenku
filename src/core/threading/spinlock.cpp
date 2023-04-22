#include "core/threading/spinlock.h"

namespace tenku {

SpinLock::SpinLock()
{}

SpinLock::~SpinLock()
{}

void SpinLock::Lock()
{
    while (m_state.test_and_set(std::memory_order_acquire)) {
    }
}

bool SpinLock::TryLock()
{
    return !m_state.test_and_set(std::memory_order_acquire);
}

void SpinLock::Unlock()
{
    m_state.clear(std::memory_order_acquire);
}

}  // namespace tenku
