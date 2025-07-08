#include <stdio.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_events.h>
#include <SDL3_image/SDL_image.h>

struct Player {
	int x, y;
	
};

SDL_Window* gWindow = NULL;
SDL_Surface* gScreenSurface = NULL;
SDL_Renderer* gRenderer = NULL;

SDL_Texture* flower = NULL;

bool quit = false;
	

bool Init() {
	bool success = SDL_Init(SDL_INIT_VIDEO);
	if (!success) {
		SDL_Log("Initialization failed! %s\n", SDL_GetError());
	}
	
	
	return success;
}

bool InitWindow() {
	const int kScreenWidth = 640;
	const int kScreenHeight = 480;
	
	gWindow = SDL_CreateWindow("Hello SDL3!", kScreenWidth, kScreenHeight, 0);
	if (gWindow == NULL) {
		SDL_Log("Window creation failed! %s\n", SDL_GetError());
		return false;
	}
	
	//gScreenSurface = SDL_GetWindowSurface(gWindow);
	
	return true;
}

bool InitRenderer() {
	gRenderer = SDL_CreateRenderer(gWindow, NULL); 
	if (gRenderer == NULL) {
		SDL_Log("Renderer creation failed! %s\n", SDL_GetError());
		return false;
	}
	return true;
}

void SetFullscreen() {
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
}

void End() {
	SDL_DestroyWindow(gWindow);
	
	gWindow = NULL;
	gScreenSurface = NULL;
	
	SDL_Quit();
}

void ProcessInput() {
	SDL_Event e;
	SDL_zero(e);
	
	// process events
	while (SDL_PollEvent(&e)) {
		switch(e.type) {
			case SDL_EVENT_QUIT:
				quit = true;
				break;
			case SDL_EVENT_KEY_DOWN:
				quit = true;
				break;
			case SDL_EVENT_MOUSE_MOTION:
				break;
			default:
				SDL_Log("Unhandled event!\n");
				break;
		}
	}
}

void Update() {

}

void Render() {
	// render
	/*
	SDL_FillSurfaceRect( gScreenSurface,
		NULL,
		SDL_MapSurfaceRGB( gScreenSurface, 0xFF, 0xFF, 0xFF) );
	SDL_UpdateWindowSurface(gWindow);
	*/
	
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(gRenderer);
	
	SDL_FRect dstRect = {10, 10, 32, 32};
	SDL_RenderTexture(gRenderer, flower, NULL, &dstRect);
	/*
	SDL_SetRenderDrawColor(gRenderer, 0,0,0,0xFF);
	SDL_FRect rect = {10, 10, 20, 20};
	SDL_RenderFillRect(gRenderer, &rect);
	*/
	SDL_RenderPresent(gRenderer);
}

void BeforeLoop() {
	// Load flower image
	char imagePath[512];
	snprintf(imagePath, sizeof(imagePath), "%s%s", SDL_GetBasePath(),"resources\\flower.png");
	SDL_Surface* tempSurf = IMG_Load(imagePath);
	if (tempSurf == NULL) {
		SDL_Log("Failed to load flower! %s\n", SDL_GetError());
	}
	flower = SDL_CreateTextureFromSurface(gRenderer, tempSurf);
	SDL_DestroySurface(tempSurf);
	
}

void MainLoop() {

	while (!quit) {	
		ProcessInput();
		Update();
		Render();
	}
	
}

int main(int argc, char** argv) {
	bool initSuccess = Init();

	if (initSuccess) {
		printf("SDL3 Initialized Successfully!\n");
	} else {
		printf("SDL3 Initialization failed.\n");
		return -1;
	}
	
	if (!InitWindow()) {
		SDL_Log("Failed to create window!\n");
		return -1;
	}
	if (!InitRenderer()) {
		SDL_Log("Failed to create renderer!\n");
		return -1;
	}

	BeforeLoop();
	
	MainLoop();
	
	End();
	return 0;
}