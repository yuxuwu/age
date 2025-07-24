#include <age.h>

int main(int argc, char** argv) {
	AgeEngine ageEngine;
	
	ageEngine.Init();
	
	ageEngine.Run();
	
	ageEngine.Destroy();
	
	return 0;
}