#include <boost/thread.hpp>

#include "general.h"
#include "unistd.h"

unsigned long int starttime = 0;

unsigned long int myGetTickCount(void)
{
    struct timeval tv;
 
    gettimeofday(&tv, 0);
    return uint64_t(( tv.tv_sec ) * 1000 + tv.tv_usec / 1000 - starttime);
}

#ifdef PCA9685_DUMMY
void delay (int duration)
{
    //usleep(duration*1000);
    boost::this_thread::sleep(boost::posix_time::millisec(duration));
}
#endif