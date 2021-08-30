#include "itemImpl.h"
#include "item.h"
#include "singleton.h"

using namespace Neural;

//==========================================================
SynapseImpl::SynapseImpl( Synapse* owner)
    : p_owner( owner)
    , p_state( new ForwardSynapseState( this))
    , m_weight( Singleton::instance().getRandom( 0.1, 2.0))
    , r_input ( owner->m_input)
    , r_output ( owner->m_output)
{

}


SynapseImpl::~SynapseImpl()
{

}


void SynapseImpl::setState( ITEM_STATE) {}


void SynapseImpl::input( double& input)
{
    p_state->input( input);
}


void SynapseImpl::output( double& output)
{
    p_state->output( output);
}



//==========================================================
NeuronImpl::NeuronImpl( Neuron* owner)
    : p_owner( owner)
    , r_input ( owner->m_input)
    , r_output ( owner->m_output)
{

}


NeuronImpl::~NeuronImpl()
{

}


NonTypeNeuronImpl::NonTypeNeuronImpl( Neuron* owner) : NeuronImpl( owner) {}


SigmoidNeuronImpl::SigmoidNeuronImpl( Neuron* owner)
    : NeuronImpl( owner)
    , p_state( new SigmoidForwardState( this))

{}


void SigmoidNeuronImpl::input( double& input)
{
    p_state->input( input);
}


void SigmoidNeuronImpl::output( double& output)
{
    p_state->output( output);
}


ReLuNeuronImpl::ReLuNeuronImpl( Neuron* owner) : NeuronImpl( owner) {}




//==========================================================
BiasNeuronImpl::BiasNeuronImpl()
{

}


BiasNeuronImpl::~BiasNeuronImpl()
{

}


//==========================================================
OutputNeuronImpl::OutputNeuronImpl()
{

}


OutputNeuronImpl::~OutputNeuronImpl()
{

}


//==========================================================
InputNeuronImpl::InputNeuronImpl()
{

}


InputNeuronImpl::~InputNeuronImpl()
{

}
