#ifndef GENERAL_H
#define GENERAL_H
#include <iostream>

//#define PCA9685_DUMMY
#define DEBUG
#define MAX_VALUE 100

#ifdef DEBUG
#define DEBUG_MSG(str) std::cout << myGetTickCount() << "; " << str << std::endl
#else
#define DEBUG_MSG(str)
#endif

unsigned long int myGetTickCount(void);
#define UNUSED(x) (void)(x)

#ifdef PCA9685_DUMMY
void delay (int duration);
#endif

#endif //GENERAL_H
