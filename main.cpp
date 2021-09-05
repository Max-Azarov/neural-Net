#include "logwrite.h"
#include "netHolder.h"
#include "netCoach.h"


#include <memory>
#include <algorithm>
#include <iterator>

#include "types.h"


int main()
{
    // Создаем сеть
    Neural::NetHolder netHolder;
    Neural::netConfiguration_t netConfig {
        { 2, Neural::NON_TYPE },
//        { 4, Neural::SIGMOID },
//        { 4, Neural::RELU },
//        { 4, Neural::RELU },
        { 6, Neural::SIGMOID },
//        { 4, Neural::RELU },
//        { 3, Neural::RELU },
//        { 4, Neural::SIGMOID },
//        { 2, Neural::SIGMOID },
        { 1, Neural::SIGMOID },
    };
    netHolder.createNet( netConfig);

    // Заполняем тренировочные сеты
    std::vector< std::vector<double>> trainingSet {
                                                       {0.0, 0.0} ,
                                                       {0.0, 1.0} ,
                                                       {1.0, 0.0} ,
                                                       {1.0, 1.0} ,
                                                     };

    std::vector< std::vector<double>> idealOut {
                                                 {1.0},
                                                 {0.0},
                                                 {0.0},
                                                 {1.0},
                                               };

    // Создаем тренера и учим
    Neural::NetCoacherRefSet netCoacher( &netHolder, trainingSet, idealOut);
    netCoacher.training();

    return 0;
}
