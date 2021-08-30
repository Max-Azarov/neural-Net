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
    , p_out_node ( Singleton::instance().createNode())
    , c_neurons()
    , c_outputValue()
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
    auto pCurrentItem = [&] () { return p_input_node->getChildList().rbegin()->get(); };

    // Добавить свойства последнему добавленному нейрону
    auto addProperty = [&] ( NEURON_TYPE_ACTIVATION activationType) { p_input_node->getChildList().rbegin()->get()->setProperty( &activationType); };

    // Добавить последний нейрон композиции в последний существующий слой двумерного контейнера нейронов
    auto pushBackNeuron = [&] () { c_neurons.rbegin()->emplace_back( pCurrentItem()); };

    // Итератор для перемещения по слоям
    auto itLayer = netConfig.begin();

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
    for( ++itLayer; itLayer != std::prev(netConfig.end()); ++itLayer)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
        {
            p_input_node->addChild( Singleton::instance().createNeuron());
            addProperty( itLayer->activationType);
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
        p_input_node->addChild( Singleton::instance().createNeuron());
        addProperty( itLayer->activationType);
        pushBackNeuron();

        // Добавляем выходной нейрон к узлу на выходе
        pCurrentItem()->addChild( p_out_node);
        p_out_node->addParent( *p_input_node->getChildList().rbegin());
    }

    p_input_node->addChild( p_out_node);
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


void NetHolder::netState( NET_STATE netState)
{
    p_input_node->setState( netState);
}


void NetHolder::setInputs( const inputContainer_t& inputs)
{
    // Подаем значения на входы сети
    auto itLayer = c_neurons.begin();
    auto itInputs = inputs.begin();
    std::for_each(itLayer->begin(), itLayer->end(), [&](Item* item)
    {
        double temp = *itInputs++;
        item->input( temp);
    });

    // Запускаем прямой проход
    p_input_node->forwardAction();
}


void NetHolder::setOutputs( const outputContainer_t& /*outputs*/)
{

}


const outputContainer_t& NetHolder::getOutputs()
{
    unsigned numOfOutputs = c_neurons.rbegin()->size();
    if( c_outputValue.size() != numOfOutputs)
    {
        c_outputValue.resize( numOfOutputs);
    }

    std::transform( c_neurons.rbegin()->begin(), c_neurons.rbegin()->end(), c_outputValue.begin(), []( Item* item)
    {
        double temp = 0.0;
        item->output( temp);
        return temp;
    });
    return c_outputValue;
}
