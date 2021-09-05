#ifndef NETHOLDER_H
#define NETHOLDER_H

#include "item.h"
#include "strategy.h"

#include <memory>


namespace Neural {



// ====================================================
class INetHolder
{
public:
    virtual void createNet( const netConfiguration_t&) {}
    virtual void setNetState( NET_STATE) {}
    virtual inputContainer_t& inputs() = 0;
    virtual outputContainer_t& outputs() = 0;
    virtual void run() = 0;

    INetHolder() {}
    virtual ~INetHolder() {}
};


// ====================================================
class NetHolder : public INetHolder
{
public:
    void createNet( const netConfiguration_t&) override;
    void setNetState( NET_STATE) override;
    inputContainer_t& inputs() override;
    outputContainer_t& outputs() override;
    void run() override;

    NetHolder();
    ~NetHolder();

private:
    void createNeurons_( const netConfiguration_t& );
    void createAndAddSynapses_();

private:
    itemPtr_t p_input_node;
    neuronContainer_t c_neurons;
    inputContainer_t c_inputValue;
    outputContainer_t c_outputValue;
    std::unique_ptr<NetHolderState> p_netHolderState;

    friend class NetHolderForwardState;
    friend class NetHolderBackpropState;
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^






} // namespace Neural

#endif // NETHOLDER_H
