#include "logwrite.h"
#include "netHolder.h"


#include <memory>
#include <algorithm>
#include <iterator>

#include "types.h"


int main()
{
    Neural::NetHolder netHolder;


    Neural::netConfiguration_t netConfig {
        { 2, Neural::NON_TYPE },
        { 10, Neural::SIGMOID },
        { 5, Neural::SIGMOID },
//        { 5, Neural::SIGMOID },
        { 1, Neural::SIGMOID },
    };

    std::vector< std::vector<double>> trainingSample { {0.0, 0.0} ,
                                                       {0.0, 1.0} ,
                                                       {1.0, 0.0} ,
                                                       {1.0, 1.0} ,
                                                     };
    std::vector< std::vector<double>> idealOut { {1.0},
                                                 {0.0},
                                                 {0.0},
                                                 {1.0}
                                               };


//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::NON_TYPE));
//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(3, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(5, Neural::SIGMOID));

    netHolder.createNet( netConfig);

//    netHolder.inputs().assign( { 1.0, 1.0});
//    LOGWRITE("Forward\n");
//    netHolder.run();
//    std::copy( netHolder.outputs().begin(), netHolder.outputs().end(), std::ostream_iterator<double>(std::cout, "\n"));

    LOGWRITE("Forward\n");
    for( unsigned j = 0; j < idealOut.size(); ++j)
    {

        netHolder.setNetState( Neural::FORWARD);
        std::copy( std::begin( trainingSample[j]), std::end( trainingSample[j]), netHolder.inputs().begin());
        std::copy( netHolder.inputs().begin(), netHolder.inputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
        netHolder.run();
        std::copy( netHolder.outputs().begin(), netHolder.outputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
    }

    for( int i = 0; i < 200000; ++i) {
        for( unsigned j = 0; j < idealOut.size(); ++j)
        {
//            LOGWRITE("Forward\n");
            netHolder.setNetState( Neural::FORWARD);
            std::copy( std::begin( trainingSample[j]), std::end( trainingSample[j]), netHolder.inputs().begin());
            netHolder.run();
    //        LOGWRITE("Backprop\n");
            std::copy( std::begin( idealOut[j]), std::end( idealOut[j]), netHolder.outputs().begin());
            netHolder.setNetState( Neural::BACKPROP);
            netHolder.run();
    //        LOGWRITE("Forward\n");

        }
    }

    LOGWRITE("Forward\n");
    for( unsigned j = 0; j < idealOut.size(); ++j)
    {

        netHolder.setNetState( Neural::FORWARD);
        std::copy( std::begin( trainingSample[j]), std::end( trainingSample[j]), netHolder.inputs().begin());
        std::copy( netHolder.inputs().begin(), netHolder.inputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
        netHolder.run();
        std::copy( netHolder.outputs().begin(), netHolder.outputs().end(), std::ostream_iterator<double>(std::cout, "\n"));
    }

    return 0;
}
