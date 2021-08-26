#ifndef NETHOLDER_H
#define NETHOLDER_H

#include "netConfiguration.h"


enum NET_STATE
{
    FORWARD_PASS,
};


using INPUTS_CONTAINER = std::vector<double>;
using OUTPUTS_CONTAINER = std::vector<double>;


class NetHolder
{
public:
    void createNet( const NetConfiguration&);
    void netState( NET_STATE);
    void setInputs( const INPUTS_CONTAINER&);
    void setOutputs( const OUTPUTS_CONTAINER&);
    OUTPUTS_CONTAINER getOutputs();

private:

};

#endif // NETHOLDER_H
