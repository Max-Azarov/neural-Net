#ifndef ITEM_H
#define ITEM_H


#include <list>
#include <memory>
#include <utility>

#include "logwrite.h"
#include "itemImpl.h"


namespace Neural {




enum ITEM_TYPE {
    BASIC_ITEM,
    SYNAPSE,
    NEURON,
    INPUT_NEURON,
    OUTPUT_NEURON,
    BIAS_NEURON,
    INPUT_NODE,
};


//==========================================================
class Item;

using itemPtr_t = std::shared_ptr<Item>;
using itemPtrList_t = std::list<Item*>;
using itemSmartPtrList_t = std::list<itemPtr_t>;
using location_t = std::pair<unsigned int, unsigned int>;



class Item
{
public:
    virtual void forwardAction();
    virtual void backwardAction();

    virtual void addChild( itemPtr_t);
    virtual void addParent( itemPtr_t);
    virtual void removeItem( Item*);
    virtual const itemSmartPtrList_t& getChildList() { return c_itemListChild; }
    virtual const itemSmartPtrList_t& getParentList() { return c_itemListParent; }
    virtual ITEM_TYPE getType();
    virtual location_t getLocation() { return m_location; }
    virtual void setLocation( location_t location) { m_location = location; }

public:
    Item();
    virtual ~Item();

protected:
    itemSmartPtrList_t c_itemListChild;
    itemSmartPtrList_t c_itemListParent;
    location_t m_location;
};



//==========================================================
class InputNode : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//    void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return INPUT_NODE;}

public:
    InputNode();
    ~InputNode();

private:

};



//==========================================================
class Synapse : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return SYNAPSE;}

public:
    Synapse();
    ~Synapse();

private:
    std::unique_ptr<SynapseImpl> p_impl;
};



//==========================================================
class Neuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    virtual ITEM_TYPE getType() override { return NEURON;}

public:
    Neuron();
    ~Neuron();

private:
    std::unique_ptr<NeuronImpl> p_impl;
};



//==========================================================
class BiasNeuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return BIAS_NEURON;}

public:
    BiasNeuron();
    ~BiasNeuron();

private:
    std::unique_ptr<BiasNeuronImpl> p_impl;
};



//==========================================================
class OutputNeuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return OUTPUT_NEURON;}

public:
    OutputNeuron();
    ~OutputNeuron();

private:
    std::unique_ptr<OutputNeuronImpl> p_impl;
};



//==========================================================
class InputNeuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return INPUT_NEURON;}

public:
    InputNeuron();
    ~InputNeuron();

private:
    std::unique_ptr<InputNeuronImpl> p_impl;
};


} // namespace Neural

#endif // ITEM_H
