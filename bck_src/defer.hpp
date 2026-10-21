#pragma once 

#include <functional>
struct Deferable {

    std::function<void()> func;

    Deferable(std::function<void()> defered) :
    func(defered){}

    ~Deferable() {
        func();
    }
};

#define GLUELESS(x, y) x##y
#define GLUE(a) GLUELESS(deffered, a)
#define defer(statement) auto GLUE(__COUNTER__) = Deferable([&]() mutable {statement;})

