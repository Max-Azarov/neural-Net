#ifndef ITEM_H
#define ITEM_H


#include <list>
#include <memory>

enum ITEM_TYPE {
    SYNAPSE,
    NEURON,
    INPUT_NEURON,
    OUTPUT_NEURON,
    BIAS_NEURON,
};


// Называем тип контейнера
class Item;
using ItemList = std::list<std::unique_ptr<Item>>;


// Интерфейс составной части композиции
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



// Реализация синапса
class Synapse : public Item
{
public:
    virtual void forwardAction() override {}
    virtual void backwardAction() override {}

    virtual void addItem( Item*) override {}
    virtual void removeItem( Item*) override {}
    virtual const ItemList& getListItem() override { return c_itemList; }
    virtual ITEM_TYPE getType() override { return SYNAPSE;}

public:
    Synapse() : c_itemList() {}
    virtual ~Synapse() {}

private:
    ItemList c_itemList;
};

#endif // ITEM_H
