#ifndef NETCONFIGURATION_H
#define NETCONFIGURATION_H

#include <vector>




enum NET_TYPE
{
    FULLY_CONNECTED,
};



enum NEURON_TYPE_ACTIVATION
{
    SIGMOID,
    RELU,
};



struct LayerConfig
{
    unsigned int numOfNeuron;
    NEURON_TYPE_ACTIVATION activationType;


    LayerConfig()
        : numOfNeuron()
        , activationType(SIGMOID)
    {}
};



struct NetConfiguration
{
    unsigned int numOfInputs;
    unsigned int numOfOutputs;
    std::vector<LayerConfig> neuronActivationType; // Определяет количество скрытых слоев и тип активации каждого из слоев


    NetConfiguration()
        : numOfInputs()
        , numOfOutputs()
        , neuronActivationType()
    {}
};




#endif // NETCONFIGURATION_H
