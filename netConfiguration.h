#ifndef NETCONFIGURATION_H
#define NETCONFIGURATION_H

#include <vector>

#include "types.h"

namespace Neural {








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


struct NetConfiguration
{
    std::vector<LayerConfig> neuronActivationType; // Определяет количество слоев и тип активации каждого из слоев


    NetConfiguration( )
        : neuronActivationType()
    {}
};


} // namespace Neural

#endif // NETCONFIGURATION_H
