#define MICROPY_HW_BOARD_NAME       "BORMIO"
#define MICROPY_HW_MCU_NAME         "STM32H747"
#define MICROPY_HW_FLASH_FS_LABEL	"bormio"

#define MICROPY_FATFS_EXFAT         (1)
#define MICROPY_HW_ENABLE_RTC       (1)
#define MICROPY_HW_ENABLE_RNG       (1)
#define MICROPY_HW_ENABLE_ADC       (1)
#define MICROPY_HW_ENABLE_DAC       (1)
#define MICROPY_HW_ENABLE_USB       (1)
#define MICROPY_HW_ENABLE_SPI4      (1)
#define MICROPY_HW_HAS_SWITCH       (0)
#define MICROPY_HW_HAS_FLASH        (1)
#define MICROPY_HW_ENABLE_SERVO     (1)
#define MICROPY_HW_ENABLE_TIMER     (1)
#define MICROPY_HW_ENABLE_SDCARD    (0)
#define MICROPY_HW_ENABLE_MMCARD    (0)
// Reserved DMA streams
#define MICROPY_HW_DMA2S1_IS_RESERVED
#define MICROPY_HW_TIM_IS_RESERVED(id) (id == 1 || id == 6)

#define MICROPY_BOARD_EARLY_INIT BORMIO_board_early_init
void BORMIO_board_early_init(void);

#define MICROPY_RESET_TO_BOOTLOADER BORMIO_reboot_to_bootloader
void BORMIO_reboot_to_bootloader(void);

void BORMIO_board_low_power(int mode);
#define MICROPY_BOARD_LEAVE_STOP    BORMIO_board_low_power(0);
#define MICROPY_BOARD_ENTER_STOP    BORMIO_board_low_power(1);
#define MICROPY_BOARD_ENTER_STANDBY BORMIO_board_low_power(2);

// Internal 64MHz HSI
#define MICROPY_HW_CLK_USE_HSI  (1)
#define MICROPY_HW_CLK_PLLM     (4)
#define MICROPY_HW_CLK_PLLN     (240)
#define MICROPY_HW_CLK_PLLP     (2)
#define MICROPY_HW_CLK_PLLQ     (20)
#define MICROPY_HW_CLK_PLLR     (2)
#define MICROPY_HW_CLK_PLLFRACN (0)

// Use external SPI flash for storage
#define MICROPY_HW_ENABLE_INTERNAL_FLASH_STORAGE (0)
#define MICROPY_HW_SPIFLASH_ENABLE_CACHE (1)

// QSPI Flash 128Mbit
#define MICROPY_HW_SPIFLASH_SIZE_BITS (120 * 1024 * 1024)
#define MICROPY_HW_QSPIFLASH_SIZE_BITS_LOG2 (27)
#define MICROPY_HW_QSPIFLASH_CS     (pyb_pin_QSPI2_CS)
#define MICROPY_HW_QSPIFLASH_SCK    (pyb_pin_QSPI2_CLK)
#define MICROPY_HW_QSPIFLASH_IO0    (pyb_pin_QSPI2_D0)
#define MICROPY_HW_QSPIFLASH_IO1    (pyb_pin_QSPI2_D1)
#define MICROPY_HW_QSPIFLASH_IO2    (pyb_pin_QSPI2_D2)
#define MICROPY_HW_QSPIFLASH_IO3    (pyb_pin_QSPI2_D3)

#define MICROPY_HW_QSPI_PRESCALER       (4) //200MHz/4=50MHz
#define MICROPY_HW_QSPI_SAMPLE_SHIFT	(0)

// block device config for SPI flash
extern const struct _mp_spiflash_config_t spiflash_config;
extern struct _spi_bdev_t spi_bdev;
#define MICROPY_HW_BDEV_IOCTL(op, arg) ( \
    (op) == BDEV_IOCTL_NUM_BLOCKS ? (MICROPY_HW_SPIFLASH_SIZE_BITS / 8 / FLASH_BLOCK_SIZE) : \
    (op) == BDEV_IOCTL_INIT ? spi_bdev_ioctl(&spi_bdev, (op), (uint32_t)&spiflash_config) : \
    spi_bdev_ioctl(&spi_bdev, (op), (arg)) \
)
#define MICROPY_HW_BDEV_READBLOCKS(dest, bl, n) spi_bdev_readblocks(&spi_bdev, (dest), (bl), (n))
#define MICROPY_HW_BDEV_WRITEBLOCKS(src, bl, n) spi_bdev_writeblocks(&spi_bdev, (src), (bl), (n))

// 4 wait states
#define MICROPY_HW_FLASH_LATENCY    FLASH_LATENCY_2

// UART config
#define MICROPY_HW_UART3_TX         (pin_C10)
#define MICROPY_HW_UART3_RX         (pin_C11)

// I2C busses
#define MICROPY_HW_I2C1_SCL         (pin_B6)
#define MICROPY_HW_I2C1_SDA         (pin_B7)

#define MICROPY_HW_I2C2_SCL         (pin_B10)
#define MICROPY_HW_I2C2_SDA         (pin_B11)

#define MICROPY_HW_I2C3_SCL         (pin_H7)
#define MICROPY_HW_I2C3_SDA         (pin_H8)

// SPI buses
#define MICROPY_HW_SPI4_NSS  (pin_E11)
#define MICROPY_HW_SPI4_SCK  (pin_E12)
#define MICROPY_HW_SPI4_MISO (pin_E13)
#define MICROPY_HW_SPI4_MOSI (pin_E14)

// LEDs
#define MICROPY_HW_LED1             (pyb_pin_LEDR) // red
#define MICROPY_HW_LED2             (pyb_pin_LEDG) // green
#define MICROPY_HW_LED3             (pyb_pin_LEDB) // yellow
#define MICROPY_HW_LED_ON(pin)      (mp_hal_pin_low(pin))
#define MICROPY_HW_LED_OFF(pin)     (mp_hal_pin_high(pin))

// WiFi SDMMC
#define MICROPY_HW_SDIO_SDMMC       (2)
#define MICROPY_HW_SDIO_CK          (pin_C1)
#define MICROPY_HW_SDIO_CMD         (pin_D7)
#define MICROPY_HW_SDIO_D0          (pin_B14)
#define MICROPY_HW_SDIO_D1          (pin_B15)
#define MICROPY_HW_SDIO_D2          (pin_G11)
#define MICROPY_HW_SDIO_D3          (pin_B4)

// USB config
#define MICROPY_HW_USB_FS           (1)
#define USBD_CDC_RX_DATA_SIZE       (512)
#define USBD_CDC_TX_DATA_SIZE       (512)

#define USBD_MANUFACTURER_STRING      "Arduino"
#define USBD_PRODUCT_HS_STRING        "Bormio Virtual Comm Port in HS Mode"
#define USBD_PRODUCT_FS_STRING        "Bormio Virtual Comm Port in FS Mode"
#define USBD_CONFIGURATION_HS_STRING  "Bormio Config"
#define USBD_INTERFACE_HS_STRING      "Bormio Interface"
#define USBD_CONFIGURATION_FS_STRING  "Bormio Config"
#define USBD_INTERFACE_FS_STRING      "Bormio Interface"
#define MICROPY_PY_SYS_PLATFORM       "Bormio"
#define USBD_PID_RNDIS_CDC_MSC        0x005B
#define USBD_PID                      0x005B
#define USBD_VID                      0x2341
