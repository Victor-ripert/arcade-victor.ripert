NAME     = arcade
CXX      = g++
FLAGS    = -std=c++17 -g -Wall -Wextra -fPIC -IInclude

CORE_OBJ = Core/main.o Core/Core.o Core/Menu.o

all: core graphicals games

# --- Core ---
core: $(CORE_OBJ)
	$(CXX) $(FLAGS) -o $(NAME) $(CORE_OBJ) -ldl

# --- Graphics ---
graphicals:
	$(CXX) $(FLAGS) -shared Graphics/SFML/SFML.cpp \
		-o lib/arcade_sfml.so \
		-lsfml-graphics -lsfml-window -lsfml-system
	$(CXX) $(FLAGS) $(shell sdl2-config --cflags) -shared Graphics/Sdl2/arcade_sdl2.cpp \
		-o lib/arcade_sdl2.so \
		$(shell sdl2-config --libs) -lSDL2_ttf
	$(CXX) $(FLAGS) -shared Graphics/NCurses/NCurses.cpp \
		-o lib/arcade_ncurses.so \
		-lncurses

# --- Games ---
games:
	$(CXX) $(FLAGS) -shared Games/Nibbler/Nibbler.cpp -o lib/arcade_nibbler.so

# --- Generic object rule ---
%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME) lib/arcade_sfml.so lib/arcade_sdl2.so lib/arcade_nibbler.so lib/arcade_ncurses.so

re: fclean all

.PHONY: all core graphicals games clean fclean re