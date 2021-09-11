#ifndef ITEMIMPL_H
#define ITEMIMPL_H


#include "strategy.h"
#include "types.h"


#include <memory>


namespace Neural {
class Synapse;
class Neuron;
class OutputNeuron;



//==========================================================
class SynapseImpl
//==========================================================
{
public:
    virtual void setState( NET_STATE);
    virtual void input( double&);
    virtual void output( double&);
    virtual void forwardAction() {}
    virtual void backpropAction() {}

public:
    SynapseImpl( Synapse*);
    virtual ~SynapseImpl();

private:
    Synapse* p_owner;
    std::unique_ptr<SynapseState> p_state;
    double m_weight;
    double& r_input;
    double& r_output;
    double m_weightDelta;
    double m_dWeight;

    friend class ForwardSynapseState;
    friend class BackpropSynapseState;
};






//==========================================================
class NeuronImpl
//==========================================================
{
public:
    virtual void setState( NET_STATE) {}
    virtual void input( double&) {}
    virtual void output( double&) {}
    virtual void forwardAction() {}
    virtual void backpropAction() {}

public:
    NeuronImpl( Neuron*);
    virtual ~NeuronImpl();

protected:
    Neuron* p_owner;
    double& r_input;
    double& r_output;

   friend class SigmoidForwardState;
   friend class SigmoidOutputBackpropState;
   friend class SigmoidBackpropState;
   friend class ReLuForwardState;
   friend class ReLuOutputBackpropState;
   friend class ReLuBackpropState;
};





//==========================================================
class NonTypeNeuronImpl : public NeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override {}
    void input( double&) override {}
    void output( double&) override {}
    void forwardAction() override {}
    void backpropAction() override {}

public:
    NonTypeNeuronImpl( Neuron*);
    ~NonTypeNeuronImpl() {}

};




//==========================================================
class NonTypeOutputNeuronImpl : public NonTypeNeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override {}
    void input( double&) override {}
    void output( double&) override {}
    void forwardAction() override {}
    void backpropAction() override {}

public:
    NonTypeOutputNeuronImpl( Neuron* owner) : NonTypeNeuronImpl(owner) {}
    ~NonTypeOutputNeuronImpl() {}
};



//==========================================================
class SigmoidNeuronImpl : public NeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override;
    void input( double&) override;
    void output( double&) override;
    void forwardAction() override;
    void backpropAction() override;

public:
    SigmoidNeuronImpl( Neuron*);
    ~SigmoidNeuronImpl() {}

protected:
    std::unique_ptr<SigmoidState> p_state;
};




//==========================================================
class SigmoidOutputNeuronImpl : public SigmoidNeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override;
    void input( double&) override;
    void output( double&) override;
    void backpropAction() override;

public:
    SigmoidOutputNeuronImpl( OutputNeuron*);
    ~SigmoidOutputNeuronImpl() {}

protected:
    std::unique_ptr<SigmoidState> p_state;

    friend class SigmoidOutputBackpropState;
};





//==========================================================
class ReLuNeuronImpl : public NeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override;
    void input( double&) override;
    void output( double&) override;
    void forwardAction() override;
    void backpropAction() override;

public:
    ReLuNeuronImpl( Neuron* owner);
    ~ReLuNeuronImpl() {}

protected:
    std::unique_ptr<ReLuState> p_state;
};





//==========================================================
class ReLuOutputNeuronImpl : public ReLuNeuronImpl
//==========================================================
{
public:
    void setState( NET_STATE) override;
    void input( double&) override;
    void output( double&) override;
    void backpropAction() override;

public:
    ReLuOutputNeuronImpl( OutputNeuron* owner);
    ~ReLuOutputNeuronImpl() {}

protected:
    std::unique_ptr<ReLuState> p_state;

    friend class ReLuOutputBackpropState;
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^





//==========================================================
class BiasNeuronImpl
//==========================================================
{
public:


public:
    BiasNeuronImpl();
    virtual ~BiasNeuronImpl();

private:

};





//==========================================================
class InputNeuronImpl
//==========================================================
{
public:


public:
    InputNeuronImpl();
    ~InputNeuronImpl();

private:

};


} // namespace Neural

#endif // ITEMIMPL_H
