#ifndef NETHOLDER_H
#define NETHOLDER_H

#include "netConfiguration.h"
#include "item.h"

#include <memory>


namespace Neural {



// ====================================================
class INetHolder
{
public:
    virtual void createNet( const netConfiguration_t&) {}
    virtual void netState( NET_STATE) {}
    virtual void setInputs( const inputContainer_t&) {}
    virtual void setOutputs( const outputContainer_t&) {}
    virtual const outputContainer_t& getOutputs() = 0;

    INetHolder() {}
    virtual ~INetHolder() {}
};


// ====================================================
class NetHolder : public INetHolder
{
public:
    void createNet( const netConfiguration_t&) override;
    void netState( NET_STATE) override;
    void setInputs( const inputContainer_t&) override;
    void setOutputs( const outputContainer_t&) override;
    const outputContainer_t& getOutputs() override;

    NetHolder();
    ~NetHolder();

private:
    void createNeurons_( const netConfiguration_t& );
    void createAndAddSynapses_();

private:
    itemPtr_t p_input_node;
    itemPtr_t p_out_node;
    neuronContainer_t c_neurons;
//    outputContainer_t c_outputValue;
    std::vector<double> c_outputValue;
};


} // namespace Neural

#endif // NETHOLDER_H
