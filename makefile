NAME        = main
LIB_FOO     = libfoo.so
LIB_BAR     = libbar.so

SRC         = main.cpp
FOO_SRC     = foo.cpp
BAR_SRC     = bar.cpp

OBJ         = $(SRC:.cpp=.o)
FOO_OBJ     = $(FOO_SRC:.cpp=.o)
BAR_OBJ     = $(BAR_SRC:.cpp=.o)

CXX         = g++
CXXFLAGS    = -Wall -Wextra
LIB_FLAGS   = -Wall -Wextra -fPIC

all: $(LIB_FOO) $(LIB_BAR) $(NAME)
	rm -f $(OBJ) $(FOO_OBJ) $(BAR_OBJ)

$(LIB_FOO): $(FOO_OBJ)
	$(CXX) -shared -o $(LIB_FOO) $(FOO_OBJ)

$(LIB_BAR): $(BAR_OBJ)
	$(CXX) -shared -o $(LIB_BAR) $(BAR_OBJ)

$(FOO_OBJ): $(FOO_SRC)
	$(CXX) $(LIB_FLAGS) -c $< -o $@

$(BAR_OBJ): $(BAR_SRC)
	$(CXX) $(LIB_FLAGS) -c $< -o $@

$(NAME): $(LIB_FOO) $(LIB_BAR) $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJ) -ldl

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(FOO_OBJ) $(BAR_OBJ)

fclean: clean
	rm -f $(NAME) $(LIB_FOO) $(LIB_BAR)

re: fclean all
