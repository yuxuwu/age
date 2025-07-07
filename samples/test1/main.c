#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Surface* gHelloWorld = NULL;

bool init() {
	bool success = SDL_Init(SDL_INIT_VIDEO);
	if (!success) {
		SDL_Log("Initialization failed! %s\n", SDL_GetError());
	}
	
	return success;
}

void end() {
	SDL_DestroyWindow(gWindow);
	SDL_DestroySurface(gHelloWorld);
	
	gWindow = NULL;
	gScreenSurface = NULL;
	gHelloWorld = NULL;
	
	SDL_Quit();
}

bool makeWindow() {
	const int kScreenWidth = 640;
	const int kScreenHeight = 480;
	
	gWindow = SDL_CreateWindow("Hello SDL3!", kScreenWidth, kScreenHeight, 0);
	if (gWindow == NULL) {
		SDL_Log("Window creation failed! %s\n", SDL_GetError());
		return false;
	}
	
	gScreenSurface = SDL_GetWindowSurface(gWindow);
	
	return true;
}

bool loadMedia() {
	char imagePath[256];
	snprintf(imagePath, sizeof(imagePath), "%s%s", SDL_GetBasePath(),"resources/hello.bmp");
	
	gHelloWorld = SDL_LoadBMP(imagePath);
	if (gHelloWorld == NULL) {
		SDL_Log("Unable to load image %s ! %s\n", imagePath, SDL_GetError());
		return false;
	}
	
	return true;
}

void loop() {
	bool quit = false;
	
	SDL_Event e;
	SDL_zero(e);
	
	
	while (!quit) {	
		// process events
		while (SDL_PollEvent( &e )) {	
			if (e.type == SDL_EVENT_QUIT) {
				quit = true;
			}
		}		
		
		// perform updates
		
		// render
		/*
		SDL_FillSurfaceRect( gScreenSurface,
			NULL,
			SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF) );
		*/
		SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
		SDL_UpdateWindowSurface(gWindow);
	}
	
}

int main(int argc, char** argv) {
	bool initSuccess = init();

	if (initSuccess) {
		printf("SDL3 Initialized Successfully!\n");
	} else {
		printf("SDL3 Initialization failed.\n");
	}
	
	makeWindow();
	loadMedia();
	
	loop();
	
	end();
	return 0;
}