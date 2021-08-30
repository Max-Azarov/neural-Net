#ifndef ITEM_H
#define ITEM_H


#include <list>
#include <memory>
#include <utility>

#include "logwrite.h"
#include "itemImpl.h"
#include "netConfiguration.h"
#include "types.h"


namespace Neural {



//==========================================================




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
    virtual void* getProperty() const { return nullptr;}
    virtual void setProperty( void*) {}
    virtual void setState( NET_STATE);
    virtual void input( double&) {}
    virtual void output( double&) {}

public:
    Item();
    virtual ~Item();

protected:
    itemSmartPtrList_t c_itemListChild;
    itemSmartPtrList_t c_itemListParent;
    NET_STATE m_state;
};



//==========================================================
class Node : public Item
{
public:
//    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//    void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return NODE;}

public:
    Node();
    ~Node();

private:

};



//==========================================================
class Synapse : public Item
{
public:
//    void forwardAction() override;
    void backwardAction() override;

//    void addChild( Item*) override;
//	void addParent( Item*) override;
    void removeItem( Item*) override;
    ITEM_TYPE getType() override { return SYNAPSE; }
    void input( double&) override;
    void output( double&) override;

public:
    Synapse();
    ~Synapse();

private:
    std::unique_ptr<SynapseImpl> p_impl;
    double m_input;
    double m_output;

    friend class SynapseImpl;
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
    void setProperty( void*) override;
    void setState( NET_STATE) override;
    void input( double&) override;
    void output( double&) override;

public:
    Neuron();
    ~Neuron();

private:
    std::unique_ptr<NeuronImpl> p_impl;
    NEURON_TYPE_ACTIVATION m_typeActivation;
    double m_input;
    double m_output;

    friend class NeuronImpl;
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
    double m_output;
};



//==========================================================
class OutputNeuron : public Item
{
public:
//    void forwardAction() override;
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
    double m_input;
    double m_output;
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
    void input( double&) override;
    void output( double&) override;

public:
    InputNeuron();
    ~InputNeuron();

private:
    std::unique_ptr<InputNeuronImpl> p_impl;
    double m_input;
};


} // namespace Neural


#endif // ITEM_H
