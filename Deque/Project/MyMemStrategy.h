#ifndef MY_MEM_STRATEGY_H_INCLUDED
#define MY_MEM_STRATEGY_H_INCLUDED

#pragma once

#include <cstdlib>

class MyMemStrategy {

  /**
  * @defgroup Mem_group Memory Methods
  * @{
  */

public:

  /**
  * @brief Allocate memory block of specified size.
  * @param sizeInBytes - needed size of memory block in bytes
  */
  void* memMalloc(int sizeInBytes) { return malloc(sizeInBytes); }

  /**
  * @brief Free memory that given pointer leads to.
  * @param ptr - pointer to memory to be freed
  */
  void memFree(void* ptr) { free(ptr); }

  /**@}*/
};

#endif // MY_MEM_STRATEGY_H_INCLUDED
