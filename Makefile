NAME := rt

# Detect the platform
ifeq ($(OS),Windows_NT)
	CXX := g++
	SDL_CFLAGS := -Isrc/include
	SDL_LDFLAGS := -Lsrc/lib
	SDL_LIBS := -lmingw32 -lSDL2main -lSDL2
	EXE := $(NAME).exe
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXX := g++
		SDL_CFLAGS := -I$(HOME)/.local/include/SDL2
		SDL_LDFLAGS := -L$(HOME)/.local/lib
		SDL_LIBS := -lSDL2
		EXE := $(NAME)
	else
		$(error Unsupported platform)
	endif
endif

# Compiler flags
CXXFLAGS := -Wall -Wextra -Werror -std=c++17 -g $(SDL_CFLAGS)
LDFLAGS := $(SDL_LDFLAGS) $(SDL_LIBS)

# Source files
SRC =	main.cpp \
		Window.cpp \
		Image.cpp
OBJ = $(SRC:.cpp=.o)

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE) $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

clean:
	rm -f $(OBJ) $(EXE)

re: clean all
.PHONY: all clean