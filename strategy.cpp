#include <cmath>

#include "strategy.h"
#include "itemImpl.h"

using namespace Neural;


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
