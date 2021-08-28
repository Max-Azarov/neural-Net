#ifndef NETHOLDER_H
#define NETHOLDER_H

#include "netConfiguration.h"
#include "item.h"

#include <memory>


namespace Neural {




enum NET_STATE
{
    FORWARD_PASS,
};


using inputContainer_t = std::vector<double>;
using outputContainer_t = std::vector<double>;
using neuronContainer_t = std::vector<std::vector<Item*>>;



// ====================================================
class INetHolder
{
public:
    virtual void createNet( const netConfiguration_t&) {}
    virtual void netState( NET_STATE) {}
    virtual void setInputs( const inputContainer_t&) {}
    virtual void setOutputs( const outputContainer_t&) {}
    virtual outputContainer_t getOutputs() {}

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
    outputContainer_t getOutputs() override;

    NetHolder();
    ~NetHolder();

private:
    void createNeurons_( const netConfiguration_t& );
    void createAndAddSynapses_();

private:
    itemPtr_t p_node;
    neuronContainer_t c_neurons;
};


} // namespace Neural

#endif // NETHOLDER_H
