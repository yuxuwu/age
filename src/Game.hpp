#ifndef GAME_H
#define GAME_H

#include "shader/ShaderProgram.hpp"

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
    const Uint64 targetFPS = 140;
    const Uint64 msPerFrame = 1000/140;
    const Uint64 windowWidth = 1280;
    const Uint64 windowHeight = 720;

    SDL_Window* window;
    SDL_GLContext context;
    
    bool running = false;
    bool wireframe = false;

    

    /// temporary vars for test scene
    // triangle
    const float triangleVerts[9] = {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.0f,  0.5f,  0.0f
    };
    unsigned int vaoTri;

    // rectangle
    const float rectangleVerts[12] = {
         0.5f,  0.5f,  0.0f, // top right
         0.5f, -0.5f,  0.0f, // bottom right
        -0.5f, -0.5f,  0.0f, // bottom left
        -0.5f,  0.5f,  0.0f  // top left
    };
    const unsigned int indicies[6] = {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int vaoRect;
    unsigned int eboRect;

    // 5.8.1 Two triangles
    const float triangle1[9] = {
        -0.5f,  0.5f,  0.0f, // left top
        -0.5f,  0.0f,  0.0f, // left left
         0.0f,  0.0f,  0.0f  // left right
    };
    const float triangle2[9] = {
         0.5f,  0.5f,  0.0f, // right top
         0.0f,  0.0f,  0.0f, // right left
         0.5f,  0.0f,  0.0f  // right right
    };
    unsigned int vaoTri1;
    unsigned int vaoTri2;

    // colored triangle
    const float coloredTriangle[18] = {
        // verts             // colors
        -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, 0.0f,
         0.5f, -0.5f,  0.0f, 0.0f, 1.0f, 0.0f,
         0.0f,  0.5f,  0.0f, 0.0f, 0.0f, 1.0f
    };
    unsigned int vaoColorTri;

    // colored textured rect
    const float coloredTexturedRect[32] = {
        // positions      // colors         // texture coords
         0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
    };
    unsigned int vaoColorTexRect;
    
    // shaders
    ShaderProgram basicProgram;
    ShaderProgram yellowProgram;
    ShaderProgram vertColorProgram;
    ShaderProgram colorPerVertexProgram;
    ShaderProgram colorTexProgram;

    // textures
    unsigned int wallTexture;
    unsigned int faceTexture;

    // uniform vars
    int uniformOurColorLoc;
    float greenValue;
    
};

#endif