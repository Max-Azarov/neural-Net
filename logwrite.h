#pragma once



// =============================================================
#define LOG

#ifdef LOG
#include <iostream>
#include <string>
#include <iomanip>
#define LOGWRITE( text) std::cout << std::setprecision(3) << text << std::flush
#define LOGWRITE_TEXT( text) std::cout << std::string(__FILE__).substr( std::string(__FILE__).find_last_of("\\/") + 1) << ":" << __LINE__ << "\t" << std::setprecision(3) << text << std::flush
#define LOGWRITE_VALUE( value) std::cout << std::string(__FILE__).substr( std::string(__FILE__).find_last_of("\\/") + 1) << ":" << __LINE__ << "\t" << #value << ": " << std::setprecision(3) << value << std::endl

#else
#define LOGWRITE( text) //
#define LOGWRITE_TEXT( text) //
#define LOGWRITE_VALUE( value) //
#endif


// =============================================================
#define CONSOL

#ifdef CONSOL
#include <iostream>
#define CONSOL_OUT( text) std::cout << std::string(__FILE__).substr( std::string(__FILE__).find_last_of("\\/") + 1) << ":" << __LINE__ << "\t" << #text << ": " << std::setprecision(3) << text << std::endl

#else
#define CONSOL( text) //

#endif
