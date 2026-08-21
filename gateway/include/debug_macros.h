#ifndef DEBUG_MACROS_H
#define DEBUG_MACROS_H

#include <iostream>

#define DEBUG_MODE // Comment this to disable debug mode

#ifdef DEBUG_MODE
  #define DEBUG_PRINT(x)   (std::cout << (x)).flush()
  #define DEBUG_PRINTLN(x) std::cout << (x) << std::endl
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTLN(x)
#endif

#endif