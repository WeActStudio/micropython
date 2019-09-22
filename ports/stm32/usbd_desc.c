/*
 * This file is part of the MicroPython project, http://micropython.org/
 */

/**
  ******************************************************************************
  * @file    USB_Device/CDC_Standalone/Src/usbd_desc.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    26-February-2014
  * @brief   This file provides the USBD descriptors and string formating method.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_conf.h"

// need this header just for MP_HAL_UNIQUE_ID_ADDRESS
#include "py/mphal.h"

#define USBD_VID                      0x1209
#define USBD_PID                      0xabd1

#define USBD_LANGID_STRING            0x409
#define USBD_MANUFACTURER_STRING      "OpenMV"

#define USBD_PRODUCT_FS_STRING        "OpenMV Virtual Comm Port in FS Mode"
#define USBD_PRODUCT_HS_STRING        "OpenMV Virtual Comm Port in HS Mode"

#define USBD_SERIALNUMBER_FS_STRING   "000000000011"
#define USBD_SERIALNUMBER_HS_STRING   "000000000010"

#define USBD_INTERFACE_FS_STRING      "VCP Interface"
#define USBD_INTERFACE_HS_STRING      "VCP Interface"

#define USBD_CONFIGURATION_FS_STRING  "VCP Config"
#define USBD_CONFIGURATION_HS_STRING  "VCP Config"

__ALIGN_BEGIN static const uint8_t USBD_LangIDDesc[USB_LEN_LANGID_STR_DESC] __ALIGN_END = {
    USB_LEN_LANGID_STR_DESC,
    USB_DESC_TYPE_STRING,
    LOBYTE(USBD_LANGID_STRING),
    HIBYTE(USBD_LANGID_STRING),
};

// set the VID, PID and device release number
void USBD_SetVIDPIDRelease(usbd_cdc_msc_hid_state_t *usbd, uint16_t vid, uint16_t pid, uint16_t device_release_num, int cdc_only) {
    uint8_t *dev_desc = &usbd->usbd_device_desc[0];

    dev_desc[0] = USB_LEN_DEV_DESC; // bLength
    dev_desc[1] = USB_DESC_TYPE_DEVICE; // bDescriptorType
    dev_desc[2] = 0x00; // bcdUSB
    dev_desc[3] = 0x02; // bcdUSB
    if (cdc_only) {
        // Make it look like a Communications device if we're only
        // using CDC. Otherwise, windows gets confused when we tell it that
        // its a composite device with only a cdc serial interface.
        dev_desc[4] = 0x02; // bDeviceClass
        dev_desc[5] = 0x00; // bDeviceSubClass
        dev_desc[6] = 0x00; // bDeviceProtocol
    } else {
        // For the other modes, we make this look like a composite device.
        dev_desc[4] = 0xef; // bDeviceClass: Miscellaneous Device Class
        dev_desc[5] = 0x02; // bDeviceSubClass: Common Class
        dev_desc[6] = 0x01; // bDeviceProtocol: Interface Association Descriptor
    }
    dev_desc[7]  = USB_MAX_EP0_SIZE; // bMaxPacketSize
    dev_desc[8]  = LOBYTE(USBD_VID); // idVendor
    dev_desc[9]  = HIBYTE(USBD_VID); // idVendor
    dev_desc[10] = LOBYTE(USBD_PID); // idVendor
    dev_desc[11] = HIBYTE(USBD_PID); // idVendor
    dev_desc[12] = LOBYTE(device_release_num); // bcdDevice
    dev_desc[13] = HIBYTE(device_release_num); // bcdDevice
    dev_desc[14] = USBD_IDX_MFC_STR; // Index of manufacturer string
    dev_desc[15] = USBD_IDX_PRODUCT_STR; // Index of product string
    dev_desc[16] = USBD_IDX_SERIAL_STR; // Index of serial number string
    dev_desc[17] = USBD_MAX_NUM_CONFIGURATION; // bNumConfigurations
}

/**
  * @brief  Returns the device descriptor.
  * @param  speed: Current device speed
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer
  */
STATIC uint8_t *USBD_DeviceDescriptor(USBD_HandleTypeDef *pdev, uint16_t *length) {
    uint8_t *dev_desc = ((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->usbd_device_desc;
    *length = USB_LEN_DEV_DESC;
    return dev_desc;
}

/**
  * @brief  Returns a string descriptor
  * @param  idx: Index of the string descriptor to retrieve
  * @param  length: Pointer to data length variable
  * @retval Pointer to descriptor buffer, or NULL if idx is invalid
  */
STATIC uint8_t *USBD_StrDescriptor(USBD_HandleTypeDef *pdev, uint8_t idx, uint16_t *length) {
    const char *str = NULL;

    switch (idx) {
        case USBD_IDX_LANGID_STR:
            *length = sizeof(USBD_LangIDDesc);
            return (uint8_t*)USBD_LangIDDesc; // the data should only be read from this buf

        case USBD_IDX_MFC_STR:
            str = USBD_MANUFACTURER_STRING;
            break;

        case USBD_IDX_PRODUCT_STR:
            if (pdev->dev_speed == USBD_SPEED_HIGH) {
                str = USBD_PRODUCT_HS_STRING;
            } else {
                str = USBD_PRODUCT_FS_STRING;
            }
            break;

        case USBD_IDX_SERIAL_STR: {
            if(pdev->dev_speed == USBD_SPEED_HIGH) {
                str = USBD_SERIALNUMBER_HS_STRING;
            } else {
                str = USBD_SERIALNUMBER_FS_STRING;
            }
            break;
        }

        case USBD_IDX_CONFIG_STR:
            if (pdev->dev_speed == USBD_SPEED_HIGH) {
                str = USBD_CONFIGURATION_HS_STRING;
            } else {
                str = USBD_CONFIGURATION_FS_STRING;
            }
            break;

        case USBD_IDX_INTERFACE_STR:
            if (pdev->dev_speed == USBD_SPEED_HIGH) {
                str = USBD_INTERFACE_HS_STRING;
            } else {
                str = USBD_INTERFACE_FS_STRING;
            }
            break;

        default:
            // invalid string index
            return NULL;
    }

    uint8_t *str_desc = ((usbd_cdc_msc_hid_state_t*)pdev->pClassData)->usbd_str_desc;
    USBD_GetString((uint8_t*)str, str_desc, length);
    return str_desc;
}

const USBD_DescriptorsTypeDef USBD_Descriptors = {
    USBD_DeviceDescriptor,
    USBD_StrDescriptor,
};

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
