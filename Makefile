BUILD_DIR:=build
TEMP_DIR:=temp
FOLDERS:= ${TEMP_DIR} ${BUILD_DIR}
CC := g++

ARCH:=$(shell ./tools/arch.exe)

#( SDL
SDL_VERSION:=3.2.16
SDL_LOCATION:=thirdparty/SDL3-${SDL_VERSION}/${ARCH}
SDL_DLL_LOCATION:=${SDL_LOCATION}/bin/SDL3.dll

SDLIMAGE_VERSION:=3.2.4
SDLIMAGE_LOCATION:=thirdparty/SDL3_image-${SDLIMAGE_VERSION}/${ARCH}
SDLIMAGE_DLL_LOCATION:=${SDLIMAGE_LOCATION}/bin/SDL3_image.dll
#) SDL

#( CGML
CGLM_LOCATION:=thirdparty/cglm
#) CGML

#( AGE
AGE_LOCATION:=src
AGE_DLL_LOCATION:=${BUILD_DIR}/${AGE_NAME}/age.dll
AGE_LDFLAGS:=-L ${SDL_LOCATION}/lib -lSDL3 -L ${SDLIMAGE_LOCATION}/lib -lSDL3_image -mwindows
#) AGE

CFLAGS:=-I ${SDL_LOCATION}/include -I ${SDLIMAGE_LOCATION}/include -I ${CGLM_LOCATION}/include -I ${AGE_LOCATION}/include
LDFLAGS:=-L ${SDL_LOCATION}/lib -lSDL3 -L ${SDLIMAGE_LOCATION}/lib -lSDL3_image -L build/age -lage -mwindows


### AGE ############################################################
AGE_FILENAMES:=AgeEngine.cpp
AGE_TEMP_DIR:=${TEMP_DIR}/${AGE_NAME}
AGE_BUILD_DIR:=${BUILD_DIR}/age
AGE_OBJECTS:=${patsubst %.cpp, ${AGE_TEMP_DIR}/%.o, ${AGE_FILENAMES}}

build/age/age.dll build/age/libage.dll.a: ${FOLDERS} ${AGE_TEMP_DIR} ${AGE_BUILD_DIR} ${AGE_OBJECTS}
	# START: $@
	${CC} ${AGE_OBJECTS} -fPIC -shared -o ${AGE_BUILD_DIR}/age.dll ${AGE_LDFLAGS} -lc -Wl,--out-implib,${AGE_BUILD_DIR}/libage.dll.a

${AGE_TEMP_DIR} ${AGE_BUILD_DIR}:
	# START: $@
	@mkdir -p $@

${AGE_OBJECTS}: ${TEMP_DIR}/${AGE_NAME}/%.o: ${AGE_LOCATION}/age/%.cpp
	# START: $@
	${CC} -c $< -o $@ ${CFLAGS}
####################################################################


### START HELLO ####################################################	
HELLO_NAME:=hello
HELLO_DIR:=samples/hello
HELLO_FILENAMES:=hello.c
HELLO_TEMP_DIR:=${TEMP_DIR}/${HELLO_NAME}
HELLO_BUILD_DIR:=${BUILD_DIR}/${HELLO_NAME}
HELLO_OBJECTS:=${patsubst %.c, ${HELLO_TEMP_DIR}/%.o, ${HELLO_FILENAMES}}

hello: ${FOLDERS} ${HELLO_TEMP_DIR} ${HELLO_BUILD_DIR} ${HELLO_OBJECTS}
	# START: $@
	${CC} ${HELLO_OBJECTS} -o ${BUILD_DIR}/${HELLO_NAME}/hello.exe ${LDFLAGS}

${HELLO_TEMP_DIR} ${HELLO_BUILD_DIR}:
	# START: $@
	@mkdir -p $@

${HELLO_OBJECTS}: ${TEMP_DIR}/${HELLO_NAME}/%.o: ${HELLO_DIR}/%.c
	# START: $@
	${CC} -c $< -o $@ ${CFLAGS}

${HELLO_BUILD_DIR}/SDL3.dll:
	# START: $@
	cp -p ${SDL_DLL_LOCATION} $@
	
run_hello: hello ${HELLO_BUILD_DIR}/SDL3.dll
	./${BUILD_DIR}/${HELLO_NAME}/hello.exe
### END HELLO #####################################################



### START TEST1 ###################################################
TEST1_NAME:=test1
TEST1_DIR:=samples/test1
TEST1_FILENAMES:=main.c
TEST1_TEMP_DIR:=${TEMP_DIR}/${TEST1_NAME}
TEST1_BUILD_DIR:=${BUILD_DIR}/${TEST1_NAME}
TEST1_OBJECTS:=${patsubst %.c, ${TEST1_TEMP_DIR}/%.o, ${TEST1_FILENAMES}}


test1: ${FOLDERS} ${TEST1_TEMP_DIR} ${TEST1_BUILD_DIR} ${TEST1_BUILD_DIR}/resources ${TEST1_OBJECTS}
	# START: test1
	${CC} ${TEST1_OBJECTS} -o ${TEST1_BUILD_DIR}/test1.exe ${LDFLAGS}

${TEST1_OBJECTS}: ${TEST1_TEMP_DIR}/%.o: ${TEST1_DIR}/%.c
	# START: test1 main.o
	${CC} -c $< -o $@ ${CFLAGS}

${TEST1_BUILD_DIR}/resources:
	# START: test1_binaries
	cp -r ${TEST1_DIR}/resources $@

${TEST1_BUILD_DIR}/SDL3.dll: 
	cp -p ${SDL_DLL_LOCATION} $@

${TEST1_TEMP_DIR} ${TEST1_BUILD_DIR}:
	# START: $@
	@mkdir -p $@
	
run_test1: test1 ${TEST1_BUILD_DIR}/SDL3.dll
	./${TEST1_BUILD_DIR}/test1.exe
### END TEST1 #####################################################



### START TEST2 ###################################################
TEST2_NAME:=test2
TEST2_DIR:=samples/test2
TEST2_FILENAMES:=main.c
TEST2_TEMP_DIR:=${TEMP_DIR}/${TEST2_NAME}
TEST2_BUILD_DIR:=${BUILD_DIR}/${TEST2_NAME}
TEST2_OBJECTS:=${patsubst %.c, ${TEST2_TEMP_DIR}/%.o, ${TEST2_FILENAMES}}

test2: ${FOLDERS} ${TEST2_TEMP_DIR} ${TEST2_BUILD_DIR} ${TEST2_OBJECTS} ${TEST2_BUILD_DIR}/resources
	# START: test2
	${CC} ${TEST2_OBJECTS} -o ${TEST2_BUILD_DIR}/test2.exe ${LDFLAGS}

${TEST2_OBJECTS}: ${TEST2_TEMP_DIR}/%.o: ${TEST2_DIR}/%.c
	# START: test2 main.o
	${CC} -c $< -o $@ ${CFLAGS}

${TEST2_BUILD_DIR}/SDL3.dll: 
	cp -p ${SDL_DLL_LOCATION} $@

${TEST2_BUILD_DIR}/SDL3_image.dll:
	cp -p ${SDLIMAGE_DLL_LOCATION} $@

${TEST2_BUILD_DIR}/resources:
	# START: $@
	cp -r ${TEST2_DIR}/resources $@

${TEST2_TEMP_DIR} ${TEST2_BUILD_DIR}:
	# START: $@
	@mkdir -p $@
	
run_test2: test2 ${TEST2_BUILD_DIR}/SDL3.dll ${TEST2_BUILD_DIR}/SDL3_image.dll 
	./${TEST2_BUILD_DIR}/test2.exe
### END TEST2 #####################################################



### START TEST3 ###################################################
TEST3_NAME:=test3
TEST3_DIR:=samples/test3
TEST3_FILENAMES:=main.cpp
TEST3_TEMP_DIR:=${TEMP_DIR}/${TEST3_NAME}
TEST3_BUILD_DIR:=${BUILD_DIR}/${TEST3_NAME}
TEST3_OBJECTS:=${patsubst %.cpp, ${TEST3_TEMP_DIR}/%.o, ${TEST3_FILENAMES}}


test3: ${FOLDERS} ${TEST3_TEMP_DIR} ${TEST3_BUILD_DIR} ${AGE_BUILD_DIR}/libage.dll.a  ${TEST3_OBJECTS}
	# START: test3
	${CC} ${TEST3_OBJECTS} -o ${TEST3_BUILD_DIR}/test3.exe ${LDFLAGS}

${TEST3_OBJECTS}: ${TEST3_TEMP_DIR}/%.o: ${TEST3_DIR}/%.cpp
	# START: test3 main.o
	${CC} -c $< -o $@ ${CFLAGS}

${TEST3_BUILD_DIR}/resources:
	# START: $@
	cp -r ${TEST3_DIR}/resources $@

${TEST3_TEMP_DIR} ${TEST3_BUILD_DIR}:
	# START: $@
	@mkdir -p $@

${TEST3_BUILD_DIR}/age.dll:
	cp build/age/age.dll build/test3/age.dll
	
${TEST3_BUILD_DIR}/SDL3.dll: 
	cp -p ${SDL_DLL_LOCATION} $@

run_test3: test3 build/test3/age.dll build/test3/SDL3.dll
	./${TEST3_BUILD_DIR}/test3.exe
### END TEST3 #####################################################


.PHONY: clean run_hello run_test1 run_test2 run_test3
 
 
${FOLDERS}:
	# START: $@
	@mkdir -p $@

 
clean:
	# START: clean
	rm -rf ${BUILD_DIR}
	rm -rf ${TEMP_DIR}