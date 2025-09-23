#include <iostream>
#include <glm/glm.hpp>

using namespace std;

int main (int argc, char** argv) {
    cout << "Hello world" << endl;

    /// Test glm
    glm::vec2 myVec(1.0, 1.0);
    glm::vec2 myOtherVec(2.0, 2.0);
    myVec += myOtherVec;
    cout << "myVec: " << myVec.x << ", " << myVec.y << endl;
    
    /// Test Lua
    /// Test entt
    /// Test SDL3
    /// Test OpenGL
}