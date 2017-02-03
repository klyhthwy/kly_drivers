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
            kly_application_error_handler(__FILE__, __LINE__, "FAILED ASSERT"); \
        } \
    } while(0)

#define KLY_FAIL(MSG) \
    do \
    { \
        kly_application_error_handler(__FILE__, __LINE__, MSG); \
    } while(0)

#else

#define KLY_ASSERT(...)
#define KLY_FAIL(...)

#endif // NDEBUG


#define KLY_ERR_MSG_NOT_SUPPORTED       "Not Supported"
#define KLY_ERR_MSG_NOT_IMPLEMENTED     "Not Implemented"
#define KLY_ERR_MSG_NO_MEMORY           "No Memory"
#define KLY_ERR_MSG_INVALID_PARAM       "Invalid Parameter"


/**
 * Application error handler for asserts. Implemented by application.
 * @param file File name
 * @param line Line number
 * @param msg Error message
 */
void kly_application_error_handler(const char *file, uint32_t line, const char *msg);


#endif /* KLY_DRIVERS_APPLICATION_DRIVERS_INCLUDE_KLY_ERROR_H_ */
