#include <iostream>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <glad/glad.h>

using namespace std;

struct entt_position {
    float x;
    float y;
};

int main (int argc, char** argv) {
    cout << "Hello world" << endl;

    /// Test glm
    glm::vec2 myVec(1.0, 1.0);
    glm::vec2 myOtherVec(2.0, 2.0);
    myVec += myOtherVec;
    cout << "myVec: " << myVec.x << ", " << myVec.y << endl;
    
    /// Test Sol/Lua
    sol::state lua;
    lua.open_libraries(sol::lib::base);
    lua.script("print('bark, bark, bark')");

    /// Test entt
    entt::registry registry;
    const auto entity = registry.create();
    registry.emplace<entt_position>(entity, 1.f, 1.f);
    
    auto view = registry.view<const entt_position>();
    for (auto entity: view) {
        auto& pos = view.get<entt_position>(entity);
        cout << "pos x: " << pos.x << " pos y: " << pos.y << endl;
    }

    /// Test SDL3
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Error, unable to initialize SDL" << endl;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_Window* window = SDL_CreateWindow("SDL Test Window", 640, 480, SDL_WINDOW_OPENGL);
    if (window == NULL) {
        cout << "Failed to create SDL window" << endl;
        SDL_Quit();
        return -1;
    }
    
    /// Test OpenGL
    SDL_GLContext context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        cout << "Failed to create SDL GL Context" << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize glad" << endl;
        
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    } 

    glViewport(0, 0, 640, 480);
    GLenum error = glGetError();

    if (error == GL_NO_ERROR) {
        cout << "OpenGL function glViewport() was able to be called" << endl;
    } else {
        cout << "OpenGL error: " << error << endl;
    }

    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return 0;
}