#ifndef ITEM_H
#define ITEM_H


#include <list>
#include <memory>

#include "logwrite.h"
#include "itemImpl.h"


enum ITEM_TYPE {
    SYNAPSE,
    NEURON,
    INPUT_NEURON,
    OUTPUT_NEURON,
    BIAS_NEURON,
};



class Item;
using ItemList = std::list<std::unique_ptr<Item>>;



class Item
{
public:
    virtual void forwardAction() = 0;
    virtual void backwardAction() = 0;

    virtual void addItem( Item*) = 0;
    virtual void removeItem( Item*) = 0;
    virtual const ItemList& getListItem() = 0;
    virtual ITEM_TYPE getType() = 0;

public:
    virtual ~Item() {}
};




class Synapse : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

    void addItem( Item*) override;
    void removeItem( Item*) override;
    const ItemList& getListItem() override { return c_itemList; }
    ITEM_TYPE getType() override { return SYNAPSE;}

public:
    Synapse();
    ~Synapse();

private:
    ItemList c_itemList;
};



class Neuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

    void addItem( Item*) override;
    void removeItem( Item*) override;
    ItemList& getListItem() override { return c_itemList; }
    virtual ITEM_TYPE getType() override { return NEURON;}

public:
    Neuron();
    ~Neuron();

private:
    ItemList c_itemList;
};



class BiasNeuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

    void addItem( Item*) override;
    void removeItem( Item*) override;
    const ItemList& getListItem() override { return c_itemList; }
    ITEM_TYPE getType() override { return BIAS_NEURON;}

public:
    BiasNeuron();
    ~BiasNeuron();

private:
    ItemList c_itemList;
};



class OutputNeuron : public Item
{
public:
    void forwardAction() override;
    void backwardAction() override;

    void addItem( Item*) override;
    void removeItem( Item*) override;
    const ItemList& getListItem() override { return c_itemList; }
    ITEM_TYPE getType() override { return OUTPUT_NEURON;}

public:
    OutputNeuron();
    ~OutputNeuron();

private:
    ItemList c_itemList;
};

#endif // ITEM_H
