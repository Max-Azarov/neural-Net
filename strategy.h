#ifndef NEURONSTATE_H
#define NEURONSTATE_H


#include <memory>



namespace Neural {


// =====================================================================
class NeuronImpl;

class SigmoidState {
public:
    virtual void input( double& ) = 0;
    virtual void output( double& ) = 0;

public:
    SigmoidState(NeuronImpl* owner) : p_owner(owner) {}
    virtual ~SigmoidState() {}

protected:
    NeuronImpl* p_owner;
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


// =====================================================================
class SynapseImpl;

class SynapseState {
public:
    virtual void input( double& ){}
    virtual void output( double& ){}

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


} // namespace Neural

#endif // NEURONSTATE_H
