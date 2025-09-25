#ifndef GAME_H
#define GAME_H

#include <SDL3/SDL.h>

class Game {
public:
    Game() = default;
    ~Game() = default;

    bool Init();
    void Run();
    void Quit();

private:

    void Load();
    void ProcessInput();
    void Update(const Uint64& deltaTime);
    void Render();

private:
    SDL_Window* window;
    SDL_GLContext context;

    const Uint64 targetFPS = 140;
    const Uint64 msPerFrame = 1000/140;

    bool running = false;

    // temporary vars for test scene
    const float triangleVerts[9] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f
    };
    unsigned int shaderProgram;
    unsigned int vao;
};

#endif