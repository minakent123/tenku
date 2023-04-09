#pragma once

class Tenku final
{
public:
    Tenku();
    ~Tenku();

    bool Initialize();
    void Finalize();
    void Run();
};