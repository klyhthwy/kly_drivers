/**
 * @file kly_stm32_gpio.c
 *
 * @author kelly.hathaway
 * @date Initial: Feb 2, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */


#include "kly_error.h"
#include "kly_gpio.h"




/**
 * Configure a GPIO pin.
 * @param pin Pin to configure.
 * @param config Configuration.
 * @param pull Pull option.
 */
void kly_gpio_pin_config(uint8_t pin, kly_gpio_config_e config, kly_gpio_pull_e pull)
{

}



/**
 * Write to the pin output register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configuration.
 * @param pin Pin to write.
 * @param level Level to write. 0 for low, 1 for high.
 */
void kly_gpio_pin_write(uint8_t pin, uint8_t level)
{

}



/**
 * Clear a GPIO pin output to bring the pin level low.
 * @param pin Pin to clear.
 */
void kly_gpio_pin_clear(uint8_t pin)
{

}



/**
 * Set a GPIO pin output to bring the pin level high.
 * @param pin Pin to set.
 */
void kly_gpio_pin_set(uint8_t pin)
{

}



/**
 * Toggle a GPIO pin output to switch the pin level from
 * high to low or low to high.
 * @param pin Pin to toggle.
 */
void kly_gpio_pin_toggle(uint8_t pin)
{

}



/**
 * Read a pin input value register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configuration.
 * @param pin Pin to read.
 * @return Pin level. 0 for low, 1 for high
 */
uint8_t kly_gpio_pin_read(uint8_t pin)
{
    return 0;
}



/**
 * Configure a GPIO port.
 * @param port Port to configure.
 * @param mask Pin mask of pins on the port to configure.
 * @param config Configuration.
 * @param pull Pull option.
 */
void kly_gpio_port_config(uint8_t port, uint32_t mask, kly_gpio_config_e config, kly_gpio_pull_e pull)
{

}



/**
 * Write to the port output register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configurations.
 * @param port Port to write.
 * @param mask Pin mask of pins on the port to write.
 * @param level Levels to write. 0 for low, 1 for high.
 */
void kly_gpio_port_write(uint8_t port, uint32_t mask, uint32_t level)
{

}



/**
 * Clear GPIO port pins output to bring the pin levels low.
 * @param port Port to clear.
 * @param mask Pin mask of pins on the port to clear.
 */
void kly_gpio_port_clear(uint8_t port, uint32_t mask)
{

}



/**
 * Set GPIO port pins output to bring the pin levels high.
 * @param port Port to set.
 * @param mask Pin mask of pins on the port to set.
 */
void kly_gpio_port_set(uint8_t port, uint32_t mask)
{

}



/**
 * Toggle GPIO port pins output to switch the pin level from
 * high to low or low to high.
 * @param port Port to toggle.
 * @param mask Pin mask of pins on the port to toggle.
 */
void kly_gpio_port_toggle(uint8_t port, uint32_t mask)
{

}



/**
 * Read a pin input value register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configuration.
 * @param port Port to read.
 * @param mask Pin mask of pins on the port to read.
 * @return Pin levels. 0 for low, 1 for high
 */
uint32_t kly_gpio_port_read(uint8_t port, uint32_t mask)
{
    return 0;
}


