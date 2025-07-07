BUILD_DIR:=build
TEMP_DIR:=temp
FOLDERS:= ${TEMP_DIR} ${BUILD_DIR}

ARCH:=$(shell ./tools/arch.exe)
SDL_VERSION:=3.2.16
SDL_LOCATION:=SDL3-${SDL_VERSION}/${ARCH}/bin/SDL3.dll

CFLAGS:=-I SDL3-${SDL_VERSION}/${ARCH}/include
LDFLAGS:=-L SDL3-${SDL_VERSION}/${ARCH}/lib -lSDL3 -mwindows



### START HELLO ####################################################	
HELLO_NAME:=hello
HELLO_DIR:=samples/hello
HELLO_FILENAMES:=hello.c
HELLO_TEMP_DIR:=${TEMP_DIR}/${HELLO_NAME}
HELLO_BUILD_DIR:=${BUILD_DIR}/${HELLO_NAME}
HELLO_OBJECTS:=${patsubst %.c, ${HELLO_TEMP_DIR}/%.o, ${HELLO_FILENAMES}}

hello: ${FOLDERS} ${HELLO_TEMP_DIR} ${HELLO_BUILD_DIR} ${HELLO_OBJECTS} ${HELLO_BUILD_DIR}/SDL3.dll
	# START: $@
	gcc ${HELLO_OBJECTS} -o ${BUILD_DIR}/${HELLO_NAME}/hello.exe ${LDFLAGS}

${HELLO_TEMP_DIR} ${HELLO_BUILD_DIR}:
	# START: $@
	@mkdir -p $@

${HELLO_OBJECTS}: ${TEMP_DIR}/${HELLO_NAME}/%.o: ${HELLO_DIR}/%.c
	# START: $@
	gcc -c $< -o $@ ${CFLAGS}

${HELLO_BUILD_DIR}/SDL3.dll:
	# START: $@
	cp -p ${SDL_LOCATION} $@

run_hello: hello
	./${BUILD_DIR}/${HELLO_NAME}/hello.exe
### END HELLO #####################################################



### START TEST1 ###################################################
TEST1_NAME:=test1
TEST1_DIR:=samples/test1
TEST1_FILENAMES:=main.c
TEST1_TEMP_DIR:=${TEMP_DIR}/${TEST1_NAME}
TEST1_BUILD_DIR:=${BUILD_DIR}/${TEST1_NAME}
TEST1_OBJECTS:=${patsubst %.c, ${TEST1_TEMP_DIR}/%.o, ${TEST1_FILENAMES}}


test1: ${FOLDERS} ${TEST1_TEMP_DIR} ${TEST1_BUILD_DIR} ${BUILD_DIR}/resources ${TEST1_OBJECTS} ${TEST1_BUILD_DIR}/SDL3.dll
	# START: test1
	gcc ${TEST1_OBJECTS} -o ${TEST1_BUILD_DIR}/test1.exe ${LDFLAGS}

${TEST1_OBJECTS}: ${TEST1_TEMP_DIR}/%.o: ${TEST1_DIR}/%.c
	# START: test1 main.o
	gcc -c $< -o $@ ${CFLAGS}

${BUILD_DIR}/resources:
	# START: test1_binaries
	cp -r ${TEST1_DIR}/resources ${TEST1_BUILD_DIR}

${TEST1_BUILD_DIR}/SDL3.dll: 
	cp -p ${SDL_LOCATION} $@

${TEST1_TEMP_DIR} ${TEST1_BUILD_DIR}:
	# START: $@
	@mkdir -p $@
	
run_test1: test1
	./${TEST1_BUILD_DIR}/test1.exe
### END TEST1 #####################################################



### START TEST2 ###################################################
TEST2_NAME:=test2
TEST2_DIR:=samples/test2
TEST2_FILENAMES:=main.c
TEST2_TEMP_DIR:=${TEMP_DIR}/${TEST2_NAME}
TEST2_BUILD_DIR:=${BUILD_DIR}/${TEST2_NAME}
TEST2_OBJECTS:=${patsubst %.c, ${TEST2_TEMP_DIR}/%.o, ${TEST2_FILENAMES}}


test2: ${FOLDERS} ${TEST2_TEMP_DIR} ${TEST2_BUILD_DIR} ${TEST2_OBJECTS} ${TEST2_BUILD_DIR}/SDL3.dll
	# START: test2
	gcc ${TEST2_OBJECTS} -o ${TEST2_BUILD_DIR}/test2.exe ${LDFLAGS}

${TEST2_OBJECTS}: ${TEST2_TEMP_DIR}/%.o: ${TEST2_DIR}/%.c
	# START: test2 main.o
	gcc -c $< -o $@ ${CFLAGS}

${TEST2_BUILD_DIR}/SDL3.dll: 
	cp -p ${SDL_LOCATION} $@

${TEST2_TEMP_DIR} ${TEST2_BUILD_DIR}:
	# START: $@
	@mkdir -p $@
	
run_test2: test2
	./${TEST2_BUILD_DIR}/test2.exe
### END TEST2 #####################################################



.PHONY: clean run_hello run_test1 run_test2
 
 
${FOLDERS}:
	# START: $@
	@mkdir -p $@

 
clean:
	# START: clean
	rm -rf ${BUILD_DIR}
	rm -rf ${TEMP_DIR}