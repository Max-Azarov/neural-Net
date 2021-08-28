#include "logwrite.h"
#include "netHolder.h"
#include "netConfiguration.h"


#include <memory>

int main()
{
    Neural::NetHolder netHolder;


    Neural::netConfiguration_t netConfig {
        { 2, Neural::NON_TYPE },
        { 2, Neural::SIGMOID },
        { 3, Neural::SIGMOID },
        { 5, Neural::SIGMOID },
    };

//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::NON_TYPE));
//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(3, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(5, Neural::SIGMOID));

    netHolder.createNet( netConfig);

    return 0;
}
