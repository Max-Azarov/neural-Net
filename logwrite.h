#pragma once



// =============================================================
#define LOG

#ifdef LOG
#include <iostream>
#define LOGWRITE( text) std::cout << __FILE__ << ":" << __LINE__ << "  " << #text << ": " << text << std::endl

#else
#define LOGWRITE( text) //
#endif


// =============================================================
#define CONSOL

#ifdef CONSOL
#include <iostream>
#define CONSOL_OUT( text) std::cout << __FILE__ << ":" << __LINE__ << "  " << #text << ": " << text << std::endl

#else
#define CONSOL( text) //

#endif
