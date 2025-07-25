#include <iostream>
#include <SDL3/SDL.h>

using namespace std;

int main(int argc, char* argv[]) {
	
	SDL_Init(SDL_INIT_VIDEO);
	
	cout << "Hello world" << endl;
	
	return 0;
}