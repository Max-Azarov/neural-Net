#include "netHolder.h"
#include "singleton.h"

//#include <iterator>
//#include <numeric>
#include <algorithm>
#include <functional>


using namespace Neural;


NetHolder::NetHolder()
    : INetHolder()
    , p_node ()
    , c_neurons()
{
}


NetHolder::~NetHolder()
{

}


void NetHolder::createNet( const netConfiguration_t& netConfig)
{
    // �������� �������� ���� ����
    p_node = Singleton::instance().createInputNode();

    // �������� ��������
    createNeurons_( netConfig);

    // �������� ��������
    createAndAddSynapses_();
}


void NetHolder::createNeurons_( const netConfiguration_t& netConfig)
{
    // ������� ��������� ����������� � ���������� Item
    auto pCurrentItem = [] ( const itemPtr_t& node) { return node->getChildList().rbegin()->get(); };

    // �������� ��������� ������ ���������� � ��������� ������������ ���� ���������� ���������� ��������
    auto pushBackNeuron = [&] ( const itemPtr_t& node, neuronContainer_t& cont) { cont.rbegin()->emplace_back( pCurrentItem( node)); };

    // �������� ��� ����������� �� �����
    auto itLayer = netConfig.begin();

    // �������� ������� ��������
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
    {
        p_node->addChild( Singleton::instance().createInputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
    // ������ ��������
    p_node->addChild( Singleton::instance().createBiasNeuron());
    pushBackNeuron(p_node, c_neurons);

    // �������� �������� ������� �����
    for( ++itLayer; itLayer != std::prev(netConfig.end()); ++itLayer)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
        {
            p_node->addChild( Singleton::instance().createNeuron());
            pushBackNeuron(p_node, c_neurons);
        }
        // ������ ��������
        p_node->addChild( Singleton::instance().createBiasNeuron());
        pushBackNeuron(p_node, c_neurons);
    }

    // �������� �������� ��������
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
    {
        p_node->addChild( Singleton::instance().createOutputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
}


void NetHolder::createAndAddSynapses_()
{
    // ������� ��������� ����������� � ���������� Item
    auto pCurrentItem = [] ( const itemPtr_t& node) { return *node->getChildList().rbegin(); };

    for( unsigned int i = 0, end_i = c_neurons.size() - 2; i < end_i; ++i) {
        for( unsigned int j = 0, end_j = c_neurons[i].size(); j < end_j; ++j) {
            for( unsigned int k = 0, end_k = c_neurons[i + 1].size() - 1; k < end_k; ++k)
            {
                // ������� ������
                p_node->addChild( Singleton::instance().createSynapse());

                // ������������ ������ � ��������
                c_neurons[i][j]->addChild( pCurrentItem( p_node));
                c_neurons[i + 1][k]->addParent( pCurrentItem( p_node));
            }
        }
    }

    unsigned int lastLayer = c_neurons.size() - 1;

    for( unsigned int j = 0, end_j = c_neurons[lastLayer - 1].size(); j < end_j; ++j) {
        for( unsigned int k = 0, end_k = c_neurons[lastLayer].size(); k < end_k; ++k)
        {
            // ������� ������
            p_node->addChild( Singleton::instance().createSynapse());

            // ������������ ������ � ��������
            c_neurons[lastLayer - 1][j]->addChild( pCurrentItem( p_node));
            c_neurons[lastLayer][k]->addParent( pCurrentItem( p_node));
        }
    }
}


void NetHolder::netState( NET_STATE /*netState*/)
{

}


void NetHolder::setInputs( const inputContainer_t& /*inputs*/)
{

}


void NetHolder::setOutputs( const outputContainer_t& /*outputs*/)
{

}


outputContainer_t NetHolder::getOutputs()
{
    return outputContainer_t();
}


//    std::unique_ptr<Synapse> synapse = Singleton::instance().createSynapse();
//    std::unique_ptr<Neuron> neuron = Singleton::instance().createNeuron();
//    std::unique_ptr<BiasNeuron> biasNeuron = Singleton::instance().createBiasNeuron();
//    std::unique_ptr<OutputNeuron> outputNeuron = Singleton::instance().createOutputNeuron();
//
//    LOGWRITE_TEXT(synapse->getType());
//    LOGWRITE_TEXT(neuron->getType());
//    LOGWRITE_TEXT(biasNeuron->getType());
//    LOGWRITE_TEXT(outputNeuron->getType());
//    LOGWRITE_TEXT(InputNode->getType());
