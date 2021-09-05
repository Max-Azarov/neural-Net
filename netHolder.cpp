#include "netHolder.h"
#include "singleton.h"

//#include <iterator>
//#include <numeric>
#include <algorithm>
#include <functional>


using namespace Neural;


NetHolder::NetHolder()
    : INetHolder()
    , p_input_node ( Singleton::instance().createNode())
    , c_neurons()
    , c_inputValue()
    , c_outputValue()
    , p_netHolderState( new NetHolderForwardState( this))
{
}


NetHolder::~NetHolder()
{

}


void NetHolder::createNet( const netConfiguration_t& netConfig)
{
    // �������� ��������
    createNeurons_( netConfig);

    // �������� ��������
    createAndAddSynapses_();
}


void NetHolder::createNeurons_( const netConfiguration_t& netConfig)
{
    // ������� ��������� ����������� � ���������� Item
    const auto pCurrentItem = [&] () { return p_input_node->getChildList().rbegin()->get(); };

    // �������� �������� ���������� ������������ �������
    const auto addProperty = [&] ( NeuronConfig activationType)
    {
        p_input_node->getChildList().rbegin()->get()->setProperty( &activationType);
    };

    // �������� ��������� ������ ���������� � ��������� ������������ ���� ���������� ���������� ��������
    const auto pushBackNeuron = [&] () { c_neurons.rbegin()->emplace_back( pCurrentItem()); };

    // �������� ��� ����������� �� �����
    auto itLayer = netConfig.begin();
    unsigned layer = 0;

    // �������� ������� ��������
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
    {
        p_input_node->addChild( Singleton::instance().createInputNeuron());
        pushBackNeuron();
    }
    // ������ ��������
    p_input_node->addChild( Singleton::instance().createBiasNeuron());
    pushBackNeuron();

    // �������� �������� ������� �����
    for( ++itLayer, ++layer; itLayer != std::prev(netConfig.end()); ++itLayer, ++layer)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
        {
            p_input_node->addChild( Singleton::instance().createNeuron());
            addProperty( NeuronConfig( itLayer->activationType, location_t(layer,i)));
            pushBackNeuron();
        }
        // ������ ��������
        p_input_node->addChild( Singleton::instance().createBiasNeuron());
        pushBackNeuron();
    }

    // �������� �������� ��������
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
    {
        p_input_node->addChild( Singleton::instance().createOutputNeuron());
        addProperty( NeuronConfig( itLayer->activationType, location_t(layer,i)));
        pushBackNeuron();
    }

    // ������� �������� ��� ������� � �������� �������� ��
    c_inputValue.resize( netConfig.begin()->numOfNeuron);
    c_outputValue.resize( netConfig.rbegin()->numOfNeuron);
}


void NetHolder::createAndAddSynapses_()
{
    itemPtr_t synapse;

    // �������� � ������������� �������� �� �������������� ����
    for( unsigned int i = 0, end_i = c_neurons.size() - 2; i < end_i; ++i) {
        for( unsigned int j = 0, end_j = c_neurons[i].size(); j < end_j; ++j) {
            for( unsigned int k = 0, end_k = c_neurons[i + 1].size() - 1; k < end_k; ++k)
            {
                // ������� ������
                synapse = Singleton::instance().createSynapse();

                // ������������ ������ � ��������
                c_neurons[i][j]->addChild( synapse);
                c_neurons[i + 1][k]->addParent( synapse);
            }
        }
    }

    // �������� � ������������� �������� ���������� ����
    unsigned int lastLayer = c_neurons.size() - 1;

    for( unsigned int j = 0, end_j = c_neurons[lastLayer - 1].size(); j < end_j; ++j) {
        for( unsigned int k = 0, end_k = c_neurons[lastLayer].size(); k < end_k; ++k)
        {
            // ������� ������
            synapse = Singleton::instance().createSynapse();

            // ������������ ������ � ��������
            c_neurons[lastLayer - 1][j]->addChild( synapse);
            c_neurons[lastLayer][k]->addParent( synapse);
        }
    }
}


void NetHolder::setNetState( NET_STATE netState)
{
    if( netState == FORWARD)
    {
        p_netHolderState.reset( new NetHolderForwardState( this));
    }
    else if( netState == BACKPROP)
    {
        p_netHolderState.reset( new NetHolderBackpropState( this));
    }

    p_input_node->setState( netState);
}


inputContainer_t& NetHolder::inputs()
{
    return c_inputValue;
}


outputContainer_t& NetHolder::outputs()
{
    return c_outputValue;
}


void NetHolder::run()
{
    p_netHolderState->run();
}
