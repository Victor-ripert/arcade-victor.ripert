#pragma once

#include <dlfcn.h>
#include <string>

template <typename T>
class DLLoader {
    private:
    void *_handler;

    public:
    DLLoader() {}
    load(const char *lib) {
        if (_handler)
            dlclose(_handler);
        _handler = dlopen(lib, RTLD_LAZY);
        // if (!_handle)
    }
    std::unique_ptr<T> getInstance() {
        void *sym = dlsym(_handler, "entryPoint");
        // if (!sym)
            //error
        //<T *(*)()> is the function;
        auto factory = reinterpret_cast<T *(*)()>(sym);
        return std::unique_ptr<T>(factory());
    }
    ~DLLoader() {
        if (_handler)
            dlclose(_handler);
    }
};
