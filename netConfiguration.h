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
    std::vector<LayerConfig> neuronActivationType; // ���������� ���������� ����� � ��� ��������� ������� �� �����


    NetConfiguration( )
        : neuronActivationType()
    {}
};


} // namespace Neural

#endif // NETCONFIGURATION_H
