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
	$(CXX) $(FLAGS) -shared Graphics/arcade_sdl2.cpp -o lib/arcade_sdl2.so -lSDL2 -lSDL2_ttf

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
	rm -f $(NAME) lib/arcade_sfml.so lib/arcade_sdl2.so lib/arcade_nibbler.so

re: fclean all

.PHONY: all core graphicals games clean fclean re