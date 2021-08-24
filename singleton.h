#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

#include "item.h"

class Singleton {
public:
    static Singleton& instance()
    {
        static Singleton* s;
        if( s == nullptr) {
            s = new Singleton();
        }
        return *s;
    }

    std::unique_ptr<Synapse> createSynapse() { return std::unique_ptr<Synapse>(new Synapse()); }
};


#endif // SINGLETON_H
