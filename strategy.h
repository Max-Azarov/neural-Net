#ifndef NEURONSTATE_H
#define NEURONSTATE_H


#include <memory>

#include "types.h"


namespace Neural {
class NeuronImpl;



// =====================================================================
class SigmoidState
// =====================================================================
{
public:
    virtual void input( double& ) = 0;
    virtual void output( double& ) = 0;

public:

    SigmoidState(NeuronImpl* owner);
    virtual ~SigmoidState() {}

protected:
    NeuronImpl* p_owner;
    double m_delta;

    friend class SigmoidOutputNeuronImpl;
};




// =====================================================================
class SigmoidForwardState : public SigmoidState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    SigmoidForwardState(NeuronImpl* owner) : SigmoidState(owner) {}
    ~SigmoidForwardState() {}
};


class SigmoidBackpropState : public SigmoidState
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    SigmoidBackpropState(NeuronImpl* owner) : SigmoidState(owner) {}
    ~SigmoidBackpropState() {}
};



// =====================================================================
class SigmoidOutputBackpropState : public SigmoidState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    SigmoidOutputBackpropState(NeuronImpl* owner);
    ~SigmoidOutputBackpropState() {}

private:
    double m_idealOutput;
};



// =====================================================================
class ReLuState
// =====================================================================
{
public:
    virtual void input( double& ) = 0;
    virtual void output( double& ) = 0;

public:
    ReLuState(NeuronImpl* owner);
    virtual ~ReLuState() {}

protected:
    NeuronImpl* p_owner;
    double m_delta;
    double m_k;

    friend class ReLuOutputNeuronImpl;
};




// =====================================================================
class ReLuForwardState : public ReLuState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    ReLuForwardState(NeuronImpl* owner) : ReLuState(owner) {}
    ~ReLuForwardState() {}
};



// =====================================================================
class ReLuBackpropState : public ReLuState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    ReLuBackpropState(NeuronImpl* owner) : ReLuState(owner) {}
    ~ReLuBackpropState() {}
};



// =====================================================================
class ReLuOutputBackpropState : public ReLuState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

public:
    ReLuOutputBackpropState(NeuronImpl* owner) : ReLuState( owner), m_idealOutput() {}
    ~ReLuOutputBackpropState() {}

private:
    double m_idealOutput;
};




//
class SynapseImpl;

// =====================================================================
class SynapseState
// =====================================================================
{
public:
    virtual void input( double& ) = 0;
    virtual void output( double& ) = 0;

    SynapseState(SynapseImpl* owner) : p_owner(owner) {}
    virtual ~SynapseState() {}

protected:
    SynapseImpl* p_owner;
};



// =====================================================================
class ForwardSynapseState : public SynapseState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

    ForwardSynapseState(SynapseImpl* owner) : SynapseState( owner) {}
    ~ForwardSynapseState() {}
};



// =====================================================================
class BackpropSynapseState : public SynapseState
// =====================================================================
{
public:
    void input( double& ) override;
    void output( double& ) override;

    BackpropSynapseState(SynapseImpl* owner) : SynapseState( owner) {}
    ~BackpropSynapseState() {}
};





// =====================================================
class NetHolder;
// =====================================================

class NetHolderState
{
public:
    virtual void run() = 0;

    NetHolderState() {}
    virtual ~NetHolderState() {}

protected:

};


// =====================================================
class NetHolderForwardState : public NetHolderState
{
public:
    void run() override;

    NetHolderForwardState( NetHolder* owner)  : p_owner(owner) {}
    virtual ~NetHolderForwardState() {}

private:
    NetHolder* p_owner;
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// =====================================================
class NetHolderBackpropState : public NetHolderState
{
public:
    void run() override;

    NetHolderBackpropState( NetHolder* owner)  : p_owner(owner) {}
    virtual ~NetHolderBackpropState() {}

private:
    NetHolder* p_owner;
};
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




} // namespace Neural

#endif // NEURONSTATE_H
