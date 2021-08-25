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
    std::unique_ptr<Neuron> createNeuron() { return std::unique_ptr<Neuron>(new Neuron()); }
    std::unique_ptr<BiasNeuron> createBiasNeuron() { return std::unique_ptr<BiasNeuron>(new BiasNeuron()); }
    std::unique_ptr<OutputNeuron> createOutputNeuron() { return std::unique_ptr<OutputNeuron>(new OutputNeuron()); }
};


#endif // SINGLETON_H
