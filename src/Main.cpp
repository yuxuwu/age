#include <iostream>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <entt/entt.hpp>

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
    /// Test OpenGL
}