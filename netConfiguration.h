#ifndef NETCONFIGURATION_H
#define NETCONFIGURATION_H

#include <vector>

namespace Neural {




enum NET_TYPE
{
    FULLY_CONNECTED,
};



enum NEURON_TYPE_ACTIVATION
{
    NON_TYPE,
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


    LayerConfig( unsigned int num, NEURON_TYPE_ACTIVATION act = SIGMOID)
        : numOfNeuron(num)
        , activationType(act)
    {}
};


using netConfiguration_t = std::vector<LayerConfig>;


struct NetConfiguration
{
    std::vector<LayerConfig> neuronActivationType; // Определяет количество слоев и тип активации каждого из слоев


    NetConfiguration( )
        : neuronActivationType()
    {}
};


} // namespace Neural

#endif // NETCONFIGURATION_H
