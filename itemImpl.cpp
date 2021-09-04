#include <algorithm>

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
    , m_weightDelta()
    , m_dWeight()
{

}


SynapseImpl::~SynapseImpl()
{

}


void SynapseImpl::setState( NET_STATE state)
{
    if( state == FORWARD)
    {
        p_state.reset( new ForwardSynapseState( this));
    }
    else if( state == BACKPROP)
    {
        p_state.reset( new BackpropSynapseState( this));
    }
}


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


void SigmoidNeuronImpl::setState( NET_STATE state)
{
    if( state == FORWARD)
    {
        p_state.reset( new SigmoidForwardState( this));
    }
    else if( state == BACKPROP)
    {
        p_state.reset( new SigmoidBackpropState( this));
    }
}


void SigmoidNeuronImpl::input( double& input)
{
    p_state->input( input);
}


void SigmoidNeuronImpl::output( double& output)
{
    p_state->output( output);
}


void SigmoidNeuronImpl::forwardAction()
{
    // Вычисляем суммарный сигнал со всех входных синапсов
    double sum = 0;
    double tempDouble = 0;
    sum = std::accumulate( p_owner->c_itemListParent.begin(),
                           p_owner->c_itemListParent.end(),
                           0.0,
                           [&]( double x, const itemPtr_t& pItem)
    {
        pItem->output( tempDouble);
        return x + tempDouble;
    });

    // Подаем полученное значение на вход нейрона
    input( sum);

    // Передаем значение выхода в синапсы
    std::for_each( p_owner->c_itemListChild.begin(),
                   p_owner->c_itemListChild.end(),
                   [&]( const itemPtr_t& pItem)
    {
        output( tempDouble);
        pItem->input( tempDouble);
    });
}


void SigmoidNeuronImpl::backpropAction()
{
    // Вычисляем суммарное значение весов - дельт синапсов
    double sum = 0;
    double tempDouble = 0;
    sum = std::accumulate( p_owner->c_itemListChild.begin(),
                           p_owner->c_itemListChild.end(),
                           0.0,
                           [&]( double x, const itemPtr_t& pItem)
    {
        pItem->input( tempDouble);
        return x + tempDouble;
    });

    // Вычисляем дельта нейрона
    double delta = sum * (1 - p_owner->m_output) * p_owner->m_output;

    // Передаем значение дельта в синапсы
    std::for_each( p_owner->c_itemListParent.begin(),
                   p_owner->c_itemListParent.end(),
                   [&]( const itemPtr_t& pItem)
    {
        pItem->output( delta);
    });
}


//==========================================================
SigmoidOutputNeuronImpl::SigmoidOutputNeuronImpl( OutputNeuron* owner)
    : SigmoidNeuronImpl( owner)
    , p_state( new SigmoidForwardState( this))
{}


void SigmoidOutputNeuronImpl::setState( NET_STATE state)
{
    if( state == FORWARD)
    {
        p_state.reset( new SigmoidForwardState( this));
    }
    else if( state == BACKPROP)
    {
        p_state.reset( new SigmoidOutputBackpropState( this));
    }
}


void SigmoidOutputNeuronImpl::backpropAction()
{
    // Передаем значение дельта в синапсы
    std::for_each( p_owner->c_itemListParent.begin(),
                   p_owner->c_itemListParent.end(),
                   [&]( const itemPtr_t& pItem)
    {
        pItem->output( p_state->m_delta);
    });
}


void SigmoidOutputNeuronImpl::input( double& input)
{
    p_state->input( input);
}


void SigmoidOutputNeuronImpl::output( double& output)
{
//    LOGWRITE_TEXT( std::string(__func__) + std::string("\n"));
    p_state->output( output);
}


//ReLuNeuronImpl::ReLuNeuronImpl( Neuron* owner) : NeuronImpl( owner) {}



//==========================================================
BiasNeuronImpl::BiasNeuronImpl()
{

}


BiasNeuronImpl::~BiasNeuronImpl()
{

}





//==========================================================
InputNeuronImpl::InputNeuronImpl()
{

}


InputNeuronImpl::~InputNeuronImpl()
{

}
