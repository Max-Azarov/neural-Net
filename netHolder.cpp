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
//    Item* pCurrentItem;

    // Создание входного узла сети
    p_node = Singleton::instance().createInputNode();
//    c_allItem.emplace_back( Singleton::instance().createInputNode());
//    p_node = c_allItem.rbegin()->get();
//    p_node->setLocation( {0, 0});

    // Создание нейронов
    createNeurons_( netConfig);

//    // Создание синапсов
//    createAndAddSynapses_( netConfig);

//    // Создание входных нейронов  и присоединение их к p_node
//    for( unsigned int i = 0; i < netConfig.numOfInputs; ++i) {
//        c_allItem.emplace_back( Singleton::instance().createInputNeuron());
//        pCurrentItem = c_allItem.rbegin()->get();
//        pCurrentItem->setLocation( {1,i});
//        p_node->addChild( pCurrentItem);
//        (*p_node->getChildList().rbegin())->addParent(p_node);
//    }

//    // Итератор перемещающийся по будующим слоям
//    auto itLayer = netConfig.neuronActivationType.begin();

//    // Создание нейронов первого из скрытых слоев
//    for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
//    {
//        c_allItem.emplace_back( Singleton::instance().createNeuron());
//        pCurrentItem = c_allItem.rbegin()->get();
//        pCurrentItem->setLocation( {2,i});
//    }

//    // Создание синапсов между нейронами
//    const itemPtrList_t& inputNeuronList = p_node->getChildList();
//    auto it = inputNeuronList.begin();

//    for( ; it != inputNeuronList.end(); ++it)
//    {
//        for( unsigned int i = 0; i < itLayer->numOfNeuron; ++i)
//        {
//            // Создаем синапс
//            c_allItem.emplace_back( Singleton::instance().createSynapse());
//            pCurrentItem = c_allItem.rbegin()->get();
//            (*it)->addChild( pCurrentItem);
//            pCurrentItem->addParent( *it);

//            // Ищем нейрон, к которому нужно присоединить синапс
//            auto itNeuron = std::find_if( c_allItem.begin(), c_allItem.end(), [&](const itemPtr_t& pItem)
//            {
//                return pItem->getLocation().second == i
//                       && pItem->getLocation().first == 2
//                       ;
//            });

//            if( itNeuron != c_allItem.end() )
//            {
//                itNeuron->get()->addParent( pCurrentItem);
//            }
//        }
//    }
}


void NetHolder::createNeurons_( const netConfiguration_t& netConfig)
{
    // Вернуть последний вставленный в композицию Item
    auto pCurrentItem = [] ( const itemPtr_t& node) { return node->getChildList().rbegin()->get(); };

    // Добавить последний нейрон композиции в последний существующий слой двумерного контейнера нейронов
    auto pushBackNeuron = [&] ( const itemPtr_t& node, neuronContainer_t& cont) { cont.rbegin()->emplace_back( pCurrentItem( node)); };

    // Создание входных нейронов
    c_neurons.emplace_back( std::vector<Item*>());
    for( unsigned int i = 0, end = netConfig.begin()->numOfNeuron; i < end; ++i)
    {
        p_node->addChild( Singleton::instance().createInputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
    // Нейрон смещения
    p_node->addChild( Singleton::instance().createBiasNeuron());
    pushBackNeuron(p_node, c_neurons);

    // Создание нейронов скрытых слоев
    for( unsigned int i = 1, end_i = netConfig.size() - 1; i < end_i; ++i)
    {
        c_neurons.emplace_back( std::vector<Item*>());
        for( unsigned int j = 0, end_j = netConfig[i].numOfNeuron; j < end_j; ++j)
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
    for( unsigned int i = 0; i < netConfig.rbegin()->numOfNeuron; ++i)
    {
        p_node->addChild( Singleton::instance().createOutputNeuron());
        pushBackNeuron(p_node, c_neurons);
    }
}


void NetHolder::createAndAddSynapses_( const netConfiguration_t& netConfig)
{
//    Item* pCurrentItem;

//    // Ищем нужный нейрон
//    auto itNeuron = std::find_if( c_allItem.begin(), c_allItem.end(), [&](const itemPtr_t& pItem)
//    {
//        return pItem->getLocation().second == i
//               && pItem->getLocation().first == 2
//               ;
//    });

//    p_node

//    c_allItem.emplace_back( Singleton::instance().createSynapse());

//    // Создание синапсов
//    for( unsigned int i = 0; i < netConfig.size(); ++i)
//    {
//        for( unsigned int j = 0; j < netConfig[i].numOfNeuron; ++j)
//        {
//            for( unsigned int k = 0; k < netConfig[i].numOfNeuron; ++k)
//            {

//            }
//        }
//    }
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
//    LOGWRITE(synapse->getType());
//    LOGWRITE(neuron->getType());
//    LOGWRITE(biasNeuron->getType());
//    LOGWRITE(outputNeuron->getType());
//    LOGWRITE(InputNode->getType());
