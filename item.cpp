#include "item.h"

#include "algorithm"


#include <functional>
#include <numeric>


using namespace Neural;


//==========================================================
Item::Item()
    : c_itemListChild()
    , c_itemListParent()
{
}


Item::~Item()
{
}


void Item::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + ": ");
//    LOGWRITE_VALUE( this);

    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), []( const itemPtr_t& pItem){ pItem->forwardAction(); });
//    std::for_each(c_itemListParent.begin(), c_itemListParent.end(), []( const itemPtr_t& pItem){ pItem->forwardAction(); });
}


void Item::setState( NET_STATE state)
{
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->setState( state); });
}


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
Node::Node()
    : Item()
{
    LOGWRITE_TEXT("Create Node\n");
}


Node::~Node()
{
    LOGWRITE_TEXT("Delete Node\n");
}


//void Node::forwardAction() {}
void Node::backwardAction() {}


void Node::removeItem( Item*) {}





//=========================================================
Synapse::Synapse()
    : Item()
    , p_impl( new SynapseImpl( this))
{
    LOGWRITE_TEXT("Create Synapse: ");
    LOGWRITE_VALUE( this);
}


Synapse::~Synapse()
{
    LOGWRITE_TEXT("Delete Synapse: ");
    LOGWRITE_VALUE( this);
}


//void Synapse::forwardAction() {}
void Synapse::backwardAction() {}

void Synapse::removeItem( Item*) {}


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
    , p_impl( new NeuronImpl( this))
    , m_typeActivation( SIGMOID)
{
    LOGWRITE_TEXT("Create Neuron\n");
}


Neuron::~Neuron()
{
    LOGWRITE_TEXT("Delete Neuron\n");
}


void Neuron::setProperty( void* pProperty)
{
    if( pProperty == nullptr) {
        CONSOL_OUT( "pProperty = nullptr");
        return;
    }
    NEURON_TYPE_ACTIVATION* pTypeActivation = static_cast<NEURON_TYPE_ACTIVATION*>(pProperty);
    m_typeActivation = *pTypeActivation;

    // ����� ���� ����������
    if( m_typeActivation == SIGMOID) {
        p_impl.reset( new SigmoidNeuronImpl( this));
    }
    else if( m_typeActivation == RELU) {
        p_impl.reset( new ReLuNeuronImpl( this));
    }
    else {
        p_impl.reset( new NonTypeNeuronImpl( this));
    }
}


void Neuron::setState( NET_STATE state)
{
    if( state == FORWARD) {
//        m_state = IN_TO_OUT;
    }
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->setState( state); });
}


void Neuron::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + " " + __func__ + "\n");

    // ��������� ��������� ������ �� ���� ������� ��������
    double sum = 0;
    double tempDouble = 0;
    sum = std::accumulate( c_itemListParent.begin(), c_itemListParent.end(), 0.0, [&]( double x, const itemPtr_t& pItem)
    {
        pItem->output( tempDouble);
        return x + tempDouble;
    });

    // ������ ���������� �������� �� ���� �������
    input( sum);

    // �������� �������� ������ � �������
    std::for_each(c_itemListParent.begin(), c_itemListParent.end(), [&]( const itemPtr_t& pItem)
    {
        pItem->output( sum);
    });
}


void Neuron::backwardAction() {}

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
BiasNeuron::BiasNeuron()
    : Item()
    , p_impl( new BiasNeuronImpl())
    , m_output(1.0)
{
    LOGWRITE_TEXT("Create BiasNeuron\n");
}


BiasNeuron::~BiasNeuron()
{
    LOGWRITE_TEXT("Delete BiasNeuron\n");
}


void BiasNeuron::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + " " + __func__ + "\n");

    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->input( m_output); });
}

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


//void OutputNeuron::forwardAction() {}
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


void InputNeuron::forwardAction()
{
//    LOGWRITE(ItemTypeName()(getType()) + " " + __func__ + "\n");
    std::for_each(c_itemListChild.begin(), c_itemListChild.end(), [&]( const itemPtr_t& pItem){ pItem->input( m_input); });
}


void InputNeuron::backwardAction() {}


void InputNeuron::removeItem( Item*) {}


void InputNeuron::input( double& input)
{
    m_input = input;
}


void InputNeuron::output( double& output)
{
    output = m_input;
}



