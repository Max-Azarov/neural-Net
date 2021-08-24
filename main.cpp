#include "logwrite.h"
#include "singleton.h"

#include <memory>

int main()
{
    std::unique_ptr<Synapse> synapse = Singleton::instance().createSynapse();
    std::unique_ptr<Neuron> neuron = Singleton::instance().createNeuron();
    LOGWRITE(synapse->getType());
    LOGWRITE(neuron->getType());
    return 0;
}
