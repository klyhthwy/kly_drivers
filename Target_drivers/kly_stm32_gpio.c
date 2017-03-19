/**
 * @file kly_stm32_gpio.c
 *
 * @author kelly.hathaway
 * @date Initial: Feb 2, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */


#include <stdbool.h>
#include "kly_error.h"
#include "kly_gpio.h"
#include "kly_static_mutex.h"
#include "stm32f103xe.h"


#define GPIO_LOCK_PORT() \
    kly_static_mutex_lock(&PORT[port].state->mutex)
#define GPIO_UNLOCK_PORT() \
    kly_static_mutex_unlock(&PORT[port].state->mutex)


/**
 * State variables of a GPIO port.
 */
typedef struct port_state_struct
{
    kly_static_mutex_t mutex;
    bool initialized;
} port_state_s;

/**
 * Port data for each GPIO port on the device.
 */
typedef struct port_data_struct
{
    port_state_s * const state;
    GPIO_TypeDef * const GPIO;
} port_data_s;


// Port states for the stm32f1xx devices.
static port_state_s state[] =
{
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
    {
        .mutex = MUTEX_UNLOCKED,
        .initialized = false
    },
};

// Port data for each GPIO
static const port_data_s PORT[] =
{
    {
        .state = &state[0],
        .GPIO = GPIOA
    },
    {
        .state = &state[1],
        .GPIO = GPIOB
    },
    {
        .state = &state[2],
        .GPIO = GPIOC
    },
    {
        .state = &state[3],
        .GPIO = GPIOD
    },
    {
        .state = &state[4],
        .GPIO = GPIOE
    },
    {
        .state = &state[5],
        .GPIO = GPIOF
    },
    {
        .state = &state[6],
        .GPIO = GPIOG
    },
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
 * Initialize a GPIO port. Intended to perform one time initialization for ports that may change
 * configurations throughout the application.
 * @param port Port to initialize.
 */
void kly_gpio_port_initialize(uint8_t port)
{
    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    GPIO_LOCK_PORT();
    if(!PORT[port].state->initialized)
    {
        RCC->APB2ENR |= 1U << (port + 2);
        PORT[port].state->initialized = true;
    }
    GPIO_UNLOCK_PORT();
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
    uint32_t pin_config;
    uint32_t reg_config;
    uint32_t i;

    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    pin_config = get_config(config, pull);

    GPIO_LOCK_PORT();
    reg_config = PORT[port].GPIO->CRL;
    for(i = 0; i < 8; i++)
    {
        if(mask & (1U << i))
        {
            reg_config &= ~(0xF << (i * 4));
            reg_config |= pin_config << (i * 4);
        }
    }
    PORT[port].GPIO->CRL = reg_config;

    reg_config = PORT[port].GPIO->CRH;
    for(i = 0; i < 8; i++)
    {
        if(mask & (1U << (i+8)))
        {
            reg_config &= ~(0xF << (i * 4));
            reg_config |= pin_config << (i * 4);
        }
    }
    PORT[port].GPIO->CRH = reg_config;
    GPIO_UNLOCK_PORT();
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
    uint32_t odr;

    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    GPIO_LOCK_PORT();
    odr  = PORT[port].GPIO->ODR;
    odr &= ~mask;
    odr |= (level & mask);
    PORT[port].GPIO->ODR = odr;
    GPIO_UNLOCK_PORT();
}



/**
 * Clear GPIO port pins output to bring the pin levels low.
 * @param port Port to clear.
 * @param mask Pin mask of pins on the port to clear.
 */
void kly_gpio_port_clear(uint8_t port, uint32_t mask)
{
    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    PORT[port].GPIO->BRR = mask;
}



/**
 * Set GPIO port pins output to bring the pin levels high.
 * @param port Port to set.
 * @param mask Pin mask of pins on the port to set.
 */
void kly_gpio_port_set(uint8_t port, uint32_t mask)
{
    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    PORT[port].GPIO->BSRR = mask;
}



/**
 * Toggle GPIO port pins output to switch the pin level from
 * high to low or low to high.
 * @param port Port to toggle.
 * @param mask Pin mask of pins on the port to toggle.
 */
void kly_gpio_port_toggle(uint8_t port, uint32_t mask)
{
    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    GPIO_LOCK_PORT();
    PORT[port].GPIO->ODR ^= mask;
    GPIO_UNLOCK_PORT();
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
    KLY_ASSERT(port < sizeof(PORT) / sizeof(PORT[0]));

    return PORT[port].GPIO->IDR & mask;
}



/**
 * Configure a GPIO pin.
 * @param port Port of the pin.
 * @param pin Pin to configure.
 * @param config Configuration.
 * @param pull Pull option.
 */
void kly_gpio_pin_config(uint8_t port, uint8_t pin, kly_gpio_config_e config, kly_gpio_pull_e pull)
{
    kly_gpio_port_config(port, 1U << pin, config, pull);
}



/**
 * Write to the pin output register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configuration.
 * @param port Port of the pin.
 * @param pin Pin to write.
 * @param level Level to write. 0 for low, 1 for high.
 */
void kly_gpio_pin_write(uint8_t port, uint8_t pin, uint8_t level)
{
    kly_gpio_port_write(port, 1U << pin, level);
}



/**
 * Clear a GPIO pin output to bring the pin level low.
 * @param port Port of the pin.
 * @param pin Pin to clear.
 */
void kly_gpio_pin_clear(uint8_t port, uint8_t pin)
{
    kly_gpio_port_clear(port, 1U << pin);
}



/**
 * Set a GPIO pin output to bring the pin level high.
 * @param port Port of the pin.
 * @param pin Pin to set.
 */
void kly_gpio_pin_set(uint8_t port, uint8_t pin)
{
    kly_gpio_port_set(port, 1U << pin);
}



/**
 * Toggle a GPIO pin output to switch the pin level from
 * high to low or low to high.
 * @param port Port of the pin.
 * @param pin Pin to toggle.
 */
void kly_gpio_pin_toggle(uint8_t port, uint8_t pin)
{
    kly_gpio_port_toggle(port, 1U << pin);
}



/**
 * Read a pin input value register. Correct configuration is not checked
 * and it is left to the user to ensure correct pin configuration.
 * @param port Port of the pin to read.
 * @param pin Pin to read.
 * @return Pin level. 0 for low, 1 for high
 */
uint8_t kly_gpio_pin_read(uint8_t port, uint8_t pin)
{
    return kly_gpio_port_read(port, 1U << pin) >> pin;
}


