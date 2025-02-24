CXX := g++

RAYLIB ?= ./external/raylib-5.5/src/
RAYGUI ?= ./external/raygui-4.0/src/

CFLAGS = -I$(RAYLIB) -I$(RAYGUI) -L$(RAYLIB) -L$(RAYGUI)
LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
DEPFLAGS = -MMD -MP

SDIR := src
BDIR := build

SRCS := $(wildcard $(SDIR)/*.cpp)
OBJS := $(SRCS:$(SDIR)/%.cpp=$(BDIR)/%.o)
DEPS := $(OBJS:%.o=%.d)

EXECUTEABLE := sokoban

build: $(OBJS)
	$(CXX) -o $(BDIR)/$(EXECUTEABLE) $^ $(CFLAGS) $(LIBS)

$(OBJS) : $(BDIR)%.o : $(SDIR)%.cpp
	$(CXX) $(DEPFLAGS) -c $< $(CFLAGS) -o $@ $(LIBS)

-include $(DEPS)

clean:
	rm -rf $(BDIR)/*

run: build
	./$(BDIR)/$(EXECUTEABLE)

