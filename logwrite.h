#pragma once

#define LOG

#ifdef LOG
#include <iostream>
#define LOGWRITE( text) std::cout << __FILE__ << ":" << __LINE__ << "  " << #text << ": " << text << std::endl

#else
#define LOGWRITE( text) //

#endif // LOGWRITE_H
