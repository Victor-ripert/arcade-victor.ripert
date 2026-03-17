#pragma once

#include <dlfcn.h>
#include <string>

template <typename T>
class DLLoader {
    private:
    void *_handler;

    public :
    DLLoader(std::string lib) {
        _handler = dlopen(lib.c_str(), RTLD_LAZY);
        // if (!_handle)
    }
    T *getInstance() {
        void *sym = dlsym(_handler, "entryPoint");
        // if (!sym)
            //error
        //<T *(*)()> is the function;
        auto factory = reinterpret_cast<T *(*)()>(sym);
        return factory();
    };
    ~DLLoader() {
        if (_handler)
            dlclose(_handler);
    }
};
