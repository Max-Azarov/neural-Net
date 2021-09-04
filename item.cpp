#include "item.h"

#include "algorithm"


#include <functional>
#include <numeric>


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

void Item::show()
{
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->show(); });
}


void Item::forwardAction()
{
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->forwardAction(); });
}


void Item::setState( NET_STATE state)
{
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->setState( state); });
}


void Item::backpropAction()
{
//    std::for_each(c_itemListChild.rbegin(), c_itemListChild.rend(), []( const itemPtr_t& pItem){ pItem->backpropAction(); });
}


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
Node::Node()
    : Item()
{
//    LOGWRITE_TEXT("Create Node\n");
}


Node::~Node()
{
//    LOGWRITE_TEXT("Delete Node\n");
}


void Node::backpropAction()
{
    std::for_each(c_itemListChild.rbegin(), c_itemListChild.rend(), []( const itemPtr_t& pItem){ pItem->backpropAction(); });
}


//void Node::forwardAction() {}
//void Node::backpropAction() {}


void Node::removeItem( Item*) {}





//=========================================================
Synapse::Synapse()
    : Item()
    , p_impl( new SynapseImpl( this))
{
//    LOGWRITE_TEXT("Create Synapse: ");
//    LOGWRITE_VALUE( this);
}


Synapse::~Synapse()
{
//    LOGWRITE_TEXT("Delete Synapse: ");
//    LOGWRITE_VALUE( this);
}


void Synapse::show()
{
    LOGWRITE( "Synapse: " +
              std::to_string(m_input) + " " +
              std::to_string(m_output) + "\n");
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->show(); });
}


//void Synapse::forwardAction() {}
void Synapse::backpropAction() {}

void Synapse::removeItem( Item*) {}


void Synapse::setState( NET_STATE state)
{
    p_impl->setState( state);
}


void Synapse::input( double& input)
{
    p_impl->input( input);
}


void Synapse::output( double& output)
{
    p_impl->output( output);
}



//==========================================================
Neuron::Neuron()
    : Item()
    , p_impl( new SigmoidNeuronImpl( this))
//    , m_typeActivation( SIGMOID)
{
//    LOGWRITE_TEXT("Create Neuron\n");
}


Neuron::~Neuron()
{
//    LOGWRITE_TEXT("Delete Neuron\n");
}

void Neuron::show()
{
    LOGWRITE( std::to_string(m_location.first) + " " +
              std::to_string(m_location.second) + " " +
              std::to_string(m_input) + " " +
              std::to_string(m_output) + "\n");
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->show(); });
}


void Neuron::setProperty( void* pProperty)
{
    if( pProperty == nullptr) {
        CONSOL_OUT( "pProperty = nullptr");
        p_impl.reset( new SigmoidNeuronImpl( this));
        return;
    }
    NeuronConfig* pConfig = static_cast<NeuronConfig*>(pProperty);
//    NEURON_TYPE_ACTIVATION* pTypeActivation = static_cast<NEURON_TYPE_ACTIVATION*>(pProperty);
//    m_typeActivation = *pTypeActivation;

    // Выбор типа реализации
//    if( *pTypeActivation == SIGMOID) {
//        p_impl.reset( new SigmoidNeuronImpl( this));
//    }
//    else if( *pTypeActivation == RELU) {
//        p_impl.reset( new ReLuNeuronImpl( this));
//    }
//    else {
//        p_impl.reset( new NonTypeNeuronImpl( this));
//    }
    // Выбор типа реализации
    if( pConfig->activationType == SIGMOID) {
        p_impl.reset( new SigmoidNeuronImpl( this));
    }
    else if( pConfig->activationType == RELU) {
        p_impl.reset( new ReLuNeuronImpl( this));
    }
    else {
        p_impl.reset( new NonTypeNeuronImpl( this));
    }
    m_location = pConfig->location;
}


void Neuron::setState( NET_STATE state)
{
    p_impl->setState( state);
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->setState( state); });
}


void Neuron::forwardAction()
{
    p_impl->forwardAction();
}


void Neuron::backpropAction()
{
    p_impl->backpropAction();
}

//void Neuron::addChild( Item*) {}
//void Neuron::addParent( Item*) {}
void Neuron::removeItem( Item*) {}


void Neuron::input( double& input)
{
    p_impl->input( input);
}


void Neuron::output( double& output)
{
    p_impl->output( output);
}


//==========================================================
OutputNeuron::OutputNeuron()
    : Neuron()
    , p_impl( new SigmoidOutputNeuronImpl( this))
    , m_idealOutput()
{
//    LOGWRITE_TEXT("Create Neuron\n");
}


OutputNeuron::~OutputNeuron()
{
//    LOGWRITE_TEXT("Delete Neuron\n");
}


void OutputNeuron::backpropAction()
{
    p_impl->backpropAction();
}


void OutputNeuron::setState( NET_STATE state)
{
    p_impl->setState( state);
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->setState( state); });
}


void OutputNeuron::input( double& input)
{
    p_impl->input( input);
}


void OutputNeuron::output( double& output)
{
    p_impl->output( output);
}



//void OutputNeuron::show()
//{
//    LOGWRITE_TEXT( std::to_string(m_location.first) + " " +
//                   std::to_string(m_location.first) + " " +
//                   std::to_string(m_output));
//    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->show(); });
//}

void OutputNeuron::setProperty( void* pProperty)
{
    if( pProperty == nullptr) {
        CONSOL_OUT( "pProperty = nullptr");
        p_impl.reset( new SigmoidOutputNeuronImpl( this));
        return;
    }

    NeuronConfig* pConfig = static_cast<NeuronConfig*>(pProperty);
    // Выбор типа реализации
    if( pConfig->activationType == SIGMOID) {
        p_impl.reset( new SigmoidOutputNeuronImpl( this));
    }
    else if( pConfig->activationType == RELU) {
        p_impl.reset( new ReLuOutputNeuronImpl( this));
    }
    else {
        p_impl.reset( new NonTypeOutputNeuronImpl( this));
    }
    m_location = pConfig->location;
}




//==========================================================
BiasNeuron::BiasNeuron()
    : Item()
    , p_impl( new BiasNeuronImpl())
    , m_output(1.0)
{
//    LOGWRITE_TEXT("Create BiasNeuron\n");
}


BiasNeuron::~BiasNeuron()
{
//    LOGWRITE_TEXT("Delete BiasNeuron\n");
}


void BiasNeuron::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + " " + __func__ + "\n");

    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->input( m_output); });
}

void BiasNeuron::backpropAction() {}

//void BiasNeuron::addChild( Item*) {}
//void BiasNeuron::addParent( Item*) {}
void BiasNeuron::removeItem( Item*) {}



//==========================================================
InputNeuron::InputNeuron()
    : Item()
    , p_impl( new InputNeuronImpl())
{
//    LOGWRITE_TEXT("Create InputNeuron\n");
}


InputNeuron::~InputNeuron()
{
//    LOGWRITE_TEXT("Delete InputNeuron\n");
}


void InputNeuron::show()
{
    LOGWRITE( std::to_string(m_location.first) + " " +
              std::to_string(m_location.second) + " " +
              std::to_string(m_input) + "\n");
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->show(); });
}


void InputNeuron::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + " " + __func__ + "\n");
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->input( m_input); });
}


void InputNeuron::backpropAction() {}


void InputNeuron::removeItem( Item*) {}


void InputNeuron::input( double& input)
{
    m_input = input;
}


void InputNeuron::output( double& output)
{
    output = m_input;
}



