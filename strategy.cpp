#include <cmath>
#include "algorithm"

#include "strategy.h"
#include "itemImpl.h"
#include "netHolder.h"
#include "singleton.h"

using namespace Neural;


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
//    LOGWRITE_TEXT( std::string(__func__) + std::string("\n"));
    out = p_owner->r_output;
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^


// =====================================================================
// =====================================================================
void SigmoidBackpropState::input( double& in)
{
    p_owner->r_input = in;
    p_owner->r_output = 1.0 / (1.0 + exp(-in));
}


void SigmoidBackpropState::output( double& out)
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
//    LOGWRITE_VALUE( out);
//    LOGWRITE_VALUE( p_owner->r_output);
    double grad = out * p_owner->r_input;
    double E = Singleton::instance().getRandValue(0.1);
    double A = Singleton::instance().getRandValue(0.03);
    p_owner->m_dWeight = E * grad + A * p_owner->m_dWeight;
    p_owner->m_weight += p_owner->m_dWeight;
    p_owner->m_weightDelta = p_owner->m_weight * out;
//    LOGWRITE_VALUE( p_owner->m_weight);
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^





// =====================================================================
// =====================================================================
SigmoidOutputBackpropState::SigmoidOutputBackpropState(NeuronImpl* owner)
    : SigmoidState(owner)
    , m_idealOutput()
{}

void SigmoidOutputBackpropState::input( double& in)
{
    in = m_delta;
}


void SigmoidOutputBackpropState::output( double& out)
{
    m_idealOutput = out;
    double output = p_owner->r_output;
    m_delta = (m_idealOutput - output) * (1 - output) * output;
//    LOGWRITE_VALUE( m_delta);
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
//    LOGWRITE_TEXT("Backprop run\n");
    // Подаем идеальные значения на выходы сети
    auto lastLayer = p_owner->c_neurons.rbegin();
    auto itOutputs = p_owner->c_outputValue.begin();
    std::for_each(lastLayer->begin(), lastLayer->end(), [&](Item* item)
    {
//        LOGWRITE("Test line\n");
        double temp = *itOutputs++;
        item->output( temp);
    });

    // Запускаем обратный проход
    p_owner->p_input_node->backpropAction();
}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
