#include "logwrite.h"
#include "singleton.h"

#include <memory>

int main()
{
    std::unique_ptr<Synapse> synapse = Singleton::instance().createSynapse();
    std::unique_ptr<Neuron> neuron = Singleton::instance().createNeuron();
    std::unique_ptr<BiasNeuron> biasNeuron = Singleton::instance().createBiasNeuron();
    std::unique_ptr<OutputNeuron> outputNeuron = Singleton::instance().createOutputNeuron();
    std::unique_ptr<InputNode> InputNode = Singleton::instance().createInputNode();
    LOGWRITE(synapse->getType());
    LOGWRITE(neuron->getType());
    LOGWRITE(biasNeuron->getType());
    LOGWRITE(outputNeuron->getType());
    LOGWRITE(InputNode->getType());
    return 0;
}
