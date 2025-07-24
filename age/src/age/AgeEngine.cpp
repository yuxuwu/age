#include <age/AgeEngine.h>
#include <SDL3/SDL.h>

void
AgeEngine::Init() 
{
	// Initialize SDL
	bool success = SDL_Init(SDL_INIT_VIDEO);
	if (!success) {
		SDL_Log("Initialization failed! %s\n", SDL_GetError());
	}
	
	// Create Window
	const int screenWidth = 640;
	const int screenHeight = 480;
	
	sdlWindow = SDL_CreateWindow("Hello SDL3!", screenWidth, screenHeight, 0);
	if (sdlWindow == NULL) {
		SDL_Log("Window creation failed! %s\n", SDL_GetError());
	}
	
	// Create Renderer
	sdlRenderer = SDL_CreateRenderer(sdlWindow, NULL);
	if (sdlRenderer == NULL) {
		SDL_Log("Renderer creation failed! %s\n", SDL_GetError());
	}
}

void 
AgeEngine::Run() 
{
}

void
AgeEngine::Destroy()
{
	SDL_DestroyWindow(sdlWindow);
	
	sdlWindow = NULL;
	sdlRenderer = NULL;
	
	SDL_Quit();
}

