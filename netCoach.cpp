#include <iterator>
#include <algorithm>
#include <functional>
#include <numeric>

#include "netCoach.h"
#include "logwrite.h"
#include "netHolder.h"


using namespace Neural;
using namespace std::placeholders;



void NetCoacherRefSet::training()
{
    LOGWRITE("Forward\n");
    p_netHolder->setNetState( Neural::FORWARD);
    for( const auto& itSet : c_trainingSet)
    {
        std::copy( std::begin( itSet), std::end( itSet), p_netHolder->inputs().begin());
        std::copy( p_netHolder->inputs().begin(), p_netHolder->inputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
        p_netHolder->run();
        std::copy( p_netHolder->outputs().begin(), p_netHolder->outputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
    }

    auto itSet = c_trainingSet.begin();
    auto itIdeal = c_idealOut.begin();
    outputContainer_t c_error( c_idealOut.size());
    double error = 0;
    unsigned numValuesForError = 0;
    bool calcError = false;

    for( int i = 0; i < 1000000; ++i)
    {
        error = 0;
        numValuesForError = 0;
        calcError = (i+1) % 1000 ? false : true;
        for( itSet = c_trainingSet.begin(), itIdeal = c_idealOut.begin(); itSet != c_trainingSet.end(); ++itSet, ++itIdeal)
        {
            std::copy( std::begin( *itSet), std::end( *itSet), p_netHolder->inputs().begin());
            p_netHolder->setNetState( Neural::FORWARD);
            p_netHolder->run();

            if( calcError == true)
            {
                std::transform( std::begin( *itIdeal), std::end( *itIdeal), std::begin( p_netHolder->outputs()), c_error.begin(),
                                std::bind(std::multiplies<double>(),
                                          std::bind( std::minus<double>(), _1, _2),
                                          std::bind( std::minus<double>(), _1, _2))
                                );

                error = std::accumulate( c_error.begin(), c_error.end(), error);
                numValuesForError += c_error.size();
            }


            std::copy( std::begin( *itIdeal), std::end( *itIdeal), p_netHolder->outputs().begin());
            p_netHolder->setNetState( Neural::BACKPROP);
            p_netHolder->run();
        }

        if( calcError == true)
        {
            error /= numValuesForError;
            LOGWRITE( i);
            LOGWRITE( ": ");
            LOGWRITE_VALUE( error);
            if( error < 0.01) {
                break;
            }
        }
    }

    LOGWRITE("Forward\n");
    p_netHolder->setNetState( Neural::FORWARD);
    for( const auto& itSet : c_trainingSet)
    {
        std::copy( std::begin( itSet), std::end( itSet), p_netHolder->inputs().begin());
        std::copy( p_netHolder->inputs().begin(), p_netHolder->inputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
        p_netHolder->run();
        std::copy( p_netHolder->outputs().begin(), p_netHolder->outputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
    }
}
