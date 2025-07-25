CC:=g++
CC_FLAGS:=-Wall -std=c++17

BUILD_DIR:=build
TEMP_DIR:=temp
SRC_DIR:=src

### THIRD PARTY
SDL_INCLUDE:=thirdparty\SDL3-3.2.16\x86_64-w64-mingw32\include
SDL_LIB:=thirdparty\SDL3-3.2.16\x86_64-w64-mingw32\lib
SDL_DLL:=thirdparty\SDL3-3.2.16\x86_64-w64-mingw32\bin\SDL3.dll

SDLIMAGE_INCLUDE:=thirdparty\SDL3_image-3.2.4\x86_64-w64-mingw32\include
SDLIMAGE_LIB:=thirdparty\SDL3_image-3.2.4\x86_64-w64-mingw32\lib
SDLIMAGE_DLL:=thirdparty\SDL3_image-3.2.4\x86_64-w64-mingw32\bin\SDL3_image.dll
### 

INCLUDE_FLAGS:=-I ${SDL_INCLUDE} -I ${SDLIMAGE_INCLUDE}
LD_FLAGS:=-L ${SDL_LIB} -lSDL3 -L ${SDLIMAGE_LIB} -lSDL3_image

.PHONY: main run clean

main: ${BUILD_DIR} ${TEMP_DIR}
	${CC} ${CC_FLAGS} Main.cpp -o ${BUILD_DIR}/Main.exe ${INCLUDE_FLAGS} ${LD_FLAGS} -mwindows
	cp -n ${SDL_DLL} ${BUILD_DIR}/SDL3.dll
	cp -n ${SDLIMAGE_DLL} ${BUILD_DIR}/SDL3_image.dll

${BUILD_DIR} ${TEMP_DIR}:
	mkdir -p $@
	
run:
	./${BUILD_DIR}/Main.exe

clean:
	rm -rf ${BUILD_DIR}
	rm -rf ${TEMP_DIR}
	