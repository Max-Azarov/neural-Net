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
    // Создание нейронов
    createNeurons_( netConfig);

    // Создание синапсов
    createAndAddSynapses_();
}


void NetHolder::createNeurons_( const netConfiguration_t& netConfig)
{
    // Вернуть последний вставленный в композицию Item
    const auto pCurrentItem = [&] () { return p_input_node->getChildList().rbegin()->get(); };

    // Добавить свойства последнему добавленному нейрону
    const auto addProperty = [&] ( NeuronConfig activationType)
    {
        p_input_node->getChildList().rbegin()->get()->setProperty( &activationType);
    };

    // Добавить последний нейрон композиции в последний существующий слой двумерного контейнера нейронов
    const auto pushBackNeuron = [&] () { c_neurons.rbegin()->emplace_back( pCurrentItem()); };

    // Итератор для перемещения по слоям
    auto itLayer = netConfig.begin();
    unsigned layer = 0;

    // Создание входных нейронов
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
    {
        p_input_node->addChild( Singleton::instance().createInputNeuron());
        pushBackNeuron();
    }
    // Нейрон смещения
    p_input_node->addChild( Singleton::instance().createBiasNeuron());
    pushBackNeuron();

    // Создание нейронов скрытых слоев
    for( ++itLayer, ++layer; itLayer != std::prev(netConfig.end()); ++itLayer, ++layer)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
        {
            p_input_node->addChild( Singleton::instance().createNeuron());
            addProperty( NeuronConfig( itLayer->activationType, location_t(layer,i)));
            pushBackNeuron();
        }
        // Нейрон смещения
        p_input_node->addChild( Singleton::instance().createBiasNeuron());
        pushBackNeuron();
    }

    // Создание выходных нейронов
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
    {
        p_input_node->addChild( Singleton::instance().createOutputNeuron());
        addProperty( NeuronConfig( itLayer->activationType, location_t(layer,i)));
        pushBackNeuron();
    }

    // Размеры массивов для входных и выходных значений НС
    c_inputValue.resize( netConfig.begin()->numOfNeuron);
    c_outputValue.resize( netConfig.rbegin()->numOfNeuron);
}


void NetHolder::createAndAddSynapses_()
{
    itemPtr_t synapse;

    // Создание и присоединение синапсов до предпоследнего слоя
    for( unsigned int i = 0, end_i = c_neurons.size() - 2; i < end_i; ++i) {
        for( unsigned int j = 0, end_j = c_neurons[i].size(); j < end_j; ++j) {
            for( unsigned int k = 0, end_k = c_neurons[i + 1].size() - 1; k < end_k; ++k)
            {
                // Создаем синапс
                synapse = Singleton::instance().createSynapse();

                // Присоединяем синапс к нейронам
                c_neurons[i][j]->addChild( synapse);
                c_neurons[i + 1][k]->addParent( synapse);
            }
        }
    }

    // Создание и присоединение синапсов последнего слоя
    unsigned int lastLayer = c_neurons.size() - 1;

    for( unsigned int j = 0, end_j = c_neurons[lastLayer - 1].size(); j < end_j; ++j) {
        for( unsigned int k = 0, end_k = c_neurons[lastLayer].size(); k < end_k; ++k)
        {
            // Создаем синапс
            synapse = Singleton::instance().createSynapse();

            // Присоединяем синапс к нейронам
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
