#ifndef NEURONSTATE_H
#define NEURONSTATE_H


#include <memory>

#include "types.h"


namespace Neural {




// =====================================================================
class NeuronImpl;
// =====================================================================

class SigmoidState
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





class SigmoidForwardState : public SigmoidState
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
class SigmoidOutputNeuronImpl;
// =====================================================================
class SigmoidOutputBackpropState : public SigmoidState
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
class SynapseImpl;
// =====================================================================

class SynapseState
{
public:
    virtual void input( double& ) = 0;
    virtual void output( double& ) = 0;

    SynapseState(SynapseImpl* owner) : p_owner(owner) {}
    virtual ~SynapseState() {}

protected:
    SynapseImpl* p_owner;
};


class ForwardSynapseState : public SynapseState
{
public:
    void input( double& ) override;
    void output( double& ) override;

    ForwardSynapseState(SynapseImpl* owner) : SynapseState( owner) {}
    ~ForwardSynapseState() {}
};


class BackpropSynapseState : public SynapseState
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
