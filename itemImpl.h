#ifndef ITEMIMPL_H
#define ITEMIMPL_H


#include "strategy.h"
#include "types.h"


#include <memory>


namespace Neural {



//==========================================================
class Synapse;

class SynapseImpl
{
public:
    virtual void setState( ITEM_STATE);
    virtual void input( double&);
    virtual void output( double&);

public:
    SynapseImpl( Synapse*);
    virtual ~SynapseImpl();

private:
    Synapse* p_owner;
    std::unique_ptr<SynapseState> p_state;
    double m_weight;
    double& r_input;
    double& r_output;

    friend class ForwardSynapseState;
};



// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
// =========================================================
class Neuron;

class NeuronImpl
{
public:
    virtual void setState( ITEM_STATE) {}
    virtual void input( double&) {}
    virtual void output( double&) {}

public:
    NeuronImpl( Neuron*);
    virtual ~NeuronImpl();

private:
    Neuron* p_owner;
    double& r_input;
    double& r_output;

   friend class SigmoidForwardState;
};

//==========================================================
class NonTypeNeuronImpl : public NeuronImpl
{

public:
    NonTypeNeuronImpl( Neuron*);
    ~NonTypeNeuronImpl() {}

};

//==========================================================
class SigmoidNeuronImpl : public NeuronImpl
{
public:
    virtual void setState( ITEM_STATE) {}
    virtual void input( double&);
    virtual void output( double&);

public:
    SigmoidNeuronImpl( Neuron*);
    ~SigmoidNeuronImpl() {}

private:
    std::unique_ptr<SigmoidState> p_state;


};

//==========================================================
class ReLuNeuronImpl : public NeuronImpl
{

public:
    ReLuNeuronImpl( Neuron*);
    ~ReLuNeuronImpl() {}

};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




//==========================================================
class BiasNeuronImpl
{
public:


public:
    BiasNeuronImpl();
    virtual ~BiasNeuronImpl();

private:

};



//==========================================================
class OutputNeuronImpl
{
public:


public:
    OutputNeuronImpl();
    ~OutputNeuronImpl();

private:

};



//==========================================================
class InputNeuronImpl
{
public:


public:
    InputNeuronImpl();
    ~InputNeuronImpl();

private:

};


} // namespace Neural

#endif // ITEMIMPL_H
