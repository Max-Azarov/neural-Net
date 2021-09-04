#ifndef TYPES_H
#define TYPES_H

#include <array>
#include <string>
#include <memory>
#include <list>
#include <vector>



namespace Neural {


enum ITEM_TYPE {
    BASIC_ITEM,
    SYNAPSE,
    NEURON,
    INPUT_NEURON,
    OUTPUT_NEURON,
    BIAS_NEURON,
    NODE,
    NUM_OF_TYPE,
};


enum ITEM_STATE {
    IN_TO_OUT,
    OUT_TO_IN,
    UPDATE,
};


enum NET_TYPE
{
    FULLY_CONNECTED,
};


enum NEURON_TYPE_ACTIVATION
{
    NON_TYPE,
    SIGMOID,
    RELU,
};


enum NET_STATE
{
    FORWARD,
    BACKPROP,
};




class Item;
struct LayerConfig;

using itemPtr_t = std::shared_ptr<Item>;
using itemPtrList_t = std::list<Item*>;
using itemSmartPtrList_t = std::list<itemPtr_t>;
using location_t = std::pair<unsigned int, unsigned int>;
using netConfiguration_t = std::vector<LayerConfig>;
using inputContainer_t = std::vector<double>;
using outputContainer_t = std::vector<double>;
using neuronContainer_t = std::vector<std::vector<Item*>>;



struct LayerConfig
{
    unsigned int numOfNeuron;
    NEURON_TYPE_ACTIVATION activationType;


    LayerConfig()
        : numOfNeuron()
        , activationType(SIGMOID)
    {}


    LayerConfig( unsigned int num, NEURON_TYPE_ACTIVATION act = SIGMOID)
        : numOfNeuron(num)
        , activationType(act)
    {}
};

struct NeuronConfig
{
    NEURON_TYPE_ACTIVATION activationType;
    location_t location;

    NeuronConfig( NEURON_TYPE_ACTIVATION act, location_t loc)
        : activationType( act)
        , location( loc)
    {}
};


struct NetConfiguration
{
    std::vector<LayerConfig> neuronActivationType; // Определяет количество слоев и тип активации каждого из слоев


    NetConfiguration( )
        : neuronActivationType()
    {}
};



class ItemTypeName
{
public:
    std::string operator() (ITEM_TYPE itemType) {
        return m_typeName[itemType];
    }

private:
    std::array<std::string, NUM_OF_TYPE> m_typeName;

public:
    ItemTypeName()
        : m_typeName { "BASIC_ITEM",
                       "SYNAPSE",
                       "NEURON",
                       "INPUT_NEURON",
                       "OUTPUT_NEURON",
                       "BIAS_NEURON",
                       "NODE" ,
                      }
    {}
};


} // namespace Neural

#endif // TYPES_H
