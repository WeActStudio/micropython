# By default this board is configured to use mboot which must be deployed first
USE_MBOOT ?= 0

# By default the filesystem is in external QSPI flash.  But by setting the
# following option this board puts some code into external flash set in XIP mode.
# USE_MBOOT must be enabled; see f769_qspi.ld for code that goes in QSPI flash
USE_QSPI_XIP ?= 0
CFLAGS += -DUSE_QSPI_XIP=$(USE_QSPI_XIP)

# MCU settings
MCU_SERIES = h7
CMSIS_MCU = STM32H743xx
MICROPY_FLOAT_IMPL = double
AF_FILE = boards/stm32h743_af.csv

ifeq ($(USE_MBOOT),1)
ifeq ($(USE_QSPI_XIP),1)

# When using Mboot and QSPI-XIP the text is split between internal and external
# QSPI flash, and the filesystem is in internal flash between the bootloader and
# the main program text.
LD_FILES = boards/WeActStudio_STM32H7xx/h7xx_qspi.ld
TEXT0_ADDR = 0x08020000
TEXT1_ADDR = 0x90000000
TEXT0_SECTIONS = .isr_vector .text .data
TEXT1_SECTIONS = .text_qspi

else

# When using Mboot all the text goes together after the filesystem
LD_FILES = boards/stm32h743.ld boards/common_blifs.ld
TEXT0_ADDR = 0x08040000

endif
else

# When not using Mboot the ISR text goes first, then the rest after the filesystem
LD_FILES = boards/stm32h743.ld boards/common_ifs.ld
TEXT0_ADDR = 0x08000000
TEXT1_ADDR = 0x08040000

endif

# MicroPython settings
MICROPY_PY_LWIP = 1
MICROPY_PY_USSL = 1
MICROPY_SSL_MBEDTLS = 1
