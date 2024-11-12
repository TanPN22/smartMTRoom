/*******************************************************************************
 *
 * Copyright (c) 2024
 * Beva, JSC.
 * All Rights Reserved
 *
 * Description: Include file for application
 *
 * Author: TanPN
 *
 * Last Changed By:  $Author: TanPN $
 * Revision:         $Revision: $
 * Last Changed:     $Date: 12/10/2024 $
 *
*******************************************************************************/
/******************************************************************************/
/*                              INCLUDE FILES                                 */
/******************************************************************************/
#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

/******************************************************************************/
/*                     EXPORTED TYPES and DEFINITIONS                         */
/******************************************************************************/
#define PIN_PIR         40
#define PIN_LED         41

bool pirStatus = 0;
/******************************************************************************/
/*                            FUNCTIONS PROTOTYPE                             */
/******************************************************************************/
void pir_Init(void);
void led_Init(void);
void pir_Control(void);
/******************************************************************************/
/*                                 FUNCTIONS                                  */
/******************************************************************************/
void app_main(void)
{
    //Init pin
    pir_Init();
    led_Init();

    while (true)
    {
        pirStatus = gpio_get_level(PIN_PIR);

        pir_Control();

        vTaskDelay(10/portTICK_PERIOD_MS);
    }
    
}

void pir_Init(void)
{
    gpio_config_t pirInitTypedef;

    pirInitTypedef.intr_type    = GPIO_INTR_DISABLE;
    pirInitTypedef.mode         = GPIO_MODE_INPUT;
    pirInitTypedef.pin_bit_mask = 1ULL << PIN_PIR;
    pirInitTypedef.pull_down_en = 0;
    pirInitTypedef.pull_up_en   = 0;

    gpio_config(&pirInitTypedef);
}

void led_Init(void)
{
    gpio_config_t ledInitTypedef;

    ledInitTypedef.intr_type    = GPIO_INTR_DISABLE;
    ledInitTypedef.mode         = GPIO_MODE_OUTPUT;
    ledInitTypedef.pin_bit_mask = 1ULL << PIN_LED;
    ledInitTypedef.pull_down_en = 0;
    ledInitTypedef.pull_up_en   = 0;

    gpio_config(&ledInitTypedef);
}

void pir_Control(void)
{
    gpio_set_level(PIN_LED, pirStatus);
}