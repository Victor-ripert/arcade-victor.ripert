#include "../Include/Core.hpp"

int main(int argc, char **argv) {
    if (argc <= 1) {
        std::cout << "Usage: ./arcade {graphic libary}" << std::endl;
        return 84;
    }
    arcade::Core core(argv[1]);
    core.run();
    return 0;
}