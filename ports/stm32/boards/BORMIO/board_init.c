#include <string.h>
#include "py/mphal.h"
#include "storage.h"

#if OPENAMP_PY
#include "modopenamp.h"
#endif

void BORMIO_board_early_init(void) {
    #if OPENAMP_PY
    OpenAMP_MPU_Config();
    SystemCoreClockUpdate();
    #endif
}

void BORMIO_reboot_to_bootloader(void) {
    RTC_HandleTypeDef RTCHandle;
    RTCHandle.Instance = RTC;
    HAL_RTCEx_BKUPWrite(&RTCHandle, RTC_BKP_DR0, 0xDF59);
    NVIC_SystemReset();
}

void BORMIO_board_low_power(int mode)
{
    switch (mode) {
        case 0:     // Leave stop mode.
            break;
        case 1:     // Enter stop mode.
            break;
        case 2:     // Enter standby mode.
            break;
    }
    // Enable QSPI deepsleep for modes 1 and 2
    mp_spiflash_deepsleep(&spi_bdev.spiflash, (mode != 0));
}
