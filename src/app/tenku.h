#pragma once

namespace tenku {

class Tenku final
{
public:
    Tenku();
    ~Tenku();

    bool Initialize();
    void Finalize();
    void Run();
};

}  // namespace tenku
