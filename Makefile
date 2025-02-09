RAYLIB ?= ./external/raylib-5.5/src/
RAYGUI ?= ./external/raygui-4.0/src/
INC = ./src/include/

build-main: build-dir
	g++ src/main.cpp -o build/main -I $(RAYLIB) -I $(RAYGUI) -I $(INC) -L $(RAYLIB) -L $(RAYGUI) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11

build-dir:
	if [ ! -d build ]; then mkdir build; fi

run: build-main
	./build/main
