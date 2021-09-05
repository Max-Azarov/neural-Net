#ifndef SINGLETON_H
#define SINGLETON_H

#include <memory>
#include <chrono>
#include <random>

#include "item.h"
#include "logwrite.h"
#include "types.h"


namespace Neural {



class Singleton {
public:
    static Singleton& instance()
    {
        static std::unique_ptr<Singleton> s;
        if( !s ) {
            s.reset( new Singleton());
        }
        return *s.get();
    }

public:
    itemPtr_t createSynapse() { return itemPtr_t( new Synapse()); }
    itemPtr_t createNeuron() { return itemPtr_t( new Neuron()); }
    itemPtr_t createBiasNeuron() { return itemPtr_t( new BiasNeuron()); }
    itemPtr_t createOutputNeuron() { return itemPtr_t( new OutputNeuron()); }
    itemPtr_t createNode() { return itemPtr_t( new Node()); }
    itemPtr_t createInputNeuron() { return itemPtr_t( new InputNeuron()); }

private:
    std::default_random_engine& getGenerator()
    {
        static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
        static std::default_random_engine generator( seed);
        return std::ref( generator);
    }

public:
    double getRandom(double lowerBound, double upperBound)
    {
        std::uniform_real_distribution<double> distribution( lowerBound, upperBound);
        return distribution( getGenerator());
    }


    double getRandValue( double value)
    {
        std::uniform_real_distribution<double> distribution( value * 0.5, value * 2.0);
        return distribution( getGenerator());
    }


    // ��� ������������� ����� ��������
    double getE() const { return 0.007; }
    double getA() const { return 0.003; }


public:
    Singleton( const Singleton&) = delete;
    void operator= ( const Singleton&) = delete;
    Singleton( Singleton&&) = delete;
    void operator= ( Singleton&&) = delete;

    ~Singleton() { /*LOGWRITE_TEXT("delete Singleton\n");*/ }
private:
    Singleton() { /*LOGWRITE_TEXT("create Singleton\n");*/ }
};


} // namespace Neural

#endif // SINGLETON_H
