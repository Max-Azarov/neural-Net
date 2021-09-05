#include <cmath>
#include "algorithm"

#include "strategy.h"
#include "itemImpl.h"
#include "netHolder.h"
#include "singleton.h"

using namespace Neural;






// =====================================================================
// =====================================================================
SigmoidState::SigmoidState(NeuronImpl* owner)
    : p_owner(owner)
    , m_delta()
{}


// =====================================================================
// =====================================================================
void SigmoidForwardState::input( double& in)
{
    p_owner->r_input = in;
    p_owner->r_output = 1.0 / (1.0 + exp(-in));
}


void SigmoidForwardState::output( double& out)
{
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// =====================================================================
// =====================================================================
void SigmoidBackpropState::input( double& delta)
{
    delta = delta * (1 - p_owner->r_output) * p_owner->r_output;
}


void SigmoidBackpropState::output( double& out)
{
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// =====================================================================
// =====================================================================
SigmoidOutputBackpropState::SigmoidOutputBackpropState(NeuronImpl* owner)
    : SigmoidState(owner)
    , m_idealOutput()
{}

void SigmoidOutputBackpropState::input( double& delta)
{
    delta = m_delta;
}


void SigmoidOutputBackpropState::output( double& out)
{
    m_idealOutput = out;
    double output = p_owner->r_output;
    m_delta = (m_idealOutput - output) * (1 - output) * output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




// =====================================================================
// =====================================================================
ReLuState::ReLuState(NeuronImpl* owner)
    : p_owner(owner)
    , m_delta()
    , m_k(1.0)
{}


// =====================================================================
// =====================================================================
void ReLuForwardState::input( double& in)
{
    p_owner->r_input = in;

//    double ratio = m_k;
    double ratio = Singleton::instance().getRandValue( m_k);
    if( in > 0)
    {
        p_owner->r_output = ratio * in;
    }
    else
    {
        p_owner->r_output = ratio * 0.1 * in;
    }
}


void ReLuForwardState::output( double& out)
{
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// =====================================================================
// =====================================================================
void ReLuBackpropState::input( double& delta)
{
//    double ratio = m_k;
    double ratio = Singleton::instance().getRandValue( m_k);
    if( p_owner->r_input > 0)
    {
        delta = delta * ratio;
    }
    else
    {
        delta = delta * ratio * 0.1;
    }
}


void ReLuBackpropState::output( double& out)
{
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// =====================================================================
// =====================================================================
void ReLuOutputBackpropState::input( double& in)
{
    in = m_delta;
}


void ReLuOutputBackpropState::output( double& idealOut)
{
    m_idealOutput = idealOut;
    double output = p_owner->r_output;

    double ratio = m_k;
//    double ratio = Singleton::instance().getRandValue( m_k);
    if( p_owner->r_input > 0)
    {
        m_delta = (m_idealOutput - output) * ratio;
    }
    else
    {
        m_delta = (m_idealOutput - output) * ratio * 0.1;
    }
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^




// =====================================================================
// =====================================================================
void ForwardSynapseState::input( double& in)
{
    p_owner->r_input = in;
    p_owner->r_output = in * p_owner->m_weight;
}


void ForwardSynapseState::output( double& out)
{
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// =====================================================================
// =====================================================================
void BackpropSynapseState::input( double& in)
{
    in = p_owner->m_weightDelta;
}


void BackpropSynapseState::output( double& out)
{
    double grad = out * p_owner->r_input;
    double E = Singleton::instance().getRandValue( Singleton::instance().getE());
    double A = Singleton::instance().getRandValue( Singleton::instance().getA());
    p_owner->m_dWeight = E * grad + A * p_owner->m_dWeight;
//    p_owner->m_dWeight = Singleton::instance().getE() * grad + Singleton::instance().getA() * p_owner->m_dWeight;
    p_owner->m_weight += p_owner->m_dWeight;
    p_owner->m_weightDelta = p_owner->m_weight * out;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^





// =====================================================
// =====================================================
void NetHolderForwardState::run()
{
    // Подаем значения на входы сети
    auto itLayer = p_owner->c_neurons.begin();
    auto itInputs = p_owner->c_inputValue.begin();
    std::for_each(itLayer->begin(), itLayer->end(), [&](Item* item)
    {
        double temp = *itInputs++;
        item->input( temp);
    });

    // Запускаем прямой проход
    p_owner->p_input_node->forwardAction();
//    p_owner->p_input_node->show();

    // Записываем значения выходов НС в выходной массив
    std::transform( p_owner->c_neurons.rbegin()->begin(),
                    p_owner->c_neurons.rbegin()->end(),
                    p_owner->c_outputValue.begin(),
                    []( Item* item)
    {
        double temp = 0.0;
        item->output( temp);
        return temp;
    });
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^



// =====================================================
// =====================================================
void NetHolderBackpropState::run()
{
    // Подаем идеальные значения на выходы сети
    auto lastLayer = p_owner->c_neurons.rbegin();
    auto itOutputs = p_owner->c_outputValue.begin();
    std::for_each(lastLayer->begin(), lastLayer->end(), [&](Item* item)
    {
        double temp = *itOutputs++;
        item->output( temp);
    });

    // Запускаем обратный проход
    p_owner->p_input_node->backpropAction();
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
