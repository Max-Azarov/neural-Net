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
    LOGWRITE_TEXT("Create InputNode\n");
}


InputNode::~InputNode()
{
    LOGWRITE_TEXT("Delete InputNode\n");
}


void InputNode::forwardAction() {}
void InputNode::backwardAction() {}


void InputNode::removeItem( Item*) {}





//=========================================================
Synapse::Synapse()
    : Item()
    , p_impl( new SynapseImpl())
{
    LOGWRITE_TEXT("Create Synapse: ");
    LOGWRITE_VALUE( this);
}


Synapse::~Synapse()
{
    LOGWRITE_TEXT("Delete Synapse: ");
    LOGWRITE_VALUE( this);
}


void Synapse::forwardAction() {}
void Synapse::backwardAction() {}

void Synapse::removeItem( Item*) {}





//==========================================================
Neuron::Neuron()
    : Item()
    , p_impl( new NeuronImpl())
{
    LOGWRITE_TEXT("Create Neuron\n");
}


Neuron::~Neuron()
{
    LOGWRITE_TEXT("Delete Neuron\n");
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
    LOGWRITE_TEXT("Create BiasNeuron\n");
}


BiasNeuron::~BiasNeuron()
{
    LOGWRITE_TEXT("Delete BiasNeuron\n");
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
    LOGWRITE_TEXT("Create OutputNeuron\n");
}


OutputNeuron::~OutputNeuron()
{
    LOGWRITE_TEXT("Delete OutputNeuron\n");
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
    LOGWRITE_TEXT("Create InputNeuron\n");
}


InputNeuron::~InputNeuron()
{
    LOGWRITE_TEXT("Delete InputNeuron\n");
}


void InputNeuron::forwardAction() {}
void InputNeuron::backwardAction() {}


void InputNeuron::removeItem( Item*) {}



