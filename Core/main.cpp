#include "../Include/Core.hpp"

int main(int argc, char **argv) {

    arcade::Core core(argv[1]);
    core.run();
    return 0;
}