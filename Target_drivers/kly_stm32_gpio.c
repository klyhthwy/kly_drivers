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
#include "stm32f103xe.h"


#define GPIO_PORT_SIZE 16



static GPIO_TypeDef * const STM32_GPIO[] =
{
    GPIOA,
    GPIOB,
    GPIOC,
    GPIOD,
    GPIOE,
    GPIOF,
    GPIOG
};



/**
 * Get the configuration as defined in the STM32 reference manuals.
 * @param config
 * @param pull
 * @return
 */
static uint32_t get_config(kly_gpio_config_e config, kly_gpio_pull_e pull)
{
    uint32_t config_rv;

    config_rv = 4; // Reset value default.
    switch(config)
    {
        case KLY_GPIO_CONFIG_INPUT:
            if(pull == KLY_GPIO_PULL_NONE)
            {
                config_rv = 4;
            }
            else
            {
                config_rv = 8;
            }
            break;
        case KLY_GPIO_CONFIG_OUTPUT_PUSH_PULL:
            config_rv = 3;
            break;
        case KLY_GPIO_CONFIG_OUTPUT_OPEN_DRAIN:
            config_rv = 7;
            break;
        case KLY_GPIO_CONFIG_ANALOG:
            config_rv = 0;
            break;
        case KLY_GPIO_CONFIG_ALT_PUSH_PULL:
            config_rv = 0xB;
            break;
        case KLY_GPIO_CONFIG_ALT_OPEN_DRAIN:
            config_rv = 0xF;
            break;
    }

    return config_rv;
}



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
    GPIO_TypeDef *GPIO;
    uint32_t pin_config;
    uint32_t reg_config;
    uint32_t i;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    RCC->APB2ENR |= 1U << (port + 2);

    pin_config = get_config(config, pull);

    reg_config = GPIO->CRL;
    for(i = 0; i < 8; i++)
    {
        if(mask & (1U << i))
        {
            reg_config &= ~(0xF << (i * 4));
            reg_config |= pin_config << (i * 4);
        }
    }
    GPIO->CRL = reg_config;

    reg_config = GPIO->CRH;
    for(i = 0; i < 8; i++)
    {
        if(mask & (1U << (i+8)))
        {
            reg_config &= ~(0xF << (i * 4));
            reg_config |= pin_config << (i * 4);
        }
    }
    GPIO->CRH = reg_config;
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
    GPIO_TypeDef *GPIO;
    uint32_t odr;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    odr  = GPIO->ODR;
    odr &= ~mask;
    odr |= (level & mask);
    GPIO->ODR = odr;
}



/**
 * Clear GPIO port pins output to bring the pin levels low.
 * @param port Port to clear.
 * @param mask Pin mask of pins on the port to clear.
 */
void kly_gpio_port_clear(uint8_t port, uint32_t mask)
{
    GPIO_TypeDef *GPIO;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    GPIO->ODR &= ~mask;
}



/**
 * Set GPIO port pins output to bring the pin levels high.
 * @param port Port to set.
 * @param mask Pin mask of pins on the port to set.
 */
void kly_gpio_port_set(uint8_t port, uint32_t mask)
{
    GPIO_TypeDef *GPIO;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    GPIO->ODR |= mask;
}



/**
 * Toggle GPIO port pins output to switch the pin level from
 * high to low or low to high.
 * @param port Port to toggle.
 * @param mask Pin mask of pins on the port to toggle.
 */
void kly_gpio_port_toggle(uint8_t port, uint32_t mask)
{
    GPIO_TypeDef *GPIO;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    GPIO->ODR ^= mask;
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
    GPIO_TypeDef *GPIO;

    KLY_ASSERT(port < sizeof(STM32_GPIO) / sizeof(STM32_GPIO[0]));
    GPIO = STM32_GPIO[port];

    return GPIO->IDR & mask;
}


