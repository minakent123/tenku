#include "app/tenku.h"

#include "SDL2/SDL.h"

namespace tenku {

Tenku::Tenku()
{}

Tenku::~Tenku()
{}

bool Tenku::Initialize()
{
    SDL_Init(SDL_INIT_VIDEO);
    return true;
}

void Tenku::Finalize()
{
    SDL_Quit();
}

void Tenku::Run()
{}

}  // namespace tenku
