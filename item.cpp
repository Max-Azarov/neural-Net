#include "item.h"


//==========================================================
void InputNode::forwardAction() {}
void InputNode::backwardAction() {}

void InputNode::addItem( Item*) {}
void InputNode::removeItem( Item*) {}

InputNode::InputNode()
    : c_itemList()
{
    LOGWRITE("Create InputNode");
}

InputNode::~InputNode()
{
    LOGWRITE("Delete InputNode");
}



//=========================================================
void Synapse::forwardAction() {}
void Synapse::backwardAction() {}

void Synapse::addItem( Item*) {}
void Synapse::removeItem( Item*) {}

Synapse::Synapse()
    : c_itemList()
    , p_impl( new SynapseImpl())
{
    LOGWRITE("Create Synapse");
}

Synapse::~Synapse()
{
    LOGWRITE("Delete Synapse");
}



//==========================================================
void Neuron::forwardAction() {}
void Neuron::backwardAction() {}

void Neuron::addItem( Item*) {}
void Neuron::removeItem( Item*) {}

Neuron::Neuron()
    : c_itemList()
    , p_impl( new NeuronImpl())
{
    LOGWRITE("Create Neuron");
}

Neuron::~Neuron()
{
    LOGWRITE("Delete Neuron");
}



//==========================================================
void BiasNeuron::forwardAction() {}
void BiasNeuron::backwardAction() {}

void BiasNeuron::addItem( Item*) {}
void BiasNeuron::removeItem( Item*) {}

BiasNeuron::BiasNeuron()
    : c_itemList()
    , p_impl( new BiasNeuronImpl())
{
    LOGWRITE("Create BiasNeuron");
}

BiasNeuron::~BiasNeuron()
{
    LOGWRITE("Delete BiasNeuron");
}



//==========================================================
void OutputNeuron::forwardAction() {}
void OutputNeuron::backwardAction() {}

void OutputNeuron::addItem( Item*) {}
void OutputNeuron::removeItem( Item*) {}

OutputNeuron::OutputNeuron()
    : c_itemList()
    , p_impl( new OutputNeuronImpl())
{
    LOGWRITE("Create OutputNeuron");
}

OutputNeuron::~OutputNeuron()
{
    LOGWRITE("Delete OutputNeuron");
}

