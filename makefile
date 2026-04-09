NAME        = arcade

CXX         = g++
CXXFLAGS    = -std=c++17 -g -Wall -Wextra -fPIC
INCLUDES    = -IInclude

# --- Core ---
CORE_SRC    = Core/main.cpp Core/Core.cpp Core/Menu.cpp
CORE_OBJ    = $(CORE_SRC:.cpp=.o)

# --- Graphics libs ---
GRAPH_LIBS  = lib/sfml.so \
              lib/ncurses.so \
              lib/sdl.so

# --- Game libs ---
GAME_LIBS   = lib/snake.so \
              lib/nibbler.so

# ------------------------------------------------

all: core graphicals games

core: $(NAME)

$(NAME): $(CORE_OBJ)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^ -ldl

graphicals: $(GRAPH_LIBS)

lib/sfml.so: Graphics/SFML.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o $@ $^ -lsfml-graphics -lsfml-window -lsfml-system

lib/ncurses.so: Graphics/NCurses.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o $@ $^ -lncurses

lib/sdl.so: Graphics/SDL.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o $@ $^ -lSDL2

games: $(GAME_LIBS)

lib/snake.so: Games/Snake/Snake.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o $@ $^

lib/nibbler.so: Games/Nibbler/Nibbler.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -shared -o $@ $^

# --- Generic object rule ---
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# ------------------------------------------------

clean:
	rm -f $(CORE_OBJ)

fclean: clean
	rm -f $(NAME) $(GRAPH_LIBS) $(GAME_LIBS)

re: fclean all

.PHONY: all core graphicals games clean fclean re