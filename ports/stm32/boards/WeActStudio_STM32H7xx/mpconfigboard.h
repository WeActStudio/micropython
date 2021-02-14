// This board is confirmed to operate using stlink and openocd.
// REPL is on UART(1) and is available through the stlink USB-UART device.
// To use openocd run "OPENOCD_CONFIG=boards/openocd_stm32f7.cfg" in
// the make command.
#define MICROPY_HW_BOARD_NAME       "WeActStudio_Core"
#define MICROPY_HW_MCU_NAME         "STM32H7xx"

#define MICROPY_HW_HAS_SWITCH       (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SERVO     (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_ADC       (1)
#define MICROPY_HW_ENABLE_SPI2      (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SDCARD    (1)
#define MICROPY_FATFS_EXFAT         (1)

// #define MICROPY_BOARD_EARLY_INIT    board_early_init
// void board_early_init(void);

// The board has an 25MHz HSE, the following gives 400MHz CPU speed
#define MICROPY_HW_CLK_PLLM (5)
#define MICROPY_HW_CLK_PLLN (160)
#define MICROPY_HW_CLK_PLLP (2)
#define MICROPY_HW_CLK_PLLQ (4)
#define MICROPY_HW_CLK_PLLR (2)

// The USB clock is set using PLL3
#define MICROPY_HW_CLK_PLL3M (5)
#define MICROPY_HW_CLK_PLL3N (48)
#define MICROPY_HW_CLK_PLL3P (2)
#define MICROPY_HW_CLK_PLL3Q (5)
#define MICROPY_HW_CLK_PLL3R (2)

#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_7 // 210-216 MHz needs 7 wait states

// Use external SPI flash for storage
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define WEACTSTUDIO_USE_QSPIFlash_AS_FLASH_STORAGE  (0)

// SPI Flash 64MBits
#define MICROPY_HW_SPIFLASH_SIZE_BITS (64 * 1024 * 1024)
#define MICROPY_HW_SPIFLASH_CS      (pin_D6)
#define MICROPY_HW_SPIFLASH_SCK     (pin_B3)
#define MICROPY_HW_SPIFLASH_MISO    (pin_B4)
#define MICROPY_HW_SPIFLASH_MOSI    (pin_D7)

// QSPI Flash 64MBits
#define MICROPY_HW_QSPIFLASH_SIZE_BITS   (64 * 1024 * 1024)
#define MICROPY_HW_QSPIFLASH_SIZE_BITS_LOG2 (26)
#define MICROPY_HW_QSPIFLASH_CS         (pin_B6)
#define MICROPY_HW_QSPIFLASH_SCK        (pin_B2)
#define MICROPY_HW_QSPIFLASH_IO0        (pin_D11)
#define MICROPY_HW_QSPIFLASH_IO1        (pin_D12)
#define MICROPY_HW_QSPIFLASH_IO2        (pin_E2)
#define MICROPY_HW_QSPIFLASH_IO3        (pin_D13)

// block device config for SPI flash
#if !MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE
#if WEACTSTUDIO_USE_QSPIFlash_AS_FLASH_STORAGE
extern const struct _mp_spiflash_config_t qspiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&qspiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#else
extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#endif
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))
#endif

// UART1 config
#define MICROPY_HW_UART1_TX         (pin_A9)
#define MICROPY_HW_UART1_RX         (pin_A10)

#define MICROPY_HW_UART_REPL        PYB_UART_1
#define MICROPY_HW_UART_REPL_BAUD   115200

// UART3 config
#define MICROPY_HW_UART3_TX  (pin_B10)
#define MICROPY_HW_UART3_RX  (pin_B11)
#define MICROPY_HW_UART3_RTS (pin_B14)
#define MICROPY_HW_UART3_CTS (pin_B13)

// I2C buses
#define MICROPY_HW_I2C2_SCL (pin_B10)
#define MICROPY_HW_I2C2_SDA (pin_B11)

#define MICROPY_HW_I2C4_SCL (pin_D12)
#define MICROPY_HW_I2C4_SDA (pin_D13)

// SPI buses
#define MICROPY_HW_SPI1_NSS  (pin_D6)
#define MICROPY_HW_SPI1_SCK  (pin_B3)
#define MICROPY_HW_SPI1_MISO (pin_B4)
#define MICROPY_HW_SPI1_MOSI (pin_D7)

#define MICROPY_HW_SPI2_NSS  (pin_B12)
#define MICROPY_HW_SPI2_SCK  (pin_B13)
#define MICROPY_HW_SPI2_MISO (pin_B14)
#define MICROPY_HW_SPI2_MOSI (pin_B15)

#define MICROPY_HW_SPI4_NSS  (pin_E11)
#define MICROPY_HW_SPI4_SCK  (pin_E12)
#define MICROPY_HW_SPI4_MISO (pin_E13)
#define MICROPY_HW_SPI4_MOSI (pin_E14)

// FDCAN bus
#define MICROPY_HW_CAN1_NAME  "FDCAN1"
#define MICROPY_HW_CAN1_TX    (pin_D1)
#define MICROPY_HW_CAN1_RX    (pin_D0)

#define MICROPY_HW_CAN2_NAME  "FDCAN2"
#define MICROPY_HW_CAN2_TX    (pin_B13)
#define MICROPY_HW_CAN2_RX    (pin_B12)

// USRSW is pulled low. Pressing the button makes the input go high.
#define MICROPY_HW_USRSW_PIN        (pin_C13)
#define MICROPY_HW_USRSW_PULL       (GPIO_PULLDOWN)
#define MICROPY_HW_USRSW_EXTI_MODE  (GPIO_MODE_IT_RISING)
#define MICROPY_HW_USRSW_PRESSED    (1)

// LEDs
#define MICROPY_HW_LED1             (pin_E3) // blue
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_high(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_low(pin))

// SD card detect switch
#define MICROPY_HW_SDMMC1_CK                (pin_C12)
#define MICROPY_HW_SDMMC1_CMD               (pin_D2)
#define MICROPY_HW_SDMMC1_D0                (pin_C8)
#define MICROPY_HW_SDMMC1_D1                (pin_C9)
#define MICROPY_HW_SDMMC1_D2                (pin_C10)
#define MICROPY_HW_SDMMC1_D3                (pin_C11)
#define MICROPY_HW_SDCARD_DETECT_PIN        (pin_D4)
#define MICROPY_HW_SDCARD_DETECT_PULL       (GPIO_PULLUP)
#define MICROPY_HW_SDCARD_DETECT_PRESENT    (GPIO_PIN_SET)

// USB config (CN15 - USB OTG HS with external PHY)
#define MICROPY_HW_USB_FS (1)

/******************************************************************************/
// Bootloader configuration

// Give Mboot access to the external QSPI flash
#define MBOOT_SPIFLASH_ADDR                     (0x90000000)
#define MBOOT_SPIFLASH_BYTE_SIZE                (512 * 128 * 1024)
#define MBOOT_SPIFLASH_LAYOUT                   "/0x90000000/512*128Kg"
#define MBOOT_SPIFLASH_ERASE_BLOCKS_PER_PAGE    (128 / 4) // 128k page, 4k erase block
#define MBOOT_SPIFLASH_CONFIG                   (&spiflash_config)
#define MBOOT_SPIFLASH_SPIFLASH                 (&spi_bdev.spiflash)
