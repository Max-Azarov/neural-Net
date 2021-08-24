#include "logwrite.h"
#include "singleton.h"

#include <memory>

int main()
{
    std::unique_ptr<Synapse> synapse = Singleton::instance().createSynapse();
    std::unique_ptr<Neuron> neuron = Singleton::instance().createNeuron();
    std::unique_ptr<BiasNeuron> biasNeuron = Singleton::instance().createBiasNeuron();
    LOGWRITE(synapse->getType());
    LOGWRITE(neuron->getType());
    LOGWRITE(biasNeuron->getType());
    return 0;
}
