#include "logwrite.h"
#include "netHolder.h"
#include "netConfiguration.h"


#include <memory>
#include <algorithm>

#include "types.h"


int main()
{
    Neural::NetHolder netHolder;


    Neural::netConfiguration_t netConfig {
        { 2, Neural::NON_TYPE },
        { 2, Neural::SIGMOID },
        { 1, Neural::SIGMOID },
    };

//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::NON_TYPE));
//    netConfig.emplace_back( Neural::LayerConfig(2, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(3, Neural::SIGMOID));
//    netConfig.emplace_back( Neural::LayerConfig(5, Neural::SIGMOID));

    netHolder.createNet( netConfig);

    Neural::inputContainer_t inputs { 1.0, 1.0};

    netHolder.setInputs( inputs);

    Neural::outputContainer_t outputs = netHolder.getOutputs();
    std::for_each( outputs.begin(), outputs.end(), []( double out) {
        CONSOL_OUT( out);
    });



    return 0;
}
