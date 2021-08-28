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
    // Создание входного узла сети
    p_node = Singleton::instance().createInputNode();

    // Создание нейронов
    createNeurons_( netConfig);

    // Создание синапсов
    createAndAddSynapses_();
}


void NetHolder::createNeurons_( const netConfiguration_t& netConfig)
{
    // Вернуть последний вставленный в композицию Item
    auto pCurrentItem = [] ( const itemPtr_t& node) { return node->getChildList().rbegin()->get(); };

    // Добавить последний нейрон композиции в последний существующий слой двумерного контейнера нейронов
    auto pushBackNeuron = [&] ( const itemPtr_t& node, neuronContainer_t& cont) { cont.rbegin()->emplace_back( pCurrentItem( node)); };

    // Итератор для перемещения по слоям
    auto itLayer = netConfig.begin();

    // Создание входных нейронов
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
    {
        p_node->addChild( Singleton::instance().createInputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
    // Нейрон смещения
    p_node->addChild( Singleton::instance().createBiasNeuron());
    pushBackNeuron(p_node, c_neurons);

    // Создание нейронов скрытых слоев
    for( ++itLayer; itLayer != std::prev(netConfig.end()); ++itLayer)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int i = 0, end = itLayer->numOfNeuron; i < end; ++i)
        {
            p_node->addChild( Singleton::instance().createNeuron());
            pushBackNeuron(p_node, c_neurons);
        }
        // Нейрон смещения
        p_node->addChild( Singleton::instance().createBiasNeuron());
        pushBackNeuron(p_node, c_neurons);
    }

    // Создание выходных нейронов
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
    {
        p_node->addChild( Singleton::instance().createOutputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
}


void NetHolder::createAndAddSynapses_()
{
    // Вернуть последний вставленный в композицию Item
    auto pCurrentItem = [] ( const itemPtr_t& node) { return *node->getChildList().rbegin(); };

    for( unsigned int i = 0, end_i = c_neurons.size() - 2; i < end_i; ++i) {
        for( unsigned int j = 0, end_j = c_neurons[i].size(); j < end_j; ++j) {
            for( unsigned int k = 0, end_k = c_neurons[i + 1].size() - 1; k < end_k; ++k)
            {
                // Создаем синапс
                p_node->addChild( Singleton::instance().createSynapse());

                // Присоединяем синапс к нейронам
                c_neurons[i][j]->addChild( pCurrentItem( p_node));
                c_neurons[i + 1][k]->addParent( pCurrentItem( p_node));
            }
        }
    }

    unsigned int lastLayer = c_neurons.size() - 1;

    for( unsigned int j = 0, end_j = c_neurons[lastLayer - 1].size(); j < end_j; ++j) {
        for( unsigned int k = 0, end_k = c_neurons[lastLayer].size(); k < end_k; ++k)
        {
            // Создаем синапс
            p_node->addChild( Singleton::instance().createSynapse());

            // Присоединяем синапс к нейронам
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
