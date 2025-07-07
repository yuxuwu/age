BUILD_DIR:=build
TEMP_DIR:=temp
FOLDERS:= ${TEMP_DIR} ${BUILD_DIR}

ARCH:=$(shell ./tools/arch.exe)
SDL_VERSION:=3.2.16

CFLAGS:=-I SDL3-${SDL_VERSION}/${ARCH}/include
LDFLAGS:=-L SDL3-${SDL_VERSION}/${ARCH}/lib -lSDL3 -mwindows


### HELLO START ####################################################	
HELLO_DIR:=samples/hello
HELLO_FILENAMES:=hello.c
HELLO_OBJECTS:=${patsubst %.c, ${TEMP_DIR}/%.o, ${HELLO_FILENAMES}}

hello: ${FOLDERS} ${HELLO_OBJECTS} ${BUILD_DIR}/SDL3.dll
	# START: hello
	gcc ${HELLO_OBJECTS} -o ${BUILD_DIR}/hello.exe ${LDFLAGS}

${HELLO_OBJECTS}: ${TEMP_DIR}/%.o: ${HELLO_DIR}/%.c
	# START: $@
	gcc -c $< -o $@ ${CFLAGS}

run_hello: hello
	./${BUILD_DIR}/hello.exe
### HELLO END #####################################################



### TEST1 START ###################################################
TEST1_DIR:=samples/test1
TEST1_FILENAMES:=main.c
TEST1_OBJECTS:=${patsubst %.c, ${TEMP_DIR}/%.o, ${TEST1_FILENAMES}}

test1: ${FOLDERS} ${BUILD_DIR}/resources ${TEST1_OBJECTS} ${BUILD_DIR}/SDL3.dll
	# START: test1
	gcc ${TEST1_OBJECTS} -o ${BUILD_DIR}/test1.exe ${LDFLAGS}
	
${TEST1_OBJECTS}: ${TEMP_DIR}/%.o: ${TEST1_DIR}/%.c
	# START: test1 main.o
	gcc -c $< -o $@ ${CFLAGS}

${BUILD_DIR}/resources:
	# START: test1_binaries
	cp -r ${TEST1_DIR}/resources ${BUILD_DIR}

run_test1: test1
	./${BUILD_DIR}/test1.exe
### TEST1 END #####################################################



${BUILD_DIR}/SDL3.dll: SDL3-${SDL_VERSION}/${ARCH}/bin/SDL3.dll ${BUILD_DIR}
	# START: SDL3.dll
	cp $< ${BUILD_DIR}/SDL3.dll
 
${FOLDERS}:
	# START: folders
	@mkdir -p $@
 
clean:
	# START: clean
	rm -rf ${BUILD_DIR}
	rm -rf ${TEMP_DIR}