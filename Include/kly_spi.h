/**
 * @file kly_spi.h
 *
 * @author kelly.hathaway
 * @date Initial: Feb 13, 2017
 * @version 1
 * @date Released: Not Released
 * @details
 */

#ifndef KLY_DRIVERS_INCLUDE_KLY_SPI_H_
#define KLY_DRIVERS_INCLUDE_KLY_SPI_H_



#include <stdint.h>


/**
 * SPI bit transfer order.
 */
typedef enum kly_spi_bit_order_enum
{
    KLY_SPI_BIT_ORDER_MSB_FIRST = 0,
    KLY_SPI_BIT_ORDER_LSB_FIRST = 1
} kly_spi_bit_order_e;


/**
 * SPI Clock Polarity
 */
typedef enum kly_spi_clk_polarity_enum
{
    KLY_SPI_CLK_POLARITY_ACTIVE_HIGH = 0,
    KLY_SPI_CLK_POLARITY_ACTIVE_LOW  = 1
} kly_spi_clk_polarity_e;


/**
 * SPI Clock Phase
 */
typedef enum kly_spi_clk_phase_enum
{
    KLY_SPI_CLK_PHASE_LEADING   = 0,
    KLY_SPI_CLK_PHASE_TRAILING  = 1
} kly_spi_clk_phase_e;


typedef void (*kly_spi_cb_fp)(void); //!< Callback function pointer for complete.


/**
 * SPI fields that can change from transaction to transaction.
 */
typedef struct kly_spi_xfr_struct
{
    const uint8_t *txb; //!< Transmit buffer.
    uint8_t *rxb;       //!< Receive buffer.
    uint16_t txb_size;  //!< Transmit buffer size.
    uint16_t rxb_size;  //!< Receive buffer size.
    kly_spi_cb_fp cb;   //!< Callback used for SPI complete.
    uint8_t tx_or_byte; //!< Byte written when receiving more than transmitting.
} kly_spi_xfr_s;


/**
 * SPI device object required for SPI transactions.
 */
typedef const struct kly_spi_struct
{
    kly_spi_xfr_s * const instance;         //!< Variable instance of SPI details
    const uint8_t SPI_bus;                  //!< Hardware SPI bus to use.
    const uint8_t ss_pin;                   //!< Device chip select pin.
    const uint16_t frequency;               //!< SPI frequency for this device in kbps.
    const kly_spi_bit_order_e bit_order;    //!< Bit order of SPI communication.
    const kly_spi_clk_polarity_e clk_pol;   //!< Clock polarity.
    const kly_spi_clk_phase_e clk_phs;      //!< Clock phase.
} kly_spi_s;


/**
 * Initializes the hardware if not already done. Sets up the necessary
 * GPIO pins and initializes the object states.
 * @param device A single SPI device handle.
 */
void spi_init(kly_spi_s *device);


/**
 * Initiate a write to a SPI device
 * @param device Device SPI handle to begin write.
 */
void spi_send_receive(kly_spi_s *device);


#endif /* KLY_DRIVERS_INCLUDE_KLY_SPI_H_ */
