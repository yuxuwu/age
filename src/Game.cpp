#include "Game.hpp"
#include "util/FileReader.hpp"

#include <glad/glad.h>

#include <iostream>

using namespace std;

bool Game::Init()
{
        /// Initialize SDL
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        cout << "Error, unable to initialize SDL" << endl;
        return false;
    }
    
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    window = SDL_CreateWindow("SDL Test Window", 640, 480, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
    if (window == NULL) {
        cout << "Failed to create SDL window" << endl;
        SDL_Quit();
        return false;
    }
    
    /// Create GL Context
    context = SDL_GL_CreateContext(window);
    if (context == NULL) {
        cout << "Failed to create SDL GL Context" << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    /// Load all GL Functions
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize glad" << endl;
        
        SDL_GL_DestroyContext(context);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    } 

    glViewport(0, 0, 640, 480);
    GLenum error = glGetError();

    if (error != GL_NO_ERROR) {
        cout << "OpenGL error: " << error << endl;
        return false;
    }

    cout << "Succesfully initialized game" << endl;
    cout << "Target FPS: " << targetFPS << endl;
    cout << "MS per frame: " << msPerFrame << endl;

    return true;
}

void Game::Run()
{

    Load();

    // Main Loop
    running = true;
    
    Uint64 previousTicks = SDL_GetTicks();
    Uint64 lag = 0;

    while(running) {
        Uint64 currentTicks = SDL_GetTicks();
        Uint64 elapsedTicks = currentTicks - previousTicks;
        previousTicks = currentTicks;
        lag += elapsedTicks;

        ProcessInput();

        while(lag >= msPerFrame) {
            Update(msPerFrame);
            lag -= msPerFrame;
        }

        Render();
    }
}

void Game::Quit()
{
    SDL_GL_DestroyContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::Load()
{
    //======================================================================================
    // Triangle
    //======================================================================================
    // link vertex attributes
    glGenVertexArrays(1, &vaoTri);
    glBindVertexArray(vaoTri);

    // load triangle vertex data to the GPU
    unsigned int vboTri;
    glGenBuffers(1, &vboTri);
    glBindBuffer(GL_ARRAY_BUFFER, vboTri);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(triangleVerts),
        triangleVerts,
        GL_STATIC_DRAW
    );
    // specify vertex attributes
    glVertexAttribPointer(
        0, // location 
        3, // num elements
        GL_FLOAT, // element type
        GL_FALSE, // normalize element values
        3 * sizeof(float), // stride
        (void*)0 // starting location from beginning in buffer
    );
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //======================================================================================
    // Rectangle
    //======================================================================================
    glGenVertexArrays(1, &vaoRect);
    glBindVertexArray(vaoRect);

    unsigned int vboRect;
    glGenBuffers(1, &vboRect);
    glBindBuffer(GL_ARRAY_BUFFER, vboRect);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(rectangleVerts),
        rectangleVerts,
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );
    
    glGenBuffers(1, &eboRect);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboRect);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //======================================================================================
    // Load Shaders
    //======================================================================================
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char* vertSource = FileReader::createCharBufferFromFile("./assets/glsl/vert/basic.vert");
    if (vertSource == NULL) {
        cout << "Failed to read Vertex Shader file" << endl;
        return;
    }

    glShaderSource(vertexShader, 1, &vertSource, NULL);
    glCompileShader(vertexShader);
    delete[] vertSource;

    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        cout << "Error: Vertex Shader failed to compile: " << infoLog << endl;
    }

    /// load frag shader
    unsigned int fragShader;
    fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    char* fragSource = FileReader::createCharBufferFromFile("./assets/glsl/frag/basic.frag");
    if (fragSource == NULL) {
        cout << "Failed to read Frag Shader file" << endl;
        return;
    }

    glShaderSource(fragShader, 1, &fragSource, NULL);
    glCompileShader(fragShader);
    delete[] fragSource;

    glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragShader, 512, NULL, infoLog);
        cout << "Error: Frag Shader failed to compiled: " << infoLog << endl;
    }

    /// link shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        cout << "Error: Shader Program failed to link" << endl;
    }


    glDeleteShader(vertexShader);
    glDeleteShader(fragShader);

}

void Game::ProcessInput()
{
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        
        switch (event.type) {
            // Keyboard events
            case SDL_EVENT_KEY_DOWN: {
                switch (event.key.key) {
                    case SDLK_ESCAPE: {
                        running = false;
                        break;
                    }
                    case SDLK_W: {
                        wireframe = !wireframe;
                        if (wireframe) {
                            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        } else {
                            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        }
                        
                    }
                }
                break;
            }

            case SDL_EVENT_QUIT: {
                running = false;
                break;
            }
                
        }
    }
}

void Game::Update(const Uint64& deltaTime)
{
}

void Game::Render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderProgram);

    /*
    glBindVertexArray(vaoTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */
    glBindVertexArray(vaoRect);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    SDL_GL_SwapWindow(window);
}
