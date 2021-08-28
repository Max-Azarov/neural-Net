#include "logwrite.h"
#include "netHolder.h"
#include "netConfiguration.h"


#include <memory>

int main()
{
    Neural::NetHolder netHolder;


    Neural::netConfiguration_t netConfig;

    netConfig.emplace_back( Neural::LayerConfig(2, Neural::NON_TYPE));
    netConfig.emplace_back( Neural::LayerConfig(2, Neural::SIGMOID));
    netConfig.emplace_back( Neural::LayerConfig(1, Neural::SIGMOID));

    netHolder.createNet( netConfig);

    return 0;
}
