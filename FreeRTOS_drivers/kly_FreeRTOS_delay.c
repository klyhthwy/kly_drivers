/**
 * @file kly_FreeRTOS_delay.c
 *
 * @author kelly.hathaway
 * @date Initial: Mar 21, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */


#include "kly_delay.h"
#include "FreeRTOS.h"
#include "task.h"



/**
 * Delay for a number of milliseconds.
 * @param time_ms Time to delay in milliseconds.
 */
void kly_delay_ms(unsigned long time_ms)
{
    vTaskDelay(time_ms / portTICK_PERIOD_MS);
}
