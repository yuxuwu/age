#ifndef AGE_ENGINE
#define AGE_ENGINE

#include <SDL3/SDL.h>

class AgeEngine {
	public:
		void Init();
		void Run();
		void Destroy();
		
	private:
		SDL_Renderer* sdlRenderer = NULL;
		SDL_Window* sdlWindow = NULL;
};

#endif