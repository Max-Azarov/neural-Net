#include "item.h"


using namespace Neural;


//==========================================================
Item::Item()
    : c_itemListChild()
    , c_itemListParent()
    , m_location()
{
}

Item::~Item()
{
}


void Item::forwardAction() {}
void Item::backwardAction() {}


void Item::addChild( itemPtr_t pItem)
{
    c_itemListChild.emplace_back( std::move( pItem));
}

void Item::addParent( itemPtr_t pItem)
{
    c_itemListParent.emplace_back( std::move( pItem));
}

void Item::removeItem( Item*) { }

ITEM_TYPE Item::getType() { return BASIC_ITEM; }




//==========================================================
InputNode::InputNode()
    : Item()
{
    LOGWRITE("Create InputNode");
}


InputNode::~InputNode()
{
    LOGWRITE("Delete InputNode");
}


void InputNode::forwardAction() {}
void InputNode::backwardAction() {}


void InputNode::removeItem( Item*) {}





//=========================================================
Synapse::Synapse()
    : Item()
    , p_impl( new SynapseImpl())
{
    LOGWRITE("Create Synapse");
}


Synapse::~Synapse()
{
    LOGWRITE("Delete Synapse");
}


void Synapse::forwardAction() {}
void Synapse::backwardAction() {}

void Synapse::removeItem( Item*) {}





//==========================================================
Neuron::Neuron()
    : Item()
    , p_impl( new NeuronImpl())
{
    LOGWRITE("Create Neuron");
}


Neuron::~Neuron()
{
    LOGWRITE("Delete Neuron");
}


void Neuron::forwardAction() {}
void Neuron::backwardAction() {}

//void Neuron::addChild( Item*) {}
//void Neuron::addParent( Item*) {}
void Neuron::removeItem( Item*) {}





//==========================================================
BiasNeuron::BiasNeuron()
    : Item()
    , p_impl( new BiasNeuronImpl())
{
    LOGWRITE("Create BiasNeuron");
}


BiasNeuron::~BiasNeuron()
{
    LOGWRITE("Delete BiasNeuron");
}


void BiasNeuron::forwardAction() {}
void BiasNeuron::backwardAction() {}

//void BiasNeuron::addChild( Item*) {}
//void BiasNeuron::addParent( Item*) {}
void BiasNeuron::removeItem( Item*) {}




//==========================================================
OutputNeuron::OutputNeuron()
    : Item()
    , p_impl( new OutputNeuronImpl())
{
    LOGWRITE("Create OutputNeuron");
}


OutputNeuron::~OutputNeuron()
{
    LOGWRITE("Delete OutputNeuron");
}


void OutputNeuron::forwardAction() {}
void OutputNeuron::backwardAction() {}

//void OutputNeuron::addChild( Item*) {}
//void OutputNeuron::addParent( Item*) {}
void OutputNeuron::removeItem( Item*) {}






//==========================================================
InputNeuron::InputNeuron()
    : Item()
    , p_impl( new InputNeuronImpl())
{
    LOGWRITE("Create InputNeuron");
}


InputNeuron::~InputNeuron()
{
    LOGWRITE("Delete InputNeuron");
}


void InputNeuron::forwardAction() {}
void InputNeuron::backwardAction() {}


void InputNeuron::removeItem( Item*) {}



