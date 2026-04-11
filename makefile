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
	$(CXX) $(FLAGS) -shared Graphics/SFML.cpp    -o lib/arcade_sfml.so    -lsfml-graphics -lsfml-window -lsfml-system

# --- Games ---
games:

# --- Generic object rule ---
%.o: %.cpp
	$(CXX) $(FLAGS) -c $< -o $@

# --- Cleanup ---
clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME) lib/sfml.so lib/ncurses.so lib/sdl.so lib/snake.so lib/nibbler.so

re: fclean all

.PHONY: all core graphicals games clean fclean re