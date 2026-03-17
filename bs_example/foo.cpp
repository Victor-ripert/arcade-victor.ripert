#include "foo.hpp"
#include <iostream>


foo::foo():_type("foo") {}


foo::~foo() {}

std::string foo::getType() {
    return _type;
}


extern "C" {
    IClass *entryPoint() {
        std::cout << "crested foo" << std::endl;
        return new foo();
    };
}