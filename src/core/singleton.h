#pragma once

#include "core/macros.h"

namespace tenku {

template <typename T>
class Singleton
{
    NOT_COPYABLE_OR_MOVABLE(Singleton);

public:
    static T* Create()
    {
        ms_instance = new T;
        return ms_instance;
    }

    static void Destroy()
    {
        delete ms_instance;
        ms_instance = nullptr;
    }

    static T& Get()
    {
        return *ms_instance;
    }

    static T* GetPtr()
    {
        return ms_instance;
    }

protected:
    Singleton()
    {}

    virtual ~Singleton()
    {}

private:
    static T* ms_instance;
};

template <typename T>
T* Singleton<T>::ms_instance = nullptr;

template <typename T>
void DestroySingleton();

template <typename T, typename... TArgs>
bool CreateSingleton(TArgs&&... args)
{
    T* instance = T::Create();
    if (instance == nullptr) {
        return false;
    }
    if (!instance->Initialize(std::forward<TArgs>(args)...)) {
        DestroySingleton<T>();
        return false;
    }
    return true;
}

template <typename T>
void DestroySingleton()
{
    T* instance = T::GetPtr();
    if (instance != nullptr) {
        instance->Finalize();
        T::Destroy();
    }
}

}  // namespace tenku
