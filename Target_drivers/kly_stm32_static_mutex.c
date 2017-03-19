/**
 * @file kly_stm32_static_mutex.c
 *
 * @author kelly.hathaway
 * @date Initial: Mar 18, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */


#include "kly_static_mutex.h"
#include "stm32f1xx.h"


/**
 * Lock a static mutex variable.
 * @param mutex Mutex to lock.
 * @return true on success, false if already locked.
 */
bool kly_static_mutex_lock(kly_static_mutex_t *mutex)
{
    kly_static_mutex_t current_value;
    uint32_t exclusive;

    do
    {
        current_value = __LDREXH(mutex);
        exclusive = __STREXH(MUTEX_LOCKED, mutex);
    } while(exclusive != 0);

    return (current_value == MUTEX_UNLOCKED);
}


/**
 * Unlock a static mutex variable.
 * @param mutex Mutex to unlock.
 */
void kly_static_mutex_unlock(kly_static_mutex_t *mutex)
{
    *mutex = MUTEX_UNLOCKED;
}
