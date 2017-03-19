/**
 * @file kly_static_mutex.h
 *
 * @author kelly.hathaway
 * @date Initial: Mar 18, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */

#ifndef KLY_DRIVERS_INCLUDE_KLY_STATIC_MUTEX_H_
#define KLY_DRIVERS_INCLUDE_KLY_STATIC_MUTEX_H_

#include <stdbool.h>
#include <stdint.h>



#define MUTEX_LOCKED    0x8811
#define MUTEX_UNLOCKED  0x0000


typedef volatile uint16_t kly_static_mutex_t; // Static mutex type.


/**
 * Lock a static mutex variable.
 * @param mutex Mutex to lock.
 * @return true on success, false if already locked.
 */
bool kly_static_mutex_lock(kly_static_mutex_t *mutex);


/**
 * Unlock a static mutex variable.
 * @param mutex Mutex to unlock.
 */
void kly_static_mutex_unlock(kly_static_mutex_t *mutex);


#endif /* KLY_DRIVERS_INCLUDE_KLY_STATIC_MUTEX_H_ */
