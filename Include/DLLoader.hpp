#pragma once

#include <dlfcn.h>
#include <string>
#include <memory>
#include <stdexcept>

template <typename T>
class DLLoader {
private:
    void *_handler = nullptr;

public:
    DLLoader() {}

    void load(const char *lib) {
        if (_handler)
            dlclose(_handler);
        _handler = dlopen(lib, RTLD_LAZY);
        if (!_handler)
            throw std::runtime_error(dlerror());
    }

    std::unique_ptr<T> getInstance(const std::string &sym = "displayEntryPoint") {
        if (!_handler)
            throw std::runtime_error("No library loaded");
        void *s = dlsym(_handler, sym.c_str());
        if (!s)
            return nullptr;
        auto factory = reinterpret_cast<T *(*)()>(s);
        return std::unique_ptr<T>(factory());
    }

    bool hasSymbol(const std::string &sym) {
        if (!_handler)
            return false;
        return dlsym(_handler, sym.c_str()) != nullptr;
    }

    ~DLLoader() {
        if (_handler)
            dlclose(_handler);
    }
};