#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>

#include "item.h"
#include "logwrite.h"


namespace Neural {



class Singleton {
public:
    static Singleton& instance()
    {
        static std::unique_ptr<Singleton> s;
        if( !s ) {
            s.reset( new Singleton());
        }
        return *s.get();
    }

    Singleton() { LOGWRITE("create Singleton"); }
    ~Singleton() { LOGWRITE("delete Singleton"); }

    itemPtr_t createSynapse() { return itemPtr_t( new Synapse()); }
    itemPtr_t createNeuron() { return itemPtr_t( new Neuron()); }
    itemPtr_t createBiasNeuron() { return itemPtr_t( new BiasNeuron()); }
    itemPtr_t createOutputNeuron() { return itemPtr_t( new OutputNeuron()); }
    itemPtr_t createInputNode() { return itemPtr_t( new InputNode()); }
    itemPtr_t createInputNeuron() { return itemPtr_t( new InputNeuron()); }
};


} // namespace Neural

#endif // SINGLETON_H
