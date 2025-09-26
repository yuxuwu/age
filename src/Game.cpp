#include "Game.hpp"

#include "util/FileReader.hpp"
#include "shader/Shader.hpp"

#include <glad/glad.h>

#include <SDL3_image/SDL_image.h>

#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

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
    
    window = SDL_CreateWindow("SDL Test Window", windowWidth, windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS);
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

    glViewport(0, 0, windowWidth, windowHeight);
    GLenum error = glGetError();

    if (error != GL_NO_ERROR) {
        cout << "OpenGL error: " << error << endl;
        return false;
    }

    cout << "Succesfully initialized game" << endl;
    cout << "Target FPS: " << targetFPS << endl;
    cout << "MS per frame: " << msPerFrame << endl;

    /// Initialize Imgui
    const char* glsl_version = "#version 330 core";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();
    
    ImGui_ImplSDL3_InitForOpenGL(window, context);
    ImGui_ImplOpenGL3_Init(glsl_version);


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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

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
    // 5.8 Two Triangles
    //======================================================================================
    // Triangle 1
    glGenVertexArrays(1, &vaoTri1);
    glBindVertexArray(vaoTri1);

    unsigned int vboTri1;
    glGenBuffers(1, &vboTri1);
    glBindBuffer(GL_ARRAY_BUFFER, vboTri1);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(triangle1),
        triangle1,
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
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    // Triangle 2
    glGenVertexArrays(1, &vaoTri2);
    glBindVertexArray(vaoTri2);

    unsigned int vboTri2;
    glGenBuffers(1, &vboTri2);
    glBindBuffer(GL_ARRAY_BUFFER, vboTri2);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(triangle2),
        triangle2,
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
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);

    //======================================================================================
    // Colored Triangle
    //======================================================================================
    glGenVertexArrays(1, &vaoColorTri);
    glBindVertexArray(vaoColorTri);

    unsigned int vboColorTri;
    glGenBuffers(1, &vboColorTri);
    glBindBuffer(GL_ARRAY_BUFFER, vboColorTri);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(coloredTriangle),
        coloredTriangle,
        GL_STATIC_DRAW
    );
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);

    //======================================================================================
    // Colored, Textured, Rect
    //======================================================================================
    glGenVertexArrays(1, &vaoColorTexRect);
    glBindVertexArray(vaoColorTexRect);
    
    unsigned int vboColorTexRect;
    glGenBuffers(1, &vboColorTexRect);
    glBindBuffer(GL_ARRAY_BUFFER, vboColorTexRect);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coloredTexturedRect), coloredTexturedRect, GL_STATIC_DRAW);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );
    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(3*sizeof(float))
    );
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)(6*sizeof(float))
    );
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboRect);
    glBindVertexArray(0);

    //======================================================================================
    // Load Shaders
    //======================================================================================
    unsigned int basicVert = Shader::createVertexShader("./assets/glsl/vert/basic.vert");
    unsigned int basicFrag = Shader::createFragmentShader("./assets/glsl/frag/basic.frag");
    unsigned int yellowFrag = Shader::createFragmentShader("./assets/glsl/frag/yellow.frag");
    unsigned int colorOutVert = Shader::createVertexShader("./assets/glsl/vert/colorOut.vert");
    unsigned int colorInFrag = Shader::createFragmentShader("./assets/glsl/frag/colorIn.frag");
    unsigned int vertexColorVert = Shader::createVertexShader("./assets/glsl/vert/vertexColor.vert");
    unsigned int colorTexVert = Shader::createVertexShader("./assets/glsl/vert/colorTex.vert");
    unsigned int colorTexFrag = Shader::createFragmentShader("./assets/glsl/frag/colorTex.frag");

    basicProgram = ShaderProgram(basicVert, basicFrag);
    yellowProgram = ShaderProgram(basicVert, yellowFrag);
    vertColorProgram = ShaderProgram(colorOutVert, colorInFrag);
    colorPerVertexProgram = ShaderProgram(vertexColorVert, colorInFrag);
    colorTexProgram = ShaderProgram(colorTexVert, colorTexFrag);

    glDeleteShader(yellowFrag);
    glDeleteShader(basicVert);
    glDeleteShader(basicFrag);
    glDeleteShader(colorOutVert);
    glDeleteShader(colorInFrag);
    glDeleteShader(colorTexVert);
    glDeleteShader(colorTexFrag);

    //======================================================================================
    // Load Images
    //======================================================================================
    // Open SDL image
    SDL_Surface* wallSurface = IMG_Load("./assets/images/container.jpg");
    SDL_Surface* awesomeSurface = IMG_Load("./assets/images/awesomeface.png");
    if (wallSurface == NULL) {
        cout << "Failed to load wall image: " << SDL_GetError() << endl;
    }
    if (awesomeSurface == NULL) {
        cout << "Failed to load face image: " << SDL_GetError() << endl;
    }
    SDL_Surface* convertedWallSurface = SDL_ConvertSurface(wallSurface, SDL_PIXELFORMAT_RGB24);
    SDL_Surface* convertedAwesomeSurface = SDL_ConvertSurface(awesomeSurface, SDL_PIXELFORMAT_RGB24);
    SDL_DestroySurface(wallSurface);
    SDL_DestroySurface(awesomeSurface);

    // Generate OpenGL texture
    glGenTextures(1, &wallTexture);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D, 
        0, 
        GL_RGB, 
        convertedWallSurface->w, convertedWallSurface->h, 
        0, 
        GL_RGB, 
        GL_UNSIGNED_BYTE, 
        convertedWallSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_DestroySurface(convertedWallSurface);

    glGenTextures(1, &faceTexture);
    glBindTexture(GL_TEXTURE_2D, faceTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB,
        convertedAwesomeSurface->w, convertedAwesomeSurface->h,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        convertedAwesomeSurface->pixels);
    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    SDL_DestroySurface(convertedAwesomeSurface);

    colorTexProgram.use();
    colorTexProgram.setInt("texture1", 0);
    colorTexProgram.setInt("texture2", 1);
}

void Game::ProcessInput()
{
    SDL_Event event{};
    while (SDL_PollEvent(&event)) {
        
        // Process Imgui Events
        ImGui_ImplSDL3_ProcessEvent(&event);

        // Handle all other events
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
    float timeInSeconds = SDL_GetTicks() / 1000.0f;
    greenValue = sin(timeInSeconds) / 2.0f + 0.5f;
}

void Game::Render()
{
    /// Clear
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    //======================================================================================
    // Scene Rendering
    //======================================================================================
    
    /* 
    // Default Triangle
    glBindVertexArray(vaoTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    /*
    // Element Rect
    glBindVertexArray(vaoRect);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    */

    /*
    // Twin Triangle
    glUseProgram(basicProgram);
    glBindVertexArray(vaoTri1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glUseProgram(yellowProgram);
    glBindVertexArray(vaoTri2);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    /*
    // Vert Out Color
    glUseProgram(vertColorProgram);
    glUniform4f(uniformOurColorLoc, 0.0f, greenValue, 0.0f, 1.0f);
    glBindVertexArray(vaoTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    /*
    // Color Per Vertex Triangle
    colorPerVertexProgram.use();
    glBindVertexArray(vaoColorTri);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    */

    // Color Texture Rect
    colorTexProgram.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, wallTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, faceTexture);
    glBindVertexArray(vaoColorTexRect);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //======================================================================================
    // ImGui Rendering
    //======================================================================================
    /*
    ImGui::ShowDemoWindow();
    */

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    //======================================================================================
    // END
    //======================================================================================
    /// Finally, swap render buffers
    SDL_GL_SwapWindow(window);
}
