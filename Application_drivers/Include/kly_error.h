/**
 * @file kly_error.h
 *
 * @author kelly.hathaway
 * @date Initial: Jan 29, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */

#ifndef KLY_DRIVERS_APPLICATION_DRIVERS_INCLUDE_KLY_ERROR_H_
#define KLY_DRIVERS_APPLICATION_DRIVERS_INCLUDE_KLY_ERROR_H_

#include <stdint.h>

#ifndef NDEBUG
#define KLY_ASSERT(COND) \
    do \
    { \
        if((COND) == 0) \
        { \
            kly_application_error_handler(__FILE__, __LINE__); \
        } \
    } while(0)
#else
#define KLY_ASSERT(...)
#endif // NDEBUG



/**
 * Application error handler for asserts. Implemented by application.
 * @param file File name
 * @param line Line number
 */
void kly_application_error_handler(const char *file, uint32_t line);


#endif /* KLY_DRIVERS_APPLICATION_DRIVERS_INCLUDE_KLY_ERROR_H_ */
