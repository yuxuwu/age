#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;

bool init() {
	bool success = SDL_Init(SDL_INIT_VIDEO);
	if (!success) {
		SDL_Log("Initialization failed! %s\n", SDL_GetError());
	}
	
	return success;
}

void end() {
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gScreenSurface = NULL;
	
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
	
	int numDisplays;
	SDL_DisplayID* displayId = SDL_GetDisplays(&numDisplays);
	SDL_Log("Found %d displays.\n", numDisplays);
	
	int i;
	for (int i = 0 ; i < numDisplays; i++) {
		int numDisplayModes;
		SDL_DisplayMode** modes = SDL_GetFullscreenDisplayModes(*displayId, &numDisplayModes);
		SDL_Log("Found %d fullscreen display modes for displayId: %d.\n", numDisplayModes, displayId[i]);
		int j;
		for (j = 0; j < numDisplayModes; j++) {
			SDL_Log("====================\n");
			SDL_Log("Fullscreen Display Mode %d info: \n", j);
			SDL_Log("DisplayID: %d\n", modes[j]->displayID);
			SDL_Log("Pixel Format: %s\n", SDL_GetPixelFormatName(modes[j]->format));
			SDL_Log("Width: %d\n", modes[j]->w);
			SDL_Log("Height: %d\n", modes[j]->h);
			SDL_Log("Pixel Density: %d\n", modes[j]->pixel_density);
			SDL_Log("Refresh Rate: %d\n", modes[j]->refresh_rate);
			SDL_Log("Refresh Rate Numerator: %d\n", modes[j]->refresh_rate_numerator);
			SDL_Log("Refresh Rate Denominator: %d\n", modes[j]->refresh_rate_denominator);
			SDL_Log("====================\n");
		}
		
		SDL_Log("Setting Display Mode 0...");
		SDL_SetWindowFullscreenMode(gWindow, modes[0]);
		SDL_SetWindowFullscreen(gWindow, true);
		
		SDL_free(modes);
		
	}
	
	SDL_free(displayId);
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
		SDL_FillSurfaceRect( gScreenSurface,
			NULL,
			SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF) );
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
	
	loop();
	
	end();
	return 0;
}